/**
 *  @file   string_util.hpp
 *  @brief  Utility function for string handling
 *  @ingroup core
 *
 *  @author Christophe Ecabert
 *  @date   26/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_STRING_UTIL__
#define __OGLKIT_STRING_UTIL__

#include <string>
#include <vector>

#include "oglkit/core/library_export.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      OpenGL development space
 */
namespace OGLKit {
  
/**
 *  @class  StringUtil
 *  @brief  Utility function for string handling
 *  @author Christophe Ecabert
 *  @date   26/08/16
 *  @ingroup core
 */
class OGLKIT_EXPORTS StringUtil {
 public:
  
  /**
   *  @name Split
   *  @fn static void Split(const std::string& string,
                           const std::string delimiter,
                           std::vector<std::string>* parts);
   *  @brief  Split a given \p string into parts for a specific delimiter
   *  @param[in]  string    String to split
   *  @param[in]  delimiter Delimiter
   *  @param[out] parts     Splitted parts
   */
  static void Split(const std::string& string,
                    const std::string delimiter,
                    std::vector<std::string>* parts);
  
  /**
   *  @name ExtractDirectory
   *  @fn static void ExtractDirectory(const std::string& path,
                                       std::string* dir,
                                       std::string* file,
                                       std::string* ext)
   *  @brief  Split path into directory + extension
   *  @param[in]  path  Path where to extract data
   *  @param[out] dir   Extracted directory
   *  @param[out] file  Extracted filename
   *  @param[out] ext   Extracted extension
   */
  static void ExtractDirectory(const std::string& path,
                               std::string* dir,
                               std::string* file,
                               std::string* ext);
};
  
}  // namespace OGLKit


#endif /* __OGLKIT_STRING_UTIL__ */
