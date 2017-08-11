/**
 *  @file   texture.cpp
 *  @brief  OpenGL texture object
 *
 *  @author Christophe Ecabert
 *  @date   05.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>

#include "oglkit/ogl/texture.hpp"

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#endif

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Type definition + helper function
  
/**
 *  @struct OGLTextureContext
 *  @brief  Structure encapsulating OpenGL related information
 */
struct OGLTextureContext {
  /** Texture object */
  GLuint tex;
  /** Texture format */
  GLenum format;
  
  /** 
   *  @name OGLTextureContext
   *  @fn OGLTextureContext(void)
   *  @brief  Constructor
   */
  OGLTextureContext(void) : tex(0) {
    // Create texture object
    glGenTextures(1, &tex);
  }
  
  /**
   *  @name ~OGLTextureContext
   *  @fn ~ OGLTextureContext(void)
   *  @brief  Destructor
   */
  ~OGLTextureContext(void) {
    // Create texture object
    glDeleteTextures(1, &tex);
    tex = 0;
  }
};
  
/**
 *  @name
 *  @fn
 *  @brief  Convert a given texture Type into a readable string format
 *  @param[in]  type  Texture type
 *  @param[out] str   Readable string type
 */
void SetFormattedString(const OGLTexture::Type& type, std::string* str) {
  switch (type) {
    case OGLTexture::kDiffuse: {
      str->assign("diffuse");
    } break;
      
    case OGLTexture::kNormal: {
      str->assign("normal");
    } break;
      
    case OGLTexture::kSpecular: {
      str->assign("specular");
    } break;
      
    default:  str->assign("diffuse");
      break;
  }
}
  
#pragma mark -
#pragma mark Initialization
  
/**
 *  @name ImageFormatConverter
 *  @brief  Convert image format to understandable OpenGL format
 *  @param[in]  format  Image format to convert
 "  @return Corresponding OpenGL format of -1 if error.
 */
GLenum ImageFormatConverter(const Image::Format& format) {
  GLenum ret = -1;
  if (format == Image::Format::kGrayscale) {
    ret = GL_RED;
  } else if (format == Image::Format::kRGB) {
    ret = GL_RGB;
  } else if (format == Image::Format::kRGBA) {
    ret = GL_RGBA;
  }
  return ret;
}
  
GLint WrappingConverter(const OGLTexture::WrappingMode& mode) {
  GLint ret;
  if (mode == OGLTexture::WrappingMode::kRepeat) {
    ret = GL_REPEAT;
  } else if (mode == OGLTexture::WrappingMode::kMirroredRepeat) {
    ret = GL_CLAMP_TO_EDGE;
  } else if (mode == OGLTexture::WrappingMode::kClampToBorder) {
    ret = GL_CLAMP_TO_BORDER;
  }
  return ret;
}
  
GLint InterpolationConverter(const OGLTexture::InterpolationMode& mode) {
  GLint ret;
  if (mode == OGLTexture::InterpolationMode::kNearest) {
    ret = GL_NEAREST;
  } else if (mode == OGLTexture::InterpolationMode::kLinear) {
    ret = GL_LINEAR;
  }
  return ret;
}
  
/*
 *  @name OGLTexture
 *  @fn OGLTexture(void)
 *  @brief  Constructor
 */
OGLTexture::OGLTexture(void) {
  // Create texture object
  ctx_ = new OGLTextureContext();
}

/*
 *  @name ~OGLTexture
 *  @fn ~OGLTexture(void)
 *  @brief  Destructor
 */
OGLTexture::~OGLTexture(void) {
  // Release texture
  if (ctx_) {
    delete ctx_;
    ctx_ = nullptr;
  }
}

/*
 *  @name Upload
 *  @fn int Upload(const Image& image)
 *  @brief  Upload a given image into OpenGL Texture buffer
 *  @return -1 if error, 0 otherwise
 */
int OGLTexture::Upload(const Image& image,
                       const Type texture_type,
                       const WrappingMode wrap_mode,
                       const InterpolationMode interp_mode) {
  int err = -1;
  if (ctx_->tex) {
    // Define texture prop
    this->widht_ = image.width();
    this->height_ = image.height();
    ctx_->format = ImageFormatConverter(image.format());
    this->type_ = texture_type;
    SetFormattedString(this->type_, &this->type_str_);
    // Continu
    if (ctx_->format != -1) {
      glBindTexture(GL_TEXTURE_2D, ctx_->tex);
      // Interpolation + border behaviour
      GLint wrap = WrappingConverter(wrap_mode);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
      GLint interp = InterpolationConverter(interp_mode);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, interp);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, interp);
      // Texutre
      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   static_cast<GLint>(ctx_->format),
                   static_cast<GLsizei>(this->widht_),
                   static_cast<GLsizei>(this->height_),
                   0,
                   ctx_->format,
                   GL_UNSIGNED_BYTE,
                   static_cast<const GLvoid*>(image.data()));
      // Unbind
      glBindTexture(GL_TEXTURE_2D, 0);
      err = glGetError() == GL_NO_ERROR ? 0 : -1;
    }
  }
  return err;
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name Bind
 *  @fn void Bind(const int texture_unit) const
 *  @brief  Bind the texture to a given texture unit
 *  @param[in]  texture_unit  Index of the texture unit to bind to
 */
void OGLTexture::Bind(const int texture_unit) const {
  // Active the given texutre unit
  glActiveTexture(GL_TEXTURE0 + texture_unit);
  // Bind texture
  glBindTexture(GL_TEXTURE_2D, ctx_->tex);
}

/*
 *  @name Unbind
 *  @fn void Unbind(void) const
 *  @brief  Unbind the texture
 */
void OGLTexture::Unbind(void) const {
  glBindTexture(GL_TEXTURE_2D, 0);
}
  
}  // namespace OGLKit
