/**
 *  @file   library_export.hpp
 *  @brief  Export macro for dll
 *  @ingroup core
 *
 *  @author Christophe Ecabert
 *  @date   30/07/16
 *  Copyright © 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __OGLKIT_LIBRARY_EXPORT__
#define __OGLKIT_LIBRARY_EXPORT__

#if (defined WIN32 || defined _WIN32 || defined WINCE)
  #define FUNC_NAME __FUNCTION__
  #if defined OGLKIT_API_EXPORTS
    #define OGLKIT_EXPORTS __declspec(dllexport)
    #if _MSC_VER && !__INTEL_COMPILER
      /* disable unknown pragma warnings */
      #pragma warning (disable : 4068 )
    #endif
  #else
    #define OGLKIT_EXPORTS __declspec(dllimport)
  #endif
#else
  #define OGLKIT_EXPORTS
  #define FUNC_NAME __PRETTY_FUNCTION__
#endif

#endif /* __OGLKIT_LIBRARY_EXPORT__ */
