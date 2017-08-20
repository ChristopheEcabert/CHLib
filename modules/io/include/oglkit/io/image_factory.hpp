/**
 *  @file   image_factory.hpp
 *  @brief  Helper class to create images
 *  @ingroup io
 *
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  Copyright © 2017 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_IMAGE_FACOTRY__
#define __OGLKIT_IMAGE_FACOTRY__

#include <unordered_set>

#include "oglkit/core/library_export.hpp"
#include "oglkit/io/image.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
/**
 *  @class  ImageLoader
 *  @brief  Singleton helper for image create. New image type can be added with 
 *          registration mechanism
 *  @author Christophe Ecabert
 *  @date   11.03.17
 *  @ingroup io
 *  @see http://www.drdobbs.com/cpp/self-registering-objects-in-c/184410633
 */
class OGLKIT_EXPORTS ImageFactory {
 
public:
  
  /**
   *  @name Get
   *  @fn static ImageFactory& Get(void)
   *  @brief  Provide access to single instance of ImageFactory
   */
  static ImageFactory& Get(void);
  
  /**
   *  @name   ~ImageFactory
   *  @fn     ~ImageFactory(void)
   *  @brief  Destructor
   */
  ~ImageFactory(void);
  
  /**
   *  @name   ImageFactory
   *  @fn     ImageFactory(const ImageFactory& other) = delete;
   *  @brief  Copy constructor
   *  @param[in] other  Object to copy from
   */
  ImageFactory(const ImageFactory& other) = delete;
  
  /**
   *  @name operator=
   *  @fn ImageFactory& operator=(const ImageFactory& rhs) = delete
   *  @brief  Assignment operator
   *  @param[in]  rhs Object to assign from
   *  @return Newly assigned operator
   */
  ImageFactory& operator=(const ImageFactory& rhs) = delete;
  
  /** 
   *  @name CreateByExtension
   *  @fn Image* CreateByExtension(const std::string& extension)
   *  @brief  Create an image based on the extension type
   *  @param[in]  extension  Image extension (type)
   *  @return Pointer to an instance of the given type, nullptr if type is 
   *  unknown
   */
  Image* CreateByExtension(const std::string& extension);
  
  /**
   *  @name Register
   *  @fn void Register(const ImageProxy* object)
   *  @brief  Register a type of image with a given proxy.
   *  @param[in]  object  Object to register
   */
  void Register(const ImageProxy* object);
  
 private:
  
  /**
   *  @name   ImageFactory
   *  @fn     ImageFactory(void)
   *  @brief  Constructor
   */
  ImageFactory(void);
  
  /** List of all unique registered image's proxies */
  std::unordered_set<const ImageProxy*> proxies_;
};
}  // namespace OGLKit

#endif /* __OGLKIT_IMAGE_FACOTRY__ */
