/**
 *  @file   png_image.hpp
 *  @brief  PNG Image object
 *  @ingroup io
 *
 *  @author Christophe Ecabert
 *  @date   06.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_PNG_IMAGE__
#define __OGLKIT_PNG_IMAGE__

#include <istream>
#include <ostream>

#include "oglkit/io/image.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
/**
 *  @class  PNGImage
 *  @brief  PNG Image object
 *  @author Christophe Ecabert
 *  @date   06.03.17
 *  @ingroup io
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
   *  @fn int Save(const std::string& filename) const
   *  @brief  Save image to dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  int Save(const std::string& filename) const;
  
  /**
   *  @name Save
   *  @fn int Save(std::ostream& stream) const
   *  @brief  Load image to dist
   *  @param[in]  stream  Binary stream to where to save the ressource
   *  @return -1 if error, 0 otherwise
   */
  int Save(std::ostream& stream) const;
};
  
/**
 *  @class  PNGProxy
 *  @brief  PNG Image object registration interface
 *  @author  Christophe Ecabert
 *  @date   15.07.17
 *  @ingroup io
 */
class OGLKIT_EXPORTS PNGProxy : public ImageProxy {
 public:
  
  /**
   *  @name PNGProxy
   *  @fn   PNGProxy(void)
   *  @brief  Constructor
   */
  PNGProxy(void);
  
  /**
   *  @name ~PNGProxy
   *  @fn   ~PNGProxy(void)
   *  @brief  Destructor
   */
  ~PNGProxy(void);
  
  /**
   *  @name   Create
   *  @fn     Image* Create(void) const
   *  @brief  Create an instance of image with proper type
   */
  Image* Create(void) const;
  
  /**
   *  @name Extension
   *  @fn const char* Extension(void) const
   *  @brief  Return the extension for a given type of image
   *  @return extension type
   */
  const char* Extension(void) const;
};
}  // namespace OGLKit
#endif /* __OGLKIT_PNG_IMAGE__ */
