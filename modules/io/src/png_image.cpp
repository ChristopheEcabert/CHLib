/**
 *  @file   png_image.cpp
 *  @brief  PNG Image object
 *
 *  @author Christophe Ecabert
 *  @date   06.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <fstream>
#include <setjmp.h>
#include <vector>
#include <iostream>

#include "png.h"
#include "oglkit/core/string_util.hpp"
#include "oglkit/io/png_image.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {

/**
 *  @name
 *  @brief  Read data from stream
 *  @param[in,out]  png_ptr       Png decoder instance
 *  @param[in.out]  out_byte      Buffer where to place data laoded
 *  @param[in]      byte_to_read  Number of byte to be read
 */
void ReadData(png_structp png_ptr,
              png_bytep out_byte,
              png_size_t byte_to_read) {
  // Get io_ptr
  png_voidp io_ptr = png_get_io_ptr(png_ptr);
  if (io_ptr) {
    // Get stream
    std::istream* stream = reinterpret_cast<std::istream*>(io_ptr);
    // Read
    stream->read(reinterpret_cast<char*>(out_byte), byte_to_read);
  }
}
/**
 *  @name WriteData
 *  @brief  Write data into custom stream
 *  @param[in]  png_str       Png decoder instance
 *  @param[in]  in_byte       Pointer to data to write
 *  @param[in]  byte_to_write Number of byte to write
 */
void WriteData(png_structp png_ptr, png_bytep in_byte, png_size_t byte_to_write) {
  // Get io_ptr
  png_voidp io_ptr = png_get_io_ptr(png_ptr);
  if (io_ptr) {
    // Get stream
    std::ostream* stream = reinterpret_cast<std::ostream*>(io_ptr);
    // Write
    stream->write(reinterpret_cast<const char*>(in_byte), byte_to_write);
  }
}
  
/**
 *  @name FlushData
 *  @brief  Flush stream
 *  @param[in]  png_str       Png decoder instance
 */
void FlushData(png_structp png_ptr) {
  // Get io_ptr
  png_voidp io_ptr = png_get_io_ptr(png_ptr);
  if (io_ptr) {
    // Get stream
    std::ostream* stream = reinterpret_cast<std::ostream*>(io_ptr);
    // Flush
    stream->flush();
  }
}
  
Image::Format PNGFormatConverter(int type) {
  if (type == PNG_COLOR_TYPE_GRAY) {
    return Image::Format::kGrayscale;
  } else if (type == PNG_COLOR_TYPE_RGB || type == PNG_COLOR_TYPE_PALETTE) {
    return Image::Format::kRGB;
  } else if (type == PNG_COLOR_TYPE_RGBA) {
    return Image::Format::kRGBA;
  }
  return static_cast<Image::Format>(-1);
}
  
int PNGColorTypeConverter(const Image::Format& format) {
  if (format == Image::Format::kGrayscale ) {
    return PNG_COLOR_TYPE_GRAY;
  } else if (format == Image::Format::kRGB) {
    return PNG_COLOR_TYPE_RGB;
  } else if (format == Image::Format::kRGBA) {
    return PNG_COLOR_TYPE_RGBA;
  }
  return -1;
}
  
/*
 *  @name PNGImage
 *  @fn PNGImage(void)
 *  @brief  Constructor
 */
PNGImage::PNGImage(void) {}

/*
 *  @name ~PNGImage
 *  @fn ~PNGImage(void)
 *  @brief  Destructor
 */
