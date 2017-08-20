/**
 *  @file   jpeg_image.cpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <fstream>
#include <setjmp.h>
#include <vector>
#include <cstring>

#include "jpeglib.h"
#include "oglkit/core/string_util.hpp"
#include "oglkit/io/jpeg_image.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
/**
 *  @struct ErrorManager
 *  @brief  Error handling, based on sample form libjpeg-turbo
 */
struct ErrorManager {
  /* "public" fields */
  struct jpeg_error_mgr pub;
  /* for return to caller */
  jmp_buf setjmp_buffer;
};
typedef struct ErrorManager *ErrorPtr;
  
/*
 * Here's the routine that will replace the standard error_exit method:
 */
void ErrorExit(j_common_ptr cinfo) {
  /* cinfo->err really points to a my_error_mgr struct, so coerce pointer */
  ErrorManager* myerr = (ErrorManager*) cinfo->err;
  
  /* Always display the message. */
  /* We could postpone this until after returning, if we chose. */
  (*cinfo->err->output_message) (cinfo);
  
  /* Return control to the setjmp point */
  longjmp(myerr->setjmp_buffer, 1);
}
  
/*
 *  @name JPEGImage
 *  @fn JPEGImage(void)
 *  @brief  Constructor
 */
JPEGImage::JPEGImage(void) {}

/*
 *  @name ~JPEGImage
 *  @fn ~JPEGImage(void)
 *  @brief  Destructor
 */
JPEGImage::~JPEGImage(void) {
  if (this->data_) {
    delete[] this->data_;
    this->data_ = nullptr;
  }
}
  
/*
 *  @name Load
 *  @fn int Load(const std::string& filename)
 *  @brief  Load image from dist
 *  @param[in]  filename  Path to ressource on the disk
 *  @return -1 if error, 0 otherwise
 */
int JPEGImage::Load(const std::string& filename) {
  int err = -1;
  // Open stream
  std::ifstream stream(filename.c_str());
  if (stream.is_open()) {
    // Load
    err = this->Load(stream);
  }
  return err;
}

/*
 *  @name Load
 *  @fn virtual int Load(std::istream& stream) = 0
 *  @brief  Load image from dist
 *  @param[in]  stream  Binary stream from where to load the ressource
 *  @return -1 if error, 0 otherwise
 */
