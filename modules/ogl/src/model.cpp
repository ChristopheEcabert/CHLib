/**
 *  @file   model.cpp
 *  @brief  3D Model
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <stack>
#include <assert.h>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "oglkit/core/string_util.hpp"
#include "oglkit/ogl/model.hpp"
#include "oglkit/ogl/texture_manager.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name   OGLModel
 *  @fn     OGLModel(void)
 *  @brief  Constructor
 */
template<typename T>
OGLModel<T>::OGLModel(void) {
  
}

/*
 *  @name   ~OGLModel
 *  @fn     ~OGLModel(void)
 *  @brief  Destructor
 */
template<typename T>
OGLModel<T>::~OGLModel(void) {
  for (size_t i = 0; i < meshes_.size(); ++i) {
    delete meshes_[i];
    meshes_[i] = nullptr;
  }
}

/*
 *  @name
 *  @fn
 *  @brief  Load model into memory
 *  @param[in]  filename  Path to the model
 *  @return -1 if error, 0 otherwise
 */
template<typename T>
int OGLModel<T>::Load(const std::string& filename) {
  int err = -1;
  // Recover folder
  std::string file, ext;
  StringUtil::ExtractDirectory(filename, &directory_, &file, &ext);
  // Load scene
  auto flag = aiProcess_Triangulate | aiProcess_FlipUVs;
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(filename.c_str(), flag);
  if (scene &&
      scene->mFlags != AI_SCENE_FLAGS_INCOMPLETE &&
      scene->mRootNode) {
    // Scene loaded, convert to our format
    err = this->ProcessScene(*scene);
  } else {
    std::cout << "Unable to load : " << filename << std::endl;
    std::cout << "Assimp:: " << importer.GetErrorString() << std::endl;
  }
  return err;
}
  
#pragma mark -
#pragma mark Usage

/*
 *  @name Render
 *  @fn void Render(const OGLShader& shader)
 *  @brief  Render the model
 *  @param[in]  shader  Shader to use while drawing
 */
template<typename T>
void OGLModel<T>::Render(const OGLShader& shader) {
  for (size_t i = 0; i < meshes_.size(); ++i) {
    meshes_[i]->Render(shader);
  }
}
  
#pragma mark -
#pragma mark Private
  
/*
 *  @name ProcessScene
 *  @fn void ProcessScene(const aiScene& scene)
 *  @brief  Process Assimp scene and convert to OGLModel format
 *  @param[in]  scene Scene to process
 */
template<typename T>
int OGLModel<T>::ProcessScene(const aiScene& scene) {
  using Vertex = typename OGLKit::OGLMesh<T>::Vertex;
  using Normal = typename OGLKit::OGLMesh<T>::Normal;
  using TCoord = typename OGLKit::OGLMesh<T>::TCoord;
  using Triangle = typename OGLKit::OGLMesh<T>::Triangle;
  // Avoid recursion by using stack
  int err = 0;
  std::stack<aiNode*> queue;
  queue.push(scene.mRootNode);
  // Loop
  while (!queue.empty()) {
    aiNode* node = queue.top();
    queue.pop();
    // Process each mesh of this node
    for (int i = 0; i < node->mNumMeshes; ++i) {
      // Query mesh
      aiMesh* mesh = scene.mMeshes[node->mMeshes[i]];
      // Add new mesh
      auto* m = new OGLMesh();
      meshes_.push_back(m);
      // Process Vertex + Normal + Tex Coord
      auto& vertex = m->get_vertex();
      auto& normal = m->get_normal();
      auto& tcoord = m->get_tex_coord();
      vertex.reserve(mesh->mNumVertices);
      normal.reserve(mesh->mNumVertices);
      tcoord.reserve(mesh->mNumVertices);
      for (int k = 0; k < mesh->mNumVertices; ++k) {
        // Vertex
        Vertex vert;
        vert.x_ = mesh->mVertices[k].x;
        vert.y_ = mesh->mVertices[k].y;
        vert.z_ = mesh->mVertices[k].z;
        vertex.push_back(vert);
        // Normal
        Normal n;
        n.x_ = mesh->mNormals[k].x;
        n.y_ = mesh->mNormals[k].y;
        n.z_ = mesh->mNormals[k].z;
        normal.push_back(n);
        // Tex Coord
        if (mesh->mTextureCoords[0]) {
          TCoord tc;
          tc.x_ = mesh->mTextureCoords[0][k].x;
          tc.y_ = mesh->mTextureCoords[0][k].y;
          tcoord.push_back(tc);
        }
      }
      // Process triangle
      auto& tri = m->get_triangle();
      for (int i = 0; i < mesh->mNumFaces; ++i) {
        aiFace face = mesh->mFaces[i];
        // Retrieve all indices of the face and store them in the indices vector
        assert(face.mNumIndices % 3 == 0);
        for(int j = 0; j < face.mNumIndices; j += 3) {
          Triangle t;
          t.x_ = face.mIndices[j];
          t.y_ = face.mIndices[j + 1];
          t.z_ = face.mIndices[j + 2];
          tri.push_back(t);
        }
      }
      // Process Material
      auto& texture = m->get_texture();
      if (mesh->mMaterialIndex > 0) {
        // Process texture
        auto& tex_manager = OGLTextureManager::Instance();
        std::vector<aiTextureType> types = {aiTextureType_DIFFUSE,
                                            aiTextureType_SPECULAR,
                                            aiTextureType_HEIGHT};
        aiMaterial* material = scene.mMaterials[mesh->mMaterialIndex];
        // Loop over types
        for (size_t t = 0; t < types.size(); ++t) {
          for (int i = 0; i < material->GetTextureCount(types[t]); ++i) {
            aiString str;
            material->GetTexture(types[t], i, &str);
            std::string path = directory_ + std::string(str.C_Str());
            OGLTexture* tex = tex_manager.Add(path, "");
            if (tex) {
              texture.push_back(tex);
            } else {
              err |= -1;
              std::cout << path << std::endl;
            }
          }
        }
      }
      // Init opengl for this mesh
      err |= m->InitOpenGLContext();
    }    
    // Push childrens
    for (int i = 0; i < node->mNumChildren; ++i) {
      queue.push(node->mChildren[i]);
    }
  }
  return err;
}
  
#pragma mark -
#pragma mark Instance
  
/** Float */
template class OGLModel<float>;
/** Double */
template class OGLModel<double>;

}  // namespace OGLKit