PNGImage::~PNGImage(void) {
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
int PNGImage::Load(const std::string& filename) {
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
int PNGImage::Load(std::istream& stream) {
  int err = -1;
  if (stream.good()) {
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    enum {kPngSignatureLength = 8};
    // Read signature + Check
    unsigned char signature[kPngSignatureLength];
    stream.read(reinterpret_cast<char*>(&signature[0]), kPngSignatureLength);
    if (png_check_sig(signature, kPngSignatureLength)) {
      // get PNG file info struct (memory is allocated by libpng)
      png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING,
                                       nullptr,
                                       nullptr,
                                       nullptr);
      if (png_ptr) {
        // get PNG image data info struct (memory is allocated by libpng)
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr) {
          // Register custom callback to read data from stream
          png_set_read_fn(png_ptr, &stream, ReadData);
          // tell libpng we already read the signature
          png_set_sig_bytes(png_ptr, kPngSignatureLength);
          // Read header
          png_read_info(png_ptr, info_ptr);
          png_uint_32 width = 0;
          png_uint_32 height = 0;
          int bitDepth = 0;
          int colorType = -1;
          png_uint_32 retval = png_get_IHDR(png_ptr,
                                            info_ptr,
                                            &width,
                                            &height,
                                            &bitDepth,
                                            &colorType,
                                            nullptr, nullptr, nullptr);
          if (retval == 1) {
            // Fix palettetype
            if (colorType == PNG_COLOR_TYPE_PALETTE) {
              png_set_palette_to_rgb(png_ptr);
            }
            // Update info
            png_read_update_info(png_ptr, info_ptr);
            // Set prop
            this->width_ = static_cast<size_t>(width);
            this->height_ = static_cast<size_t>(height);
            this->format_ = PNGFormatConverter(colorType);
            // Allocate
            if (this->data_) {
              delete[] this->data_;
            }
            const size_t sz = this->width_ * this->height_ * this->format_;
            this->data_ = new unsigned char[sz];
            // Read info + one line at a time
            const size_t bytesPerRow = png_get_rowbytes(png_ptr, info_ptr);
            for (size_t r = 0; r < this->height_; ++r) {
              png_read_row(png_ptr, &this->data_[r * bytesPerRow], nullptr);
            }
            err = 0;
          }
        }
      }
    }
    // release reading struct
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
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
int PNGImage::Save(const std::string& filename) const {
  int err = -1;
  // Check filename
  std::string dir, file, ext, f;
  StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext != ".png") {
    if (dir.empty()) {
      f = file + ".png";
    } else {
      f = dir + "/" + file + ".png";
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
int PNGImage::Save(std::ostream& stream) const {
  int err = -1;
  if (stream.good() && this->data_) {
    png_structp png_ptr = nullptr;
    png_infop info_ptr = nullptr;
    // get PNG file info struct (memory is allocated by libpng)
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING,
                                      nullptr, nullptr, nullptr);
    if (png_ptr) {
      // Info
      info_ptr = png_create_info_struct(png_ptr);
      if (info_ptr) {
        // Register custom callback
        png_set_write_fn(png_ptr, &stream, WriteData, FlushData);
        
        // Write header (8 bit colour depth)
        png_uint_32 w = static_cast<png_uint_32>(this->width_);
        png_uint_32 h = static_cast<png_uint_32>(this->height_);
        int colorType = PNGColorTypeConverter(this->format_);
        png_set_IHDR(png_ptr, info_ptr, w, h, 8, colorType,
                     PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_DEFAULT,
                     PNG_FILTER_TYPE_DEFAULT);
        png_write_info(png_ptr, info_ptr);
        
        // Write image data, one row at a time
        size_t byte_per_row = this->width_ * this->format_;
        for (size_t r = 0; r < this->height_; ++r) {
          png_write_row(png_ptr, &(this->data_[r * byte_per_row]));
        }
        // End write
        png_write_end(png_ptr, nullptr);
        err = 0;
      }
    }
    // Release
    png_destroy_write_struct(&png_ptr, &info_ptr);
  }
  return err;
}
  
#pragma mark -
#pragma mark Registration
  
/*
 *  @name PNGProxy
 *  @fn   PNGProxy(void)
 *  @brief  Constructor
 */
PNGProxy::PNGProxy(void) : OGLKit::ImageProxy() {}
  
/*
 *  @name ~PNGProxy
 *  @fn   ~PNGProxy(void)
 *  @brief  Destructor
 */
PNGProxy::~PNGProxy(void) {}
  
/*
 *  @name   Create
 *  @fn     Image* Create(void) const
 *  @brief  Create an instance of image with proper type
 */
Image* PNGProxy::Create(void) const {
  return new PNGImage();
}
  
/*
 *  @name Extension
 *  @fn const char* Extension(void) const
 *  @brief  Return the extension for a given type of image
 *  @return extension type
 */
const char* PNGProxy::Extension(void) const {
  return "png";
}
  
// Explicit registration
PNGProxy png_proxy;

}  // namespace OGLKit
