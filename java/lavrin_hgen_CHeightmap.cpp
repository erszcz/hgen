#include <jni.h>
#include <new>
#include "../HeightmapCore.h"

#include <cstdio>

jfieldID FID_CHeightmap_peer;

HeightmapCore* self2hmap(JNIEnv * env, jobject self)
{
  return (HeightmapCore*)(env->GetLongField(self, FID_CHeightmap_peer));
}

// to match the signatures expected by JVM
extern "C" {

JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getHeight
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->getHeight();
}

JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getWidth
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->getWidth();
}

JNIEXPORT jint JNICALL Java_lavrin_hgen_CHeightmap_getMargin
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->getMargin();
}

JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getPixel
  (JNIEnv * env, jobject self, jint x, jint y)
{
  return self2hmap(env, self)->getPixel(x, y);
}

JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getMax
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->getMax();
}

JNIEXPORT jfloat JNICALL Java_lavrin_hgen_CHeightmap_getMin
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->getMin();
}

JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_setPixel
  (JNIEnv * env, jobject self, jint x, jint y, jfloat val)
{
  return self2hmap(env, self)->setPixel(x, y, val);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_flatFill
  (JNIEnv * env, jobject self, jfloat val)
{
  self2hmap(env, self)->flatFill(val);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_randomFill
  (JNIEnv * env, jobject self, jfloat min, jfloat max)
{
  self2hmap(env, self)->randomFill(min, max);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_clusterFill
  (JNIEnv * env, jobject self,
   jfloat min, jfloat max, jint clusterChance, jint radius)
{
  self2hmap(env, self)->clusterFill(min, max, clusterChance, radius);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_clusterFilter
  (JNIEnv * env, jobject self, jint radius)
{
  self2hmap(env, self)->clusterFilter(radius);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_alternateClusterFilter
  (JNIEnv * env, jobject self, jint radius)
{
  self2hmap(env, self)->alternateClusterFilter(radius);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_liquidFilter
  (JNIEnv * env, jobject self,
   jfloat c, jfloat d, jfloat t, jfloat u, jboolean wrap)
{
  self2hmap(env, self)->liquidFilter(c, d, t, u, wrap);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_smoothFilter
  (JNIEnv * env, jobject self, jint radius, jboolean wrap)
{
  self2hmap(env, self)->smoothFilter(radius, wrap);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_terraceFilter
  (JNIEnv * env, jobject self, jint levels)
{
  self2hmap(env, self)->terraceFilter(levels);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_walkerFilter
  (JNIEnv * env, jobject self, jint inc, jint dec, jboolean wrap)
{
  self2hmap(env, self)->walkerFilter(inc, dec, wrap);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_faultingFilter
  (JNIEnv * env, jobject self, jint inc, jint dec, jboolean wrap)
{
  self2hmap(env, self)->faultingFilter(inc, dec, wrap);
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_normalize__
  (JNIEnv * env, jobject self)
{
  self2hmap(env, self)->normalize();
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_normalize__FF
  (JNIEnv * env, jobject self, jfloat max, jfloat min)
{
  self2hmap(env, self)->normalize(max, min);
}

JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_isMasked
  (JNIEnv * env, jobject self)
{
  return self2hmap(env, self)->hasMask();
}

JNIEXPORT jboolean JNICALL Java_lavrin_hgen_CHeightmap_initIDs(JNIEnv * env, jclass cls)
{
  if ( NULL == (FID_CHeightmap_peer = env->GetFieldID(cls, "_peer", "J")) )
    return false;
  return true;
}


JNIEXPORT jlong JNICALL Java_lavrin_hgen_CHeightmap_create
  (JNIEnv * env, jobject self, jint height, jint width, jint margin)
{
  return (jlong)(new(std::nothrow) HeightmapCore(height, width, margin));
}

JNIEXPORT void JNICALL Java_lavrin_hgen_CHeightmap_destroy
  (JNIEnv * env, jobject self, jlong peer)
{
  delete (HeightmapCore*)peer;
}

JNIEXPORT jlong JNICALL Java_lavrin_hgen_CHeightmap_peerCopy
  (JNIEnv * env, jobject self, jlong peer)
{
  HeightmapCore* orig = (HeightmapCore*)peer;
  return (jlong)(new(std::nothrow) HeightmapCore(*orig));
}

} // extern "C"
