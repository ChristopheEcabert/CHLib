/**
 *  @file   image_loader.hpp
 *  @brief  Helper class to load images into memory
 *  @ingroup io
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_IMAGE_LOADER__
#define __CHLIB_IMAGE_LOADER__

#include "chlib/core/library_export.hpp"
#include "chlib/io/image.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  ImageLoader
 *  @brief  Helper class to load images into memory
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  @ingroup io
 */
class CHLIB_EXPORTS ImageLoader {
 public:
  
  /** 
   *  @name Load
   *  @fn static int Load(const std::string& filename, Image** image)
   *  @brief  Load an image file into memory
   *  @param[in]  filename  Path to the image file
   *  @param[out] image     Image object where to load the data
   */
  static int Load(const std::string& filename, Image** image);
};
}  // namespace CHLib

#endif /* __CHLIB_IMAGE_LOADER__ */
