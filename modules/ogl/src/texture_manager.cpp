/**
 *  @file   texture_manager.cpp
 *  @brief  Manage OpenGL texture, avoid multiple instance of the same data
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>

#include "oglkit/ogl/texture_manager.hpp"
#include "oglkit/io/image_factory.hpp"
#include "oglkit/core/string_util.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
OGLTexture::Type ConvertTypeFromString(const std::string& type) {
  if (type == "diffuse" || type == "D") {
    return OGLTexture::Type::kDiffuse;
  } else if (type == "normal" || type == "N") {
    return OGLTexture::Type::kNormal;
  } else if (type == "specular" || type == "S") {
    return OGLTexture::Type::kSpecular;
  } else {
    // Else diffuse by default
    return OGLTexture::Type::kDiffuse;
  }
}
  
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

OGLTexture* OGLTextureManager::Add(const std::string& filename,
                                   const std::string& tex_id) {
  OGLTexture* tex = nullptr;
  std::string key, dir, file, ext;
  StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  // Check if ID is empty
  key = tex_id.empty() ? file : tex_id;
  // Already in it ?
  const auto it = texture_map_.find(key);
  if (it == texture_map_.end()) {
    // No, add it. First load image, if no isse create OGLTexture
    Image* img = ImageFactory::Get().CreateByExtension(ext);
    if (img) {
      int err = img->Load(filename);
      if (!err) {
        // Extrac type
        std::vector<std::string> parts;
        StringUtil::Split(file, "_", &parts);
        // Load texture
        OGLTexture::Type type;
        tex = new OGLTexture();
        type = ConvertTypeFromString(parts.back());
        err = tex->Upload(*img,
                          type,
                          this->wrapping_mode_,
                          this->interp_mode_);
        if (!err) {
          texture_map_.emplace(key, tex);
        } else {
          std::cout << "Error, can not upload texture" << std::endl;
          // CLean up
          delete tex;
          tex = nullptr;
        }
        // Clean up
        delete img;
      } else {
        std::cout << "Unable to open : " << filename << std::endl;
      }
    } else {
      std::cout << "Unknown extension type : " << ext << std::endl;
    }
  } else {
    tex = it->second;
  }
  return tex;
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
  
/*
 *  @name Remove
 *  @fn void Remove(const std::string& tex_id)
 *  @biref  Release specific textures
 *  @param[in]  tex_id  Texture ID to remove/release, if empty remove every
 *                      textures
 */
void OGLTextureManager::Remove(const std::string& tex_id) {
  if (tex_id.empty()) {
    // Release all texture
    for (auto it = texture_map_.begin(); it != texture_map_.end(); ++it) {
      delete it->second;
      it->second = nullptr;
    }
  } else {
    // Remove only specific texture
    auto it = texture_map_.find(tex_id);
    if (it != texture_map_.end()) {
      delete it->second;
      it->second = nullptr;
      texture_map_.erase(it);
    }
  }
}
  
#pragma mark -
#pragma mark Private
  
/*
 *  @name OGLTextureManager
 *  @fn OGLTextureManager(void)
 *  @brief  Constructor
 */
OGLTextureManager::OGLTextureManager(void) {
  wrapping_mode_ = OGLTexture::WrappingMode::kClampToBorder;
  interp_mode_ = OGLTexture::InterpolationMode::kLinear;
}
  
}  // namespace OGLKit
