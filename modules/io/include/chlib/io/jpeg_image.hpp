/**
 *  @file   jpeg_image.hpp
 *  @brief  JPEG Image object
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_JPEG_IMAGE__
#define __CHLIB_JPEG_IMAGE__

#include "chlib/io/image.hpp"


/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  JPEGImage
 *  @brief  JPEG Image object
 *  @author Christophe Ecabert
 *  @date   05.03.17
 */
class JPEGImage : public Image {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name JPEGImage
   *  @fn JPEGImage(void)
   *  @brief  Constructor
   */
  JPEGImage(void);
  
  /**
   *  @name ~JPEGImage
   *  @fn ~JPEGImage(void)
   *  @brief  Destructor
   */
  ~JPEGImage(void);
  
  /**
   *  @name Load
   *  @fn int Load(const std::string& filename)
   *  @brief  Load image from dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  int Load(const std::string& filename);
  
  /**
   *  @name Load
   *  @fn int Load(std::istream& stream)
   *  @brief  Load image from dist
   *  @param[in]  stream  Binary stream from where to load the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Load(std::istream& stream);
  
  /**
   *  @name Save
   *  @fn int Save(const std::string& filename)
   *  @brief  Save image to dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  int Save(const std::string& filename);
  
  /**
   *  @name Save
   *  @fn int Save(std::ostream& stream)
   *  @brief  Load image to dist
   *  @param[in]  stream  Binary stream to where to save the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Save(std::ostream& stream);
  
  
};
}  // namespace CHLib
#endif /* __CHLIB_JPEG_IMAGE__ */
