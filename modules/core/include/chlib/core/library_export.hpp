/**
 *  @file   library_export.hpp
 *  @brief
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_LIBRARY_EXPORT__
#define __CHLIB_LIBRARY_EXPORT__

#if (defined WIN32 || defined _WIN32 || defined WINCE)
  #define FUNC_NAME __FUNCTION__
  #if defined CHLIB_API_EXPORTS
    #define CHLIB_EXPORTS __declspec(dllexport)
    #if _MSC_VER && !__INTEL_COMPILER
      /* disable unknown pragma warnings */
      #pragma warning (disable : 4068 )
    #endif
  #else
    #define LTS5_EXPORTS __declspec(dllimport)
  #endif
#else
  #define CHLIB_EXPORTS
  #define FUNC_NAME __PRETTY_FUNCTION__
#endif

#endif /* __CHLIB_LIBRARY_EXPORT__ */
