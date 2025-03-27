
#pragma once

#include <thread>
#include <mutex>

#include <android_native_app_glue.h>

namespace tire {
    struct Render {
        Render();
        Render(const Render &other) = delete;
        Render(Render &&other) = delete;
        Render &operator=(const Render &other) = delete;
        Render &operator=(Render &&other) = delete;

        virtual ~Render();

        virtual void init(ANativeWindow *window) = 0;
        virtual void preLoop() = 0;
        void run();
        virtual void postLoop() = 0;

    protected:
        virtual void preFrame() = 0;
        virtual void frame() = 0;
        virtual void postFrame() = 0;
        virtual void swapBuffers() = 0;

    protected:
        ANativeWindow *window_{};
        bool displayReady_{false};
    };
}