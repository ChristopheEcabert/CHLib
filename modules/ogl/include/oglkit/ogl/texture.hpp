/**
 *  @file   texture.hpp
 *  @brief  OpenGL texture object
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_TEXTURE__
#define __OGLKIT_TEXTURE__

#include <cstddef>

#include "oglkit/core/library_export.hpp"
#include "oglkit/io/image.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma Type forwarding 
  
/** OpenGL context for texture object */
struct OGLTextureContext;
  
/**
 *  @class  OGLTexture
 *  @brief  OpenGL texture object
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  @ingroup ogl
 */
class OGLKIT_EXPORTS OGLTexture {
 public:
  
#pragma mark -
#pragma mark Type Defintion
  
  /**
   *  @enum Type
   *  @brief  Type of texture, specular, normal, diffuse
   */
  enum Type {
    /** Normal */
    kNormal,
    /** Diffuse */
    kDiffuse,
    /** Specular */
    kSpecular
  };
  
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
   *  @param[in]  image         Image to upload to texture
   *  @param[in]  texture_type  Type of texture
   *  @param[in]  wrap_mode     Type of wrapping to use
   *  @param[in]  interp_mode   Type of interpolation to use
   *  @return -1 if error, 0 otherwise
   */
  int Upload(const Image& image,
             const Type texture_type,
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
#pragma mark Accessors
  
  /**
   *  @name get_type
   *  @fn OGLTexture::Type get_type(void) const
   *  @brief  Type of texture
   *  @return Type of texture
   */
  OGLTexture::Type get_type(void) const {
    return this->type_;
  }
  
  /**
   *  @name get_type_str
   *  @fn const std::string& get_type_str(void) const
   *  @brief  String holding type of texture
   *  @return string
   */
  const std::string& get_type_str(void) const {
    return this->type_str_;
  }
  
#pragma mark -
#pragma mark Private
  
 private:
  /** Texture object context */
  OGLTextureContext* ctx_;
  /** Width */
  size_t widht_;
  /** Height */
  size_t height_;
  /** Type */
  Type type_;
  /** Type string formatted */
  std::string type_str_;
};
  
}  // namespace OGLKit
#endif /* __OGLKIT_TEXTURE__ */
