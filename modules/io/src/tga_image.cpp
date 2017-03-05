/**
 *  @file   tga_image.cpp
 *  @brief  TGA Image object
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <fstream>
#include <iostream>

#include "chlib/io/tga_image.hpp"
#include "chlib/core/string_util.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark - 
#pragma mark Type definition

#pragma mark -
#pragma mark Initialization
/*
 *  @name TGAImage
 *  @fn TGAImage(void)
 *  @brief  Constructor
 */
TGAImage::TGAImage(void) {
}

/*
 *  @name ~TGAImage
 *  @fn ~TGAImage(void)
 *  @brief  Destructor
 */
TGAImage::~TGAImage(void) {
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
int TGAImage::Load(const std::string& filename) {
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
 *  @fn int Load(std::istream& stream)
 *  @brief  Load image from dist
 *  @param[in]  stream  Binary stream from where to load the ressource
 *  @return -1 if error, 0 otherwise
 */
int TGAImage::Load(std::istream& stream) {
  int err = -1;
  if (stream.good()) {
    // Read header
    stream >> header_;
    if (header_.image_type == 2 || header_.image_type == 3) {
      // Handle only color or grayscale image for the moment
      // Define image prop
      this->width_ = static_cast<size_t>(header_.image_spec.width);
      this->height_ = static_cast<size_t>(header_.image_spec.height);
      this->format_ = static_cast<Format>(header_.image_spec.pixel_depth / 8);
      // Allocate buffer
      if (this->data_) {
        delete[] this->data_;
      }
      int bpp = (header_.image_spec.pixel_depth + 7) / 8;
      const size_t sz = (this->width_  * this->height_ * bpp);
      this->data_ = new unsigned char[sz];
      // Read data
      stream.read(reinterpret_cast<char*>(this->data_), sz);
      // Convert image pixel format (BGR -> RGB or BGRA -> RGBA)
      unsigned char* src = this->data_;
      unsigned char* dst = &src[2];
      unsigned char tmp = 0;
      for (size_t n = 0; n < this->width_ * this->height_; ++n) {
        tmp = *src;
        *src = *dst;
        *dst = tmp;
        src += bpp;
        dst += bpp;
      }
      // Sanity check
      err = stream.good() ? 0 : -1;
    } else {
      std::cout << "Unsupported TGA format" << std::endl;
    }
  }
  return err;
}

/*
 *  @name Save
 *  @fn int Save(const std::string& filename) const
 *  @brief  Save image to dist
 *  @param[in]  filename  Path to ressource on the disk
 *  @return -1 if error, 0 otherwise
 */
int TGAImage::Save(const std::string& filename) const {
  int err = -1;
  // Check filename
  std::string dir, file, ext, f;
  StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext != ".tga") {
    if (dir.empty()) {
      f = file + ".tga";
    } else {
      f = dir + "/" + file + ".tga";
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
int TGAImage::Save(std::ostream& stream) const {
  int err = -1;
  if (stream.good()) {
    // Write header
    stream << header_;
    // Convert image pixel format (RGB -> BGR or RGBA -> BGRA)
    // Do copy since the method is marked as 'const' 
    size_t bpp = static_cast<size_t>(this->format_);
    size_t n_pixel = this->width_ * this->height_;
    std::vector<unsigned char> buffer(this->data_,
                                      this->data_ + (n_pixel * bpp));
    unsigned char* src = buffer.data();
    unsigned char* dst = &src[2];
    unsigned char tmp = 0;
    for (size_t n = 0; n < n_pixel; ++n) {
      tmp = *src;
      *src = *dst;
      *dst = tmp;
      src += bpp;
      dst += bpp;
    }
    // Write
    stream.write(reinterpret_cast<const char*>(buffer.data()),
                 this->width_ * this->height_ * bpp);
    err = stream.good() ? 0 : -1;
  }
  return err;
}
  
}  // namespace CHLib
