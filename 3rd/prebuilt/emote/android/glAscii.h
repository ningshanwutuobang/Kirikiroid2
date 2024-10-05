//
// ◇ UTF-8
// $Id$
//


#ifndef __GLASCII_H__
#define __GLASCII_H__

#if defined(_WIN32) && !defined(NN_NINTENDO_SDK)
#if defined(EMOTE_EXPORTS)
#define _EXPORT __declspec(dllexport)
#else // defined(EMOTE_EXPORTS)
#if defined(EMOTE_STATIC_LIBRARY) || defined(EMOTE_STATIC) || defined(MOTION_DRIVER_STAND_ALONE) || !defined(__EMOTE_DRIVER_H)
#define _EXPORT
#else // defined(EMOTE_STATIC_LIBRARY) || defined(EMOTE_STATIC) || defined(MOTION_DRIVER_STAND_ALONE) || !defined(__EMOTE_DRIVER_H)
#define _EXPORT __declspec(dllimport)
#endif // defined(EMOTE_STATIC_LIBRARY) || defined(EMOTE_STATIC) || defined(MOTION_DRIVER_STAND_ALONE) || !defined(__EMOTE_DRIVER_H)
#endif // EMOTE_EXPORTS
#else // _WIN32
#define _EXPORT
#endif // _WIN32

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

extern int _EXPORT glAsciiInitialize(int screenWidth, int screenHeight);
extern int _EXPORT glAsciiFinalize(void);
extern int _EXPORT glAsciiPutString(float posx, float posy, float scale, const char *str);
extern int _EXPORT glAsciiPrintf(float posx, float posy, float scale, const char *format, ...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif  // __GLASCII_H__
