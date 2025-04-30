
#include <memory>

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "glue.h"
#include "log/log.h"
#include "render/render.h"
#include "render/vk/rendervk.h"

extern "C" {

static ANativeWindow *window = nullptr;
static tire::RenderVK *renderer = nullptr;

static jobject gClassLoader;
static jmethodID gFindClassMethod;

void testCallNonStaticMethod(struct android_app *pApp);
void testCallNonStaticArgInt(struct android_app *pApp);

// TestLibrary::NonStaticMethod()
void testCallNonStaticMethod(struct android_app *pApp) {
    JavaVM *vmHandle = pApp->activity->vm;
    JNIEnv *jniEnv = pApp->activity->env;

    JavaVMAttachArgs lJavaVMAttachArgs;
    lJavaVMAttachArgs.version = JNI_VERSION_1_6;
    lJavaVMAttachArgs.name = "NativeThread";
    lJavaVMAttachArgs.group = nullptr;

    jint lResult = vmHandle->AttachCurrentThread(&jniEnv, &lJavaVMAttachArgs);
    if (lResult == JNI_ERR) {
        return;
    }

    auto classDefinition = jniEnv->FindClass("native_activity/TestLibrary");
    auto ctorId = jniEnv->GetMethodID(classDefinition, "<init>", "()V");
    auto classInstatnce = jniEnv->NewObject(classDefinition, ctorId);
    jmethodID NonStaticMethodId = jniEnv->GetMethodID(classDefinition, "nonStaticMethod", "()V");
    jniEnv->CallVoidMethod(classInstatnce, NonStaticMethodId);
    vmHandle->DetachCurrentThread();
}

// TestLibrary::NonStaticArgInt(arg: Int)
void testCallNonStaticArgInt(struct android_app *pApp) {
    JavaVM *vmHandle = pApp->activity->vm;
    JNIEnv *jniEnv = pApp->activity->env;

    jint lResult = vmHandle->AttachCurrentThread(&jniEnv, nullptr);
    if (lResult == JNI_ERR) {
        return;
    }

    auto classDefinition = jniEnv->FindClass("native_activity/TestLibrary");
    auto ctorId = jniEnv->GetMethodID(classDefinition, "<init>", "()V");
    auto classInstatnce = jniEnv->NewObject(classDefinition, ctorId);
    jmethodID NonStaticMethodId = jniEnv->GetMethodID(classDefinition, "nonStaticArgInt", "(I)V");
    jniEnv->CallVoidMethod(classInstatnce, NonStaticMethodId, 42);
    vmHandle->DetachCurrentThread();
}

JNIEXPORT void JNICALL nativeOnStart(JNIEnv *jenv, jobject obj) {

}

JNIEXPORT void JNICALL nativeOnResume(JNIEnv *jenv, jobject obj) {

}

JNIEXPORT void JNICALL nativeOnPause(JNIEnv *jenv, jobject obj) {

}

JNIEXPORT void JNICALL nativeOnStop(JNIEnv *jenv, jobject obj) {

}

JNIEXPORT void JNICALL nativeSetSurface(JNIEnv *jenv, jobject obj, jobject surface) {

}

}
