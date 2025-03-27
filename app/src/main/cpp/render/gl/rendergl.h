
#pragma once

#include <EGL/egl.h> // requires ndk r5 or newer
#include <GLES/gl.h>

#include "../render.h"
#include "../../log/log.h"

namespace tire {
    struct RenderGL : Render {
        RenderGL();
        ~RenderGL();

        void init(ANativeWindow *window) override;
        void preLoop() override;
        void postLoop() override;

        void testMethod() {
            log::info("call RenderGL::testmethod()");
        }

    protected:
        void preFrame() override;
        void frame() override;
        void postFrame() override;
        void swapBuffers() override;

    private:
        EGLDisplay display_;
        EGLSurface surface_;
        EGLContext context_;

        int width_{};
        int height_{};
    };
}
