/**
 *  @file   error.cpp
 *  @brief  Error class
 *
 *  @author Christophe Ecabert
 *  @date   02/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#include "oglkit/core/error.hpp"

/**
 *  @namespace  OGLKit
 *  @brief      Chris dev space
 */
namespace OGLKit {

#pragma mark -
#pragma mark Initialization

/*
 *  @name CHError
 *  @fn CHError(void)
 *  @brief  Constructor
 */
CHError::CHError(void) : msg_("") {
}

/*
 *  @name CHError
 *  @fn CHError(const Type err_code,
                const std::string& message,
                const std::string& function_name)
 *  @brief  Constructor
 *  @param[in]  err_code      Error code
 *  @param[in]  message       Error message
 *  @param[in]  function_name Name of the function that trigger the exception
 */
CHError::CHError(const Type err_code,
                 const std::string& message,
                 const std::string& function_name) {
  msg_ = function_name + " gives error : " + std::to_string(err_code) +
         " with the following message : " + message;
}

/*
 *  @name ~CHError
 *  @fn virtual ~CHError(void) throw()
 *  @brief  Destructor
 */
CHError::~CHError(void) throw() {
}

#pragma mark -
#pragma mark Usage

/*
*  @name   what
*  @fn virtual const char *what() const throw()
*  @brief  Return description and context of the error
*/
const char* CHError::what() const throw() {
  return msg_.c_str();
}

}  // namespace OGLKit
