/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class lavrin_hgen_CHeightmap */

#ifndef _Included_lavrin_hgen_CHeightmap
#define _Included_lavrin_hgen_CHeightmap
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getHeight
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getHeight
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getWidth
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getWidth
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getMargin
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getMargin
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getPixel
 * Signature: (II)F
 */
JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getPixel
  (JNIEnv *, jobject, jint, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getMax
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getMax
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    getMin
 * Signature: ()F
 */
JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getMin
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    setPixel
 * Signature: (IIF)Z
 */
JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_setPixel
  (JNIEnv *, jobject, jint, jint, jfloat);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    flatFill
 * Signature: (F)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_flatFill
  (JNIEnv *, jobject, jfloat);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    randomFill
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_randomFill
  (JNIEnv *, jobject, jfloat, jfloat);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    clusterFill
 * Signature: (FFII)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_clusterFill
  (JNIEnv *, jobject, jfloat, jfloat, jint, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    clusterFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_clusterFilter
  (JNIEnv *, jobject, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    alternateClusterFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_alternateClusterFilter
  (JNIEnv *, jobject, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    liquidFilter
 * Signature: (FFFFZ)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_liquidFilter
  (JNIEnv *, jobject, jfloat, jfloat, jfloat, jfloat, jboolean);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    smoothFilter
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_smoothFilter
  (JNIEnv *, jobject, jint, jboolean);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    terraceFilter
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_terraceFilter
  (JNIEnv *, jobject, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    walkerFilter
 * Signature: (IIZ)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_walkerFilter
  (JNIEnv *, jobject, jint, jint, jboolean);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    faultingFilter
 * Signature: (IIZ)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_faultingFilter
  (JNIEnv *, jobject, jint, jint, jboolean);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    normalize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_normalize__
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    normalize
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_normalize__FF
  (JNIEnv *, jobject, jfloat, jfloat);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    isMasked
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_isMasked
  (JNIEnv *, jobject);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    initIDs
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_initIDs
  (JNIEnv *, jclass);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    create
 * Signature: (III)J
 */
JNIEXPORT jlong JNICALL Java_lavrin_hgen_CHeightmap_create
  (JNIEnv *, jobject, jint, jint, jint);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    destroy
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_destroy
  (JNIEnv *, jobject, jlong);

/*
 * Class:     lavrin_hgen_CHeightmap
 * Method:    peerCopy
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_lavrin_hgen_CHeightmap_peerCopy
  (JNIEnv *, jobject, jlong);

#ifdef __cplusplus
}
#endif
#endif
