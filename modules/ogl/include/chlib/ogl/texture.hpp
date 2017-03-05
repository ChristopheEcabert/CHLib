/**
 *  @file   texture.hpp
 *  @brief  OpenGL texture object
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_TEXTURE__
#define __CHLIB_TEXTURE__

#include <cstddef>
#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

#include "chlib/core/library_export.hpp"
#include "chlib/io/image.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  OGLTexture
 *  @brief  OpenGL texture object
 *  @author Christophe Ecabert
 *  @date   05.03.17
 */
class CHLIB_EXPORTS OGLTexture {
 public:
  
#pragma mark -
#pragma mark Type Defintion
  
  /** 
   *  @enum WrappingMode
   *  @brief  Type of wrapping
   */
  enum WrappingMode {
    /** Repeated */
    kRepeat,
    /** Repeated - mirrored */
    kMirroredRepeat,
    /** Clamp to border */
    kClampToBorder
  };
  
  /**
   *  @enum InterpolationMode
   *  @brief  Type of interpolation
   */
  enum InterpolationMode {
    /** Nearest - blocky */
    kNearest,
    /** Linear */
    kLinear
  };
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name OGLTexture
   *  @fn OGLTexture(void)
   *  @brief  Constructor
   */
  OGLTexture(void);
  
  /**
   *  @name OGLTexture
   *  @fn OGLTexture(const OGLTexture& other) = delete
   *  @brief  Copy Constructor
   *  @param[in]  other Object to copy
   */
  OGLTexture(const OGLTexture& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLTexture& operator=(const OGLTexture& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign form
   *  @return Newly assign object
   */
  OGLTexture& operator=(const OGLTexture& rhs) = delete;
  
  /**
   *  @name ~OGLTexture
   *  @fn ~OGLTexture(void)
   *  @brief  Destructor
   */
  ~OGLTexture(void);
  
  /**
   *  @name Upload
   *  @fn int Upload(const Image& image, const WrappingMode wrap_mode,
                     const InterpolationMode interp_mode)
   *  @brief  Upload a given image into OpenGL Texture buffer
   *  @param[in]  image       Image to upload to texture
   *  @param[in]  wrap_mode   Type of wrapping to use
   *  @param[in]  interp_mode Type of interpolation to use
   *  @return -1 if error, 0 otherwise
   */
  int Upload(const Image& image,
             const WrappingMode wrap_mode,
             const InterpolationMode interp_mode);
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @name Bind
   *  @fn void Bind(const int texture_unit) const
   *  @brief  Bind the texture to a given texture unit
   *  @param[in]  texture_unit  Index of the texture unit to bind to
   */
  void Bind(const int texture_unit) const;
  
  /**
   *  @name Unbind
   *  @fn void Unbind(void) const
   *  @brief  Unbind the texture
   */
  void Unbind(void) const;
  
#pragma mark -
#pragma mark Private
  
 private:
  /** Texture object */
  GLuint tex_;
  /** Width */
  size_t widht_;
  /** Height */
  size_t height_;
  /** Format */
  GLenum format_;
};
  
}  // namespace CHLib
#endif /* __CHLIB_TEXTURE__ */
