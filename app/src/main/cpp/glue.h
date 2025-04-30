
#pragma once

#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL
Java_another_tiny_1render_TinyRender_nativeInit(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL nativeOnStart(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL nativeOnResume(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL nativeOnPause(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL nativeOnStop(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL nativeSetSurface(JNIEnv *jenv, jobject obj, jobject surface);
}