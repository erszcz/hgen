#include <jni.h>
#include "../HeightmapCore.h"

#include <cstdio>

// to match the signatures expected by JVM
extern "C" {

JNIEXPORT jint JNICALL Java_CHeightmap_getHeight(JNIEnv *, jobject)
{
  printf("Astounding - it works!\n");
  return 0;
}

JNIEXPORT jint JNICALL Java_CHeightmap_getWidth(JNIEnv *, jobject)
{
  // stub
  return 0;
}

JNIEXPORT jint JNICALL Java_CHeightmap_getMargin
  (JNIEnv *, jobject)
{
  // stub
  return 0;
}

JNIEXPORT jdouble JNICALL Java_CHeightmap_getPixel
  (JNIEnv *, jobject, jint, jint)
{
  // stub
  return 0.0;
}

JNIEXPORT jdouble JNICALL Java_CHeightmap_getMax
  (JNIEnv *, jobject)
{
  // stub
  return 0.0;
}

JNIEXPORT jdouble JNICALL Java_CHeightmap_getMin
  (JNIEnv *, jobject)
{
  // stub
  return 0.0;
}

JNIEXPORT jboolean JNICALL Java_CHeightmap_setPixel
  (JNIEnv *, jobject, jint, jint, jdouble)
{
  // stub
  return false;
}

JNIEXPORT void JNICALL Java_CHeightmap_flatFill
  (JNIEnv *, jobject, jdouble)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_randomFill
  (JNIEnv *, jobject, jdouble, jdouble)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_clusterFill
  (JNIEnv *, jobject, jdouble, jdouble, jshort, jshort)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_clusterFilter
  (JNIEnv *, jobject, jint)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_alternateClusterFilter
  (JNIEnv *, jobject, jshort)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_liquidFilter
  (JNIEnv *, jobject, jdouble, jdouble, jdouble, jdouble, jboolean)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_smoothFilter
  (JNIEnv *, jobject, jshort, jboolean)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_terraceFilter(JNIEnv *, jobject, jshort)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_walkerFilter
  (JNIEnv *, jobject, jint, jint, jboolean)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_faultingFilter
  (JNIEnv *, jobject, jint, jint, jboolean)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_normalize__(JNIEnv *, jobject)
{
  // stub
  return;
}

JNIEXPORT void JNICALL Java_CHeightmap_normalize__DD
  (JNIEnv *, jobject, jdouble, jdouble)
{
  // stub
  return;
}

JNIEXPORT jboolean JNICALL Java_CHeightmap_hasMask(JNIEnv *, jobject)
{
  // stub
  return 0;
}

JNIEXPORT jlong JNICALL Java_CHeightmap_create
  (JNIEnv *, jobject, jint, jint, jint)
{
  // stub
  return 0L;
}

JNIEXPORT void JNICALL Java_CHeightmap_destroy(JNIEnv *, jobject, jlong)
{
  // stub
  return;
}

} // extern "C"
