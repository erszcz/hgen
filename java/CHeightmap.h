/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class CHeightmap */

#ifndef _Included_CHeightmap
#define _Included_CHeightmap
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     CHeightmap
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_CHeightmap_getHeight
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_CHeightmap_getWidth
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    getMargin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_CHeightmap_getMargin
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    getPixel
 * Signature: (II)D
 */
JNIEXPORT jdouble JNICALL Java_CHeightmap_getPixel
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     CHeightmap
 * Method:    getMax
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_CHeightmap_getMax
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    getMin
 * Signature: ()D
 */
JNIEXPORT jdouble JNICALL Java_CHeightmap_getMin
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    setPixel
 * Signature: (IID)Z
 */
JNIEXPORT jboolean JNICALL Java_CHeightmap_setPixel
  (JNIEnv *, jobject, jint, jint, jdouble);

/*
 * Class:     CHeightmap
 * Method:    flatFill
 * Signature: (D)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_flatFill
  (JNIEnv *, jobject, jdouble);

/*
 * Class:     CHeightmap
 * Method:    randomFill
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_randomFill
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     CHeightmap
 * Method:    clusterFill
 * Signature: (DDSS)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_clusterFill
  (JNIEnv *, jobject, jdouble, jdouble, jshort, jshort);

/*
 * Class:     CHeightmap
 * Method:    clusterFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_clusterFilter
  (JNIEnv *, jobject, jint);

/*
 * Class:     CHeightmap
 * Method:    alternateClusterFilter
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_alternateClusterFilter
  (JNIEnv *, jobject, jshort);

/*
 * Class:     CHeightmap
 * Method:    liquidFilter
 * Signature: (DDDDZ)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_liquidFilter
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jboolean);

/*
 * Class:     CHeightmap
 * Method:    smoothFilter
 * Signature: (SZ)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_smoothFilter
  (JNIEnv *, jobject, jshort, jboolean);

/*
 * Class:     CHeightmap
 * Method:    terraceFilter
 * Signature: (S)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_terraceFilter
  (JNIEnv *, jobject, jshort);

/*
 * Class:     CHeightmap
 * Method:    walkerFilter
 * Signature: (IIZ)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_walkerFilter
  (JNIEnv *, jobject, jint, jint, jboolean);

/*
 * Class:     CHeightmap
 * Method:    faultingFilter
 * Signature: (IIZ)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_faultingFilter
  (JNIEnv *, jobject, jint, jint, jboolean);

/*
 * Class:     CHeightmap
 * Method:    normalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_CHeightmap_normalize__
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    normalize
 * Signature: (DD)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_normalize__DD
  (JNIEnv *, jobject, jdouble, jdouble);

/*
 * Class:     CHeightmap
 * Method:    hasMask
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_CHeightmap_hasMask
  (JNIEnv *, jobject);

/*
 * Class:     CHeightmap
 * Method:    create
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL Java_CHeightmap_create
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     CHeightmap
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_CHeightmap_destroy
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
