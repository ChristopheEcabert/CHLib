/**
 *  @file   image.hpp
 *  @brief  Image abstraction class
 *  @ingroup io
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_IMAGE__
#define __CHLIB_IMAGE__

#include <cstdio>
#include <string>
#include <istream>
#include <fstream>


/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  Image
 *  @brief  Image abstraction layer
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  @ingroup io
 */
class Image {
 public:
  
#pragma mark -
#pragma mark Type definition
  
  /**
   *  @enum   Format
   *  @brief  List of possible image format
   */
  enum Format {
    /** Grayscale */
    kGrayscale = 1,
    /** Color - RGB */
    kRGB = 3,
    /** Color - RGBA */
    kRGBA = 4
  };
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name Image
   *  @fn Image(void)
   *  @brief  Constructor
   */
  Image(void) : format_(kGrayscale), width_(0), height_(0), data_(nullptr) {}
  
  /**
   *  @name ~Image
   *  @fn virtual ~Image(void)
   *  @brief  Destructor
   */
  virtual ~Image(void) {}
  
  /**
   *  @name Load
   *  @fn int Load(const std::string& filename)
   *  @brief  Load image from dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  virtual int Load(const std::string& filename) = 0;
  
  /**
   *  @name Load
   *  @fn virtual int Load(std::istream& stream) = 0
   *  @brief  Load image from dist
   *  @param[in]  stream  Binary stream from where to load the ressource
   *  @return -1 if error, 0 otherwise
   */
  virtual int Load(std::istream& stream) = 0;
  
  /**
   *  @name Save
   *  @fn virtual int Save(const std::string& filename) const = 0
   *  @brief  Save image to dist
   *  @param[in]  filename  Path to ressource on the disk
   *  @return -1 if error, 0 otherwise
   */
  virtual int Save(const std::string& filename) const = 0;
  
  /**
   *  @name Save
   *  @fn virtual int Save(std::ostream& stream) const = 0
   *  @brief  Load image to dist
   *  @param[in]  stream  Binary stream to where to save the ressource
   *  @return -1 if error, 0 otherwise
   */
  virtual int Save(std::ostream& stream) const = 0;
  
#pragma mark -
#pragma mark accessors
  
  /**
   *  @name   format
   *  @fn     const Format& format(void) const
   *  @brief  Provide image format
   *  @return Image format
   */
  const Format& format(void) const {
    return format_;
  }
  
  /**
   *  @name   width
   *  @fn     const size_t& width(void) const
   *  @brief  Provide image width
   *  @return Image width
   */
  const size_t& width(void) const {
    return width_;
  }
  
  /**
   *  @name   height
   *  @fn     const size_t& height(void) const
   *  @brief  Provide image height
   *  @return Image height
   */
  const size_t& height(void) const {
    return height_;
  }
  
  /**
   *  @name   data
   *  @fn     const unsigned char* data(void) const
   *  @brief  Provide image data
   *  @return Image data
   */
  const unsigned char* data(void) const {
    return data_;
  }
  
 protected:
  /** Image format */
  Format format_;
  /** Image width */
  size_t width_;
  /** Image height */
  size_t height_;
  /** Image data */
  unsigned char* data_;
};
  
  
/**
 *  @class  ImageProxy
 *  @brief  Interface for registration mechanism for Image type
 *  @author Christophe Ecabert
 *  @date   15.07.17
 *  @ingroup io
 */
class ImageProxy {
 public:
  
  /**
   *  @name   ImageProxy
   *  @fn     ImageProxy(void)
   *  @brief  Constructor
   */
  ImageProxy(void);
  
  /**
   *  @name   ~ImageProxy
   *  @fn     ~ImageProxy(void)
   *  @brief  Destructor
   */
  virtual ~ImageProxy(void);
  
  /**
   *  @name   Create
   *  @fn     virtual Image* Create(void) = 0
   *  @brief  Create an instance of image with proper type
   */
  virtual Image* Create(void) const = 0;
  
  /**
   *  @name Extension
   *  @fn virtual const char* Extension(void) const = 0
   *  @brief  Return the extension for a given type of image
   *  @return extension type
   */
  virtual const char* Extension(void) const = 0;
};
  
}  // namespace CHLib
#endif /* __CHLIB_IMAGE__ */
