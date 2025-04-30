
#pragma once

#include <jni.h>

extern "C" {
JNIEXPORT void JNICALL Java_nativeActivity_Render_nativeOnStart(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL Java_nativeActivity_Render_nativeOnResume(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL Java_nativeActivity_Render_nativeOnPause(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL Java_nativeActivity_Render_nativeOnStop(JNIEnv *jenv, jobject obj);

JNIEXPORT void JNICALL
Java_nativeActivity_Render_nativeSetSurface(JNIEnv *jenv, jobject obj, jobject surface);
}