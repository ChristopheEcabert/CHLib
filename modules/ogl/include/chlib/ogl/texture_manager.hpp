/**
 *  @file   texture_manager.hpp
 *  @brief  Manage OpenGL texture, avoid multiple instance of the same data
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
   *  @fn int Add(const std::string& filename, const std::string& tex_id)
   *  @brief  Add a new texture into the manager
   *  @param[in]  filename  Path to the image file
   *  @param[in]  id       id for this texture, if empty use filename
   *  @return -1 if error, 0 otherwise.
   */
   
  int Add(const std::string& filename, const std::string& tex_id);
  
  /**
   *  @name Get
   *  @fn OGLTexture* Get(const std::string& tex_id) const
   *  @brief  Provide acces to textire object
   *  @param[in]  tex_id  Texture ID to query
   *  @return OpenGL texture object
   */
  OGLTexture* Get(const std::string& tex_id) const;
  
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
};
}  // namespace CHLib


#endif /* __CHLIB_OGLTEXTURE_MANAGER__ */