int JPEGImage::Load(std::istream& stream) {
  int err = -1;
  if (stream.good()) {
    // Get stream lenght
    auto start_pos = stream.tellg();
    stream.seekg(0, std::ios_base::end);
    auto lengh = stream.tellg();
    // Return to start
    stream.seekg(start_pos);
    // Load raw data in memory
    std::vector<unsigned char> buffer(lengh);
    stream.read(reinterpret_cast<char*>(buffer.data()), lengh);
    if (stream.good()) {
      // This struct contains the JPEG decompression parameters and pointers to
      // working space (which is allocated as needed by the JPEG library).
      struct jpeg_decompress_struct cinfo;
      
      // We use our private extension JPEG error handler.
      // Note that this struct must live as long as the main JPEG parameter
      // struct, to avoid dangling-pointer problems.
      ErrorManager jerr;
      
      // Step 1: allocate and initialize JPEG decompression object
      // We set up the normal JPEG error routines, then override error_exit.
      cinfo.err = jpeg_std_error(&jerr.pub);
      jerr.pub.error_exit = ErrorExit;
      // Establish the setjmp return context for my_error_exit to use.
      if (setjmp(jerr.setjmp_buffer)) {
        // If we get here, the JPEG code has signaled an error.
        // We need to clean up the JPEG object, close the input file, and
        // return.
        jpeg_destroy_decompress(&cinfo);
        return -1;
      }
      // Now we can initialize the JPEG decompression object.
      jpeg_create_decompress(&cinfo);
      // Step 2: specify data source (eg, a file)
      jpeg_mem_src (&cinfo, buffer.data(), buffer.size());
      // Step 3: read file parameters with jpeg_read_header()
      jpeg_read_header(&cinfo, TRUE);
      // Step 5: Start decompressor
      jpeg_start_decompress(&cinfo);
      // We may need to do some setup of our own at this point before reading
      // the data.  After jpeg_start_decompress() we have the correct scaled
      // output image dimensions available, as well as the output colormap
      // if we asked for color quantization.
      // In this example, we need to make an output work buffer of the right
      // size.
      // JSAMPLEs per row in output buffer
      int row_stride = cinfo.output_width * cinfo.output_components;
      
      // Allocate buffer + define color space
      if (this->data_) {
        delete[] this->data_;
      }
      this->width_ = cinfo.output_width;
      this->height_ = cinfo.output_height;
      this->format_ = static_cast<Image::Format>(cinfo.output_components);
      size_t sz = this->width_ * this->height_ * cinfo.output_components;
      this->data_ = new unsigned char[sz];
      // Single row buffer
      JSAMPARRAY work_buffer;
      work_buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo,
                                               JPOOL_IMAGE,
                                               row_stride,
                                               1);
      // Step 6: while (scan lines remain to be read)
      //           jpeg_read_scanlines(...);
      // Here we use the library's state variable cinfo.output_scanline as the
      // loop counter, so that we don't have to keep track ourselves.
      int i = 0;
      while (cinfo.output_scanline < cinfo.output_height) {
        /* jpeg_read_scanlines expects an array of pointers to scanlines.
         * Here the array is only one element long, but you could ask for
         * more than one scanline at a time if that's more convenient.
         */
        jpeg_read_scanlines(&cinfo, work_buffer, 1);
        /* Assume put_scanline_someplace wants a pointer and sample count. */
        memcpy(reinterpret_cast<void*>(&(this->data_[i * row_stride])),
               reinterpret_cast<const char*>(work_buffer[0]), row_stride);
        ++i;
      }
      // Step 7: Finish decompression
      jpeg_finish_decompress(&cinfo);
      // Step 8: Release JPEG decompression object
      jpeg_destroy_decompress(&cinfo);
      
      err = !jerr.pub.num_warnings ? 0 : -1;
    }
  }
  return err;
}
  
/*
 *  @name Save
 *  @fn int Save(const std::string& filename)
 *  @brief  Save image to dist
 *  @param[in]  filename  Path to ressource on the disk
 *  @return -1 if error, 0 otherwise
 */
int JPEGImage::Save(const std::string& filename) const {
  int err = -1;
  // Check filename
  std::string dir, file, ext, f;
  StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext != ".jpg") {
    if (dir.empty()) {
      f = file + ".jpg";
    } else {
      f = dir + "/" + file + ".jpg";
    }
  } else {
    f = filename;
  }
  // Open stream
  std::fstream stream(f.c_str(),
                      std::ios_base::binary|std::ios_base::out);
  if (stream.is_open()) {
    // Load
    err = this->Save(stream);
  }
  return err;
}
  
/*
 *  @name Save
 *  @fn int Save(std::ostream& stream)
 *  @brief  Load image to dist
 *  @param[in]  stream  Binary stream to where to save the ressource
 *  @return -1 if error, 0 otherwise
 */
