/**
 *  @file   error.hpp
 *  @brief  Error class
 *
 *  @author Christophe Ecabert
 *  @date   02/08/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_ERROR__
#define __CHLIB_ERROR__

#include <exception>
#include <string>

#include "chlib/core/library_export.hpp"

/**
 *  @namespace  CHLib
 *  @brief      Chris dev space
 */
namespace CHLib {

/**
 *  @class  CHError
 *  @brief  Error class
 *  @author Christophe Ecabert
 *  @date   02/08/16
 */
class CHLIB_EXPORTS CHError : public std::exception {

 public:

#pragma mark -
#pragma mark Type definition

  /**
   *  @enum Type
   *  @brief  Type of error
   */
  enum Type {
    /** Generic */
    kGeneric = -1,
    /** Opening file */
    kFileOpening = -2,
    /** Reading data */
    kReadingData = -3
  };

#pragma mark -
#pragma mark Initialization

  /**
   *  @name CHError
   *  @fn CHError(void)
   *  @brief  Constructor
   */
  CHError(void);

  /**
   *  @name CHError
   *  @fn CHError(const Type err_code, 
                  const std::string& message,
                  const std::string& function_name)
   *  @brief  Constructor
   *  @param[in]  err_code      Error code
   *  @param[in]  message       Error message
   *  @param[in]  function_name Name of the function that trigger the exception
   */
  CHError(const Type err_code,
          const std::string& message,
          const std::string& function_name);

  /**
   *  @name ~CHError
   *  @fn virtual ~CHError(void) throw()
   *  @brief  Destructor
   */
  virtual ~CHError(void) throw();

#pragma mark -
#pragma mark Usage

  /**
   *  @name   what
   *  @fn virtual const char *what() const throw()
   *  @brief  Return description and context of the error
   */
  virtual const char* what() const throw();

#pragma mark -
#pragma mark Protected

 protected:
  /** Error message */
  std::string msg_;
};

}  // namespace CHLib
#endif /* __CHLIB_ERROR__ */
