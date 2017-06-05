/**
 *  @file   texture_manager.hpp
 *  @brief  Manage OpenGL texture, avoid multiple instance of the same data
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_OGLTEXTURE_MANAGER__
#define __CHLIB_OGLTEXTURE_MANAGER__

#include <string>
#include <unordered_map>

#include "chlib/core/library_export.hpp"
#include "chlib/ogl/texture.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
/**
 *  @class  OGLTextureManager
 *  @brief  Manager for OpenGL texture object
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  @ingroup ogl
 */
class CHLIB_EXPORTS OGLTextureManager {
 public:
  
#pragma mark -
#pragma mark Initialization
  
  /**
   *  @name Instance
   *  @fn static OGLTextureManager& Instance(void)
   *  @brief  Provide unique reference to the manager (Singleton)
   *  @return Texture manager
   */
  static OGLTextureManager& Instance(void);
  
  /**
   *  @name ~OGLTextureManager
   *  @fn ~OGLTextureManager(void)
   *  @brief  Destructor
   */
  ~OGLTextureManager(void);
  
  /**
   *  @name OGLTextureManager
   *  @fn OGLTextureManager(const OGLTextureManager& other) = delete
   *  @brief  Copy constructor
   *  @param[in]  other Object to copy from
   */
  OGLTextureManager(const OGLTextureManager& other) = delete;
  
  /**
   *  @name operator=
   *  @fn OGLTextureManager& operator=(const OGLTextureManager& rhs)
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned object
   *
   */
  OGLTextureManager& operator=(const OGLTextureManager& rhs) = delete;
  
#pragma mark -
#pragma mark Usage
  
  /**
   *  @name Add
   *  @fn OGLTexture* Add(const std::string& filename,const std::string& tex_id)
   *  @brief  Add a new texture into the manager
   *  @param[in]  filename  Path to the image file
   *  @param[in]  tex_id       id for this texture, if empty use filename
   *  @return nullptr if error, reference to the new texture otherwise.
   */
   
  OGLTexture* Add(const std::string& filename, const std::string& tex_id);
  
  /**
   *  @name Get
   *  @fn OGLTexture* Get(const std::string& tex_id) const
   *  @brief  Provide acces to textire object
   *  @param[in]  tex_id  Texture ID to query
   *  @return OpenGL texture object
   */
  OGLTexture* Get(const std::string& tex_id) const;
  
  /**
   *  @name Remove
   *  @fn void Remove(const std::string& tex_id)
   *  @brief  Release specific textures
   *  @param[in]  tex_id  Texture ID to remove/release, if empty remove every
   *                      textures
   */
  void Remove(const std::string& tex_id);
  
#pragma mark -
#pragma mark Accessors
  
  /**
   *  @name set_wraping_mode
   *  @fn  void set_wraping_model(const OGLTexture::WrappingMode& mode)
   *  @brief  Set the texture type of wrapping
   *  @param[in]  mode  Type of texture wrapping
   */
  void set_wraping_model(const OGLTexture::WrappingMode& mode) {
    wrapping_mode_ = mode;
  }
  
  /**
   *  @name set_interpolation_mode
   *  @fn void set_interpolation_mode(const OGLTexture::InterpolationMode& mode)
   *  @brief  Set the texture type of interpolation
   *  @param[in]  mode  Type of texture interpolation
   */
  void set_interpolation_mode(const OGLTexture::InterpolationMode& mode) {
    interp_mode_ = mode;
  }
  
#pragma mark -
#pragma mark Private
 private:
  
  /** 
   *  @name OGLTextureManager
   *  @fn OGLTextureManager(void)
   *  @brief  Constructor
   */
  OGLTextureManager(void);
  
  /** Texture map - hold all registered texture */
  std::unordered_map<std::string, OGLTexture*> texture_map_;
  /** Type of wrapping */
  OGLTexture::WrappingMode wrapping_mode_;
  /** Type of interpolation */
  OGLTexture::InterpolationMode interp_mode_;
};
}  // namespace CHLib


#endif /* __CHLIB_OGLTEXTURE_MANAGER__ */