int JPEGImage::Save(std::ostream& stream) const {
  int err = -1;
  if (stream.good() && this->data_) {
    // This struct contains the JPEG compression parameters and pointers to
    // working space (which is allocated as needed by the JPEG library).
    // It is possible to have several such structures, representing multiple
    // compression/decompression processes, in existence at once.  We refer
    // to any one struct (and its associated working data) as a "JPEG object".
    struct jpeg_compress_struct cinfo;
    // This struct represents a JPEG error handler.  It is declared separately
    // because applications often want to supply a specialized error handler
    // (see the second half of this file for an example).  But here we just
    // take the easy way out and use the standard error handler, which will
    // print a message on stderr and call exit() if compression fails.
    // Note that this struct must live as long as the main JPEG parameter
    // struct, to avoid dangling-pointer problems.
    struct jpeg_error_mgr jerr;
    JSAMPROW row_pointer[1];      // pointer to JSAMPLE row[s]
    int row_stride = 0;           // physical row width in image buffer

    // Step 1: allocate and initialize JPEG compression object
    // We have to set up the error handler first, in case the initialization
    // step fails.  (Unlikely, but it could happen if you are out of memory.)
    // This routine fills in the contents of struct jerr, and returns jerr's
    // address which we place into the link field in cinfo.
    cinfo.err = jpeg_std_error(&jerr);
    // Now we can initialize the JPEG compression object.
    jpeg_create_compress(&cinfo);
    
    // Step 2: set parameters for compression
    // image width and height, in pixels
    cinfo.image_width = static_cast<int>(this->width_);
    cinfo.image_height = static_cast<int>(this->height_);
    // of color components per pixel
    cinfo.input_components = static_cast<int>(this->format_);
    cinfo.in_color_space = JCS_RGB;  // colorspace of input image
    
    // Step 3: specify data destination (eg, a file)
    unsigned char* work_buffer = nullptr;
    unsigned long work_buffer_length = 0;
    jpeg_mem_dest(&cinfo, &work_buffer, &work_buffer_length);
    
    // Now use the library's routine to set default compression parameters.
    // (You must set at least cinfo.in_color_space before calling this,
    // since the defaults depend on the source color space.)
    jpeg_set_defaults(&cinfo);
    // Now you can set any non-default parameters you wish to.
    // Here we just illustrate the use of quality (quantization table) scaling:
    jpeg_set_quality(&cinfo, 100, TRUE /* limit to baseline-JPEG values */);
    
    // Step 4: Start compressor
    // TRUE ensures that we will write a complete interchange-JPEG file.
    // Pass TRUE unless you are very sure of what you're doing.
    jpeg_start_compress(&cinfo, TRUE);
    
    // Step 5: while (scan lines remain to be written)
    //          jpeg_write_scanlines(...);
    // Here we use the library's state variable cinfo.next_scanline as the
    // loop counter, so that we don't have to keep track ourselves.
    // To keep things simple, we pass one scanline per call; you can pass
    // more if you wish, though.
    // JSAMPLEs per row in image_buffer
    row_stride = cinfo.image_width * cinfo.input_components;
    while (cinfo.next_scanline < cinfo.image_height) {
      // jpeg_write_scanlines expects an array of pointers to scanlines.
      // Here the array is only one element long, but you could pass
      // more than one scanline at a time if that's more convenient.
      row_pointer[0] = &(this->data_[cinfo.next_scanline * row_stride]);
      jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }
    // Step 6: Finish compression
    jpeg_finish_compress(&cinfo);
    // Dump into stream
    stream.write(reinterpret_cast<const char*>(work_buffer),
                 work_buffer_length);
    // Step 7: release JPEG compression object */
    // This is an important step since it will release a good deal of memory.
    jpeg_destroy_compress(&cinfo);
    // Release memory buffer
    free(work_buffer);
    // Check error
    err = !jerr.num_warnings ? 0 : -1;
  }
  return err;
}
  
#pragma mark -
#pragma mark Registration
  
/*
 *  @name JPEGProxy
 *  @fn   JPEGProxy(void)
 *  @brief  Constructor
 */
JPEGProxy::JPEGProxy(void) : ImageProxy() {}

/*
 *  @name ~JPEGProxy
 *  @fn   ~JPEGProxy(void)
 *  @brief  Destructor
 */
JPEGProxy::~JPEGProxy(void) {}

/*
 *  @name   Create
 *  @fn     Image* Create(void) const
 *  @brief  Create an instance of image with proper type
 */
Image* JPEGProxy::Create(void) const {
  return new JPEGImage();
}
  
/*
 *  @name Extension
 *  @fn const char* Extension(void) const
 *  @brief  Return the extension for a given type of image
 *  @return extension type
 */
const char* JPEGProxy::Extension(void) const {
  return "jpg";
}
  
// Explicit registration
JPEGProxy jpeg_proxy;

}  // namespace OGLKit
