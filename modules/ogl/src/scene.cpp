/**
 *  @file   scene.cpp
 *  @brief  High level abstraction representing the content of a scene. The
 *          scene stands for all what is displayed on the screen as well as all
 *          parameters needed to render it such as shaders, lights, camera
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   07.08.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#include <iostream>
#include <fstream>
#include <sstream>

#include "tinyxml2.h"

#include "oglkit/ogl/scene.hpp"
#include "oglkit/core/string_util.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
#pragma mark -
#pragma mark Prototype
  
/**
 *  @struct XMLReader
 *  @brief  Lightweight wrapper to pass xml structure to function
 */
struct XMLReader {
  
  /**
   *  @name XMLReader
   *  @fn explicit XMLReader(tinyxml2::XMLElement* root)
   *  @brief  Lightweight wrapper for xml reader
   *  @param[in]  root  Root element in xml file
   */
  explicit XMLReader(tinyxml2::XMLElement* root) {
    elem = root;
  }
  
  /**
   *  @name Value
   *  @fn static T Value(const tinyxml2::XMLElement* element)
   *  @brief  Read the value of a given element
   *  @param[in]  element XML element to read
   *  @return value
   */
  template<typename T>
  static T Value(const tinyxml2::XMLElement* element) {
    return T(-1.0);
  }
  
  /**
   *  @name Attribute
   *  @fn static T Attribute(const tinyxml2::XMLElement* element,
                             const std::string& name)
   *  @brief  Read an attribute from a given element
   *  @param[in]  element XML element to read
   *  @param[in]  name    Attribute's name
   *  @return value
   */
  template<typename T>
  static T Attribute(const tinyxml2::XMLElement* element,
                     const std::string& name) {
    return T(-1.0);
  }
  
  /** XML Document */
  tinyxml2::XMLElement* elem;
};
  
template<>
float XMLReader::Value<float>(const tinyxml2::XMLElement* element) {
  return element->FloatText();
}

template<>
double XMLReader::Value<double>(const tinyxml2::XMLElement* element) {
  return element->DoubleText();
}
  
template<>
float XMLReader::Attribute<float>(const tinyxml2::XMLElement* element,
                                  const std::string& name) {
  return element->FloatAttribute(name.c_str());
}

template<>
double XMLReader::Attribute<double>(const tinyxml2::XMLElement* element,
                                    const std::string& name) {
  return element->DoubleAttribute(name.c_str());
}
  
#pragma mark -
#pragma mark Initialization
  
/*
 *  @name OGLScene
 *  @fn OGLScene(void)
 *  @brief  Constructor
 */
template<typename T>
OGLScene<T>::OGLScene(void) {}
  
/*
 *  @name ~OGLScene
 *  @fn ~OGLScene(void)
 *  @brief  Destructor
 */
template<typename T>
OGLScene<T>::~OGLScene(void) {
  if (cam_) {
    delete cam_;
    cam_ = nullptr;
  }
}
  
/*
 *  @name   LoadFromFile
 *  @fn     int LoadFromFile(const std::string& filename)
 *  @brief  Load a scene from a given *.xml file
 *  @param[in] filename Path to a xml file
 *  @return -1 if error, 0 otherwise
 */
template<typename T>
int OGLScene<T>::LoadFromFile(const std::string& filename) {
  int err = -1;
  // Sanity check for extension, only support *.xml
  std::string dir, file, ext;
  StringUtil::ExtractDirectory(filename, &dir, &file, &ext);
  if (ext == "xml") {
    // Open
    std::ifstream in(filename.c_str());
    if (in.is_open()) {
      // Push data into buffer
      std::stringstream buffer;
      buffer << in.rdbuf();
      // Load scene
      err = this->LoadFromString(buffer.str());
    } else {
      std::cout << "Unable to open file : " << filename << std::endl;
    }
  } else {
    std::cout << "File extension not supported" << std::endl;
  }
  return err;
}
  
/*
 *  @name   LoadFromString
 *  @fn     int LoadFromString(const std::string& scene_str)
 *  @brief  Load a scene from a given string. Internally parse it and
 *          construct the scene
 *  @param[in] scene_str  String holding scene description in xml format.
 *  @return -1 if error, 0 otherwise
 */
template<typename T>
int OGLScene<T>::LoadFromString(const std::string& scene_str) {
  int err = -1;
  // Sanity check
  if (!scene_str.empty()) {
    // Create XML documents
    tinyxml2::XMLDocument doc;
    if (doc.Parse(scene_str.c_str()) == tinyxml2::XMLError::XML_SUCCESS) {
      // Get root
      auto* root = doc.FirstChildElement("Scene");
      // Load camera
      XMLReader reader(root);
      cam_ = this->CreateCamera(&reader);
      
      // Load transforms
      
      
      
      
    } else {
      std::cout << "Not a valid XML String" << std::endl;
    }
  } else {
    std::cout << "Can not load scene from empty String" << std::endl;
  }
  return err;
}
  
#pragma mark -
#pragma mark Usage
  
  
#pragma mark -
#pragma mark Private
  
/**
 *  @name CreateCamera
 *  @fn OGLCamera<T>* CreateCamera(const XMLReader* reader)
 *  @brief  Construct a camera object from scene file.
 *  @param[in]  reader  Document reader
 *  @return Newly created camera, or nullptr if something went wrong.
 */
template<typename T>
OGLCamera<T>* OGLScene<T>::CreateCamera(const XMLReader* reader) const {
  OGLCamera<T>* cam = nullptr;
  auto* elem = reader->elem->FirstChildElement("Camera");
  if (elem) {
    auto* elem_pos = elem->FirstChildElement("Position");
    auto* elem_tar = elem->FirstChildElement("Target");
    auto* elem_param = elem->FirstChildElement("Parameters");
    if (elem_pos && elem_tar && elem_param) {
      // Read position
      T x = XMLReader::Attribute<T>(elem_pos, "x");
      T y = XMLReader::Attribute<T>(elem_pos, "y");
      T z = XMLReader::Attribute<T>(elem_pos, "z");
      Vec3 pos(x, y, z);
      // Read target
      x = XMLReader::Attribute<T>(elem_tar, "x");
      y = XMLReader::Attribute<T>(elem_tar, "y");
      z = XMLReader::Attribute<T>(elem_tar, "z");
      Vec3 target(x, y, z);
      // Create camera instance
      cam = new OGLCamera<T>(pos, target);
      // Extra parameters
      T fov = XMLReader::Value<T>(elem_param->FirstChildElement("Fov"));
      T near = XMLReader::Value<T>(elem_param->FirstChildElement("Near"));
      T far = XMLReader::Value<T>(elem_param->FirstChildElement("Far"));
      T aspect = XMLReader::Value<T>(elem_param->FirstChildElement("Aspect"));
      cam->UpdateProjectionTransform(fov, near, far, aspect);
    } else {
      std::cout << "Missing camera parameters" << std::endl;
    }
  }
  return cam;
}
  
#pragma mark -
#pragma mark Explicit instantiation
  
/** Float - Scene */
template class OGLScene<float>;
/** Double - Scene */
template class OGLScene<double>;
  
}  // namespace OGLKit
