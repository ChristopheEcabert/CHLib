/**
 *  @file   png_image.hpp
 *  @brief  PNG Image object
 *
 *  @author Christophe Ecabert
 *  @date   06.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_PNG_IMAGE__
#define __CHLIB_PNG_IMAGE__

#include <istream>
#include <ostream>

#include "chlib/io/image.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  PNGImage
 *  @brief  PNG Image object
 *  @author Christophe Ecabert
 *  @date   06.03.17
 */
class PNGImage : public Image {
 public:
  
#pragma mark -
#pragma mark Type Definition
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name PNGImage
   *  @fn PNGImage(void)
   *  @brief  Constructor
   */
  PNGImage(void);
  
  /**
   *  @name PNGImage
   *  @fn PNGImage(const PNGImage& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy
   */
  PNGImage(const PNGImage& other) = delete;
  
  /**
   *  @name operator=
   *  @fn PNGImage& operator=(const PNGImage& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign form
   *  @return Newly assign object
   */
  PNGImage& operator=(const PNGImage& rhs) = delete;
  
  /**
   *  @name ~PNGImage
   *  @fn ~PNGImage(void)
   *  @brief  Destructor
   */
  ~PNGImage(void);
  
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
  int Save(const std::string& filename) const;
  
  /**
   *  @name Save
   *  @fn int Save(std::ostream& stream)
   *  @brief  Load image to dist
   *  @param[in]  stream  Binary stream to where to save the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Save(std::ostream& stream) const;
};
}  // namespace CHLib
#endif /* __CHLIB_PNG_IMAGE__ */
