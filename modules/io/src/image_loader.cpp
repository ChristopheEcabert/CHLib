/**
 *  @file   image_loader.cpp
 *  @brief  Helper class to load images into memory
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */


#include "chlib/io/image_loader.hpp"
#include "chlib/io/tga_image.hpp"
#include "chlib/io/jpeg_image.hpp"
#include "chlib/io/png_image.hpp"
#include "chlib/core/string_util.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/*
 *  @name Load
 *  @fn static int Load(const std::string& filename, Image** image)
 *  @brief  Load an image file into memory
 *  @param[in]  filename  Path to the image file
 *  @param[out] image     Image object where to load the data
 */
int ImageLoader::Load(const std::string& filename, Image** image) {
  int err = -1;
  if (*image == nullptr) {
    std::string dir, file, ext;
    StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
    // Create based on extension
    if (ext == "tga") {
      *image = new TGAImage();
    } else if (ext == "jpg") {
      *image = new JPEGImage();
    } else if (ext == "png") {
      *image = new PNGImage();
    }
    if (*image != nullptr) {
      err = (*image)->Load(filename);
      // Release image if error in order to avoid leaks
      if (err) {
        delete *image;
        *image = nullptr;
      }
    }
  }
  return err;
}
}  // namespace CHLib
