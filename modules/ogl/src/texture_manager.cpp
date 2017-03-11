/**
 *  @file   texture_manager.cpp
 *  @brief  Manage OpenGL texture, avoid multiple instance of the same data
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>

#include "chlib/ogl/texture_manager.hpp"
#include "chlib/io/image_loader.hpp"
#include "chlib/core/string_util.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name Instance
 *  @fn static OGLTextureManager& Instance(void)
 *  @brief  Provide unique reference to the manager (Singleton)
 *  @return Texture manager
 */
OGLTextureManager& OGLTextureManager::Instance(void) {
  // Singleton, thread safe since C++11
  static OGLTextureManager manager;
  return manager;
}

/*
 *  @name ~OGLTextureManager
 *  @fn ~OGLTextureManager(void)
 *  @brief  Destructor
 */
OGLTextureManager::~OGLTextureManager(void) {
  // Release all texture
  for (auto it = texture_map_.begin(); it != texture_map_.end(); ++it) {
    delete it->second;
    it->second = nullptr;
  }
}
  
#pragma mark -
#pragma mark Usage
  
/*
 *  @name Add
 *  @fn int Add(const std::string& filename, const std::string& tex_id)
 *  @brief  Add a new texture into the manager
 *  @param[in]  filename  Path to the image file
 *  @param[in]  id       id for this texture, if empty use filename
 *  @return -1 if error, 0 otherwise.
 */

int OGLTextureManager::Add(const std::string& filename,
                           const std::string& tex_id) {
  int err = 0;
  std::string key;
  // Check if ID is empty
  if (tex_id.empty()) {
    std::string dir, ext;
    StringUtil::ExtractDirectory(filename, &dir, &key, &ext);
  } else {
    key = tex_id;
  }
  // Already in it ?
  const auto it = texture_map_.find(key);
  if (it == texture_map_.end()) {
    // No, add it. First load image, if no isse create OGLTexture
    Image* img = nullptr;
    err = ImageLoader::Load(filename, &img);
    if (!err) {
      // Load texture
      OGLTexture* tex = new OGLTexture();
      err = tex->Upload(*img,
                        OGLTexture::WrappingMode::kClampToBorder,
                        OGLTexture::InterpolationMode::kLinear);
      if (!err) {
        texture_map_.emplace(key, tex);
      } else {
        std::cout << "Error, can not upload texture" << std::endl;
        // CLean up
        delete tex;
      }
      // Clean up
      delete img;
    } else {
      std::cout << "Unable to open : " << filename << std::endl;
    }
  }
  return err;
}

/*
 *  @name Get
 *  @fn OGLTexture* Get(const std::string& tex_id) const
 *  @brief  Provide acces to textire object
 *  @param[in]  tex_id  Texture ID to query
 *  @return OpenGL texture object
 */
OGLTexture* OGLTextureManager::Get(const std::string& tex_id) const {
  // Texture in map ?
  const auto it = texture_map_.find(tex_id);
  return it != texture_map_.end() ? it->second : nullptr;
}
  
#pragma mark -
#pragma mark Private
  
/*
 *  @name OGLTextureManager
 *  @fn OGLTextureManager(void)
 *  @brief  Constructor
 */
OGLTextureManager::OGLTextureManager(void) {
}
  
}  // namespace CHLib
