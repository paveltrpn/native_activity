
#include <memory>

#include <android/native_window.h>
#include <android/native_window_jni.h>

#include "glue.h"
#include "log/log.h"
#include "render/render.h"
#include "render/vk/rendervk.h"
#include "render/gl/rendergl.h"

extern "C" {

static jobject gClassLoader;
static jmethodID gFindClassMethod;

static tire::RenderGL *globalHandle;

void testCallNonStaticMethod(struct android_app *pApp);
void testCallNonStaticArgInt(struct android_app *pApp);

void handle_cmd(android_app *pApp, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_START: {
            tire::log::info("android_app === onStart()");

//            testCallNonStaticMethod(pApp);
//            testCallNonStaticArgInt(pApp);

            break;
        }
        case APP_CMD_STOP: {
            tire::log::info("android_app === APP_CMD_STOP");
            break;
        }
        case APP_CMD_DESTROY: {
            tire::log::info("android_app === APP_CMD_DESTROY");

            break;
        }
        case APP_CMD_RESUME: {
            tire::log::info("android_app === APP_CMD_RESUME");
            break;
        }
        case APP_CMD_INIT_WINDOW: {
            tire::log::info("android_app === APP_CMD_INIT_WINDOW");

            auto *renderPtr = static_cast<tire::RenderGL *>(pApp->userData);
            renderPtr->init(pApp->window);
            renderPtr->preLoop();

            break;
        }

        case APP_CMD_TERM_WINDOW: {
            tire::log::info("android_app === APP_CMD_TERM_WINDOW");
            if (pApp->userData) {
                auto *renderPtr = static_cast<tire::RenderGL *>(pApp->userData);
                renderPtr->postLoop();
                pApp->userData = nullptr;
                delete renderPtr;
            }
            break;
        }
    }
}

void android_main(struct android_app *pApp) {
    tire::log::info("android_app === call android_main()");

    const auto renderPtr = new tire::RenderGL{};
    globalHandle = renderPtr;
    pApp->userData = renderPtr;

    pApp->onAppCmd = handle_cmd;

    int events;
    android_poll_source *pSource;

    do {
        if (ALooper_pollOnce(0, nullptr, &events, (void **) &pSource) >= 0) {
            if (pSource) {
                pSource->process(pApp, pSource);
            }
        }
        renderPtr->run();
    } while (!pApp->destroyRequested);
}

// TestLibrary::NonStaticMethod()
void testCallNonStaticMethod(struct android_app *pApp) {
    JavaVM *vmHandle = pApp->activity->vm;
    JNIEnv *jniEnv = pApp->activity->env;

    JavaVMAttachArgs lJavaVMAttachArgs;
    lJavaVMAttachArgs.version = JNI_VERSION_1_6;
    lJavaVMAttachArgs.name = "NativeThread";
    lJavaVMAttachArgs.group = NULL;

    jint lResult = vmHandle->AttachCurrentThread(&jniEnv, &lJavaVMAttachArgs);
    if (lResult == JNI_ERR) {
        return;
    }

    auto classDefinition = jniEnv->FindClass("another/tiny_render/TestLibrary");
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

    auto classDefinition = jniEnv->FindClass("another/tiny_render/TestLibrary");
    auto ctorId = jniEnv->GetMethodID(classDefinition, "<init>", "()V");
    auto classInstatnce = jniEnv->NewObject(classDefinition, ctorId);
    jmethodID NonStaticMethodId = jniEnv->GetMethodID(classDefinition, "nonStaticArgInt", "(I)V");
    jniEnv->CallVoidMethod(classInstatnce, NonStaticMethodId, 42);
    vmHandle->DetachCurrentThread();
}

JNIEXPORT void JNICALL
Java_another_tiny_1render_TinyRender_nativeInit(JNIEnv *jenv, jobject self) {
    tire::log::info("call nativeInit()");

    jclass clazz = jenv->FindClass("another/tiny_render/TinyRender");
    // For argument string example
    // jmethodID methodId = jenv->GetMethodID(clazz, "someAction", "(Ljava/lang/String;I)V"
    jmethodID methodId = jenv->GetMethodID(clazz, "someAction", "()V");
    jenv->CallVoidMethod(self, methodId);

    globalHandle->testMethod();
}

}
