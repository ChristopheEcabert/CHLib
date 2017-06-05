/**
 *  @file   key_types.hpp
 *  @brief  Generic key definition for abstract layer.
 *          Based on : http://ogldev.atspace.co.uk/
 *  @ingroup ogl
 *
 *  @author Christophe Ecabert
 *  @date   16/08/16
 *  Copyright (c) 2016 Christophe Ecabert. All rights reserved.
 */

#ifndef __CHLIB_KEY_TYPES__
#define __CHLIB_KEY_TYPES__

#include "chlib/core/library_export.hpp"

/**
 *  @namespace  CHLib
 *  @brief      CHLib dev space
 */
namespace CHLib {

/**
 *  @enum OGLKey
 *  @brief Define different keyboard's key
 *  @ingroup ogl
 */
enum OGLKey {
  /** Space */
  kSPACE =             32,
  /** Apostrophe */
  kAPOSTROPHE =        39,
  /** Plus sign */
  kPLUS =              43,
  /** Comma */
  kCOMMA =             44,
  /** Minus sign */
  kMINUS =             45,
  /** Period */
  kPERIOD =            46,
  /** Slash */
  kSLASH =             47,
  /** Zero */
  k0 =                 48,
  /** One */
  k1 =                 49,
  /** Two */
  k2 =                 50,
  /** Three */
  k3 =                 51,
  /** Four */
  k4 =                 52,
  /** Five */
  k5 =                 53,
  /** Six */
  k6 =                 54,
  /** Seven */
  k7 =                 55,
  /** Eight */
  k8 =                 56,
  /** Nine */
  k9 =                 57,
  /** Semicolon */
  kSEMICOLON =         58,
  /** Equal sign */
  kEQUAL =             61,
  /** A */
  kA =                 65,
  /** B */
  kB =                 66,
  /** C */
  kC =                 67,
  /** D */
  kD =                 68,
  /** E */
  kE =                 69,
  /** F */
  kF =                 70,
  /** G */
  kG =                 71,
  /** H */
  kH =                 72,
  /** I */
  kI =                 73,
  /** J */
  kJ =                 74,
  /** K */
  kK =                 75,
  /** L */
  kL =                 76,
  /** M */
  kM =                 77,
  /** N */
  kN =                 78,
  /** O */
  kO =                 79,
  /** P */
  kP =                 80,
  /** Q */
  kQ =                 81,
  /** R */
  kR =                 82,
  /** S */
  kS =                 83,
  /** T */
  kT =                 84,
  /** U */
  kU =                 85,
  /** V */
  kV =                 86,
  /** W */
  kW =                 87,
  /** X */
  kX =                 88,
  /** Y */
  kY =                 89,
  /** Z */
  kZ =                 90,
  /** Left bracket */
  kLEFT_BRACKET =      91,
  /** Backslash */
  kBACKSLASH =         92,
  /** Right bracket */
  kRIGHT_BRACKET =     93,
  /** a */
  ka =                 97,
  /** b */
  kb =                 98,
  /** c */
  kc =                 99,
  /** d */
  kd =                 100,
  /** e */
  ke =                 101,
  /** f */
  kf =                 102,
  /** g */
  kg =                 103,
  /** h */
  kh =                 104,
  /** i */
  ki =                 105,
  /** j */
  kj =                 106,
  /** k */
  kk =                 107,
  /** l */
  kl =                 108,
  /** m */
  km =                 109,
  /** n */
  kn =                 110,
  /** o */
  ko =                 111,
  /** p */
  kp =                 112,
  /** q */
  kq =                 113,
  /** r */
  kr =                 114,
  /** s */
  ks =                 115,
  /** t */
  kt =                 116,
  /** u */
  ku =                 117,
  /** v */
  kv =                 118,
  /** w */
  kw =                 119,
  /** x */
  kx =                 120,
  /** y */
  ky =                 121,
  /** z */
  kz =                 122,
  /** Escape */
  kESCAPE,
  /** Enter */
  kENTER,
  /** Tab */
  kTAB,
  /** Backspace */
  kBACKSPACE,
  /** Insert */
  kINSERT,
  /** Delete*/
  kDELETE,
  /** Right */
  kRIGHT,
  /** Left */
  kLEFT,
  /** Down */
  kDOWN,
  /** Up */
  kUP,
  /** Page up */
  kPAGE_UP,
  /** Page down*/
  kPAGE_DOWN,
  /** Home */
  kHOME,
  /** End */
  kEND,
  /** F1 */
  kF1,
  /** F2 */
  kF2,
  /** F3 */
  kF3,
  /** F4 */
  kF4,
  /** F5 */
  kF5,
  /** F6 */
  kF6,
  /** F7 */
  kF7,
  /** F8 */
  kF8,
  /** F9 */
  kF9,
  /** F10 */
  kF10,
  /** F11 */
  kF11,
  /** F12 */
  kF12,
  /** Undefined */
  kUNDEFINED = 999
};

/**
 *  @enum OGLMouse
 *  @brief Define different mouse event type
 *  @ingroup ogl
 */
enum OGLMouse {
  /** Mouse left button */
  kMouseLeft,
  /** Mouse right button */
  kMouseRight,
  /** Mouse midlle button */
  kMouseMiddle,
  /** Mouse undefined event */
  kUndefined = 999
};

/**
 *  @enum OGLKeyState
 *  @brief Define all possible key state
 *  @ingroup ogl
 */
enum OGLKeyState {
  /** Key was pressed */
  kPress,
  /** Key was released */
  kRelease
};

}

#endif //__CHLIB_KEY_TYPES__
