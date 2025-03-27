
#include "rendergl.h"
#include "../../log/log.h"

namespace tire {
    void RenderGL::preLoop() {
        tire::log::info("RenderGL === preLoop()");
        glClearColor(1, 0, 0, 0);
    }

    void RenderGL::preFrame() {

    }

    void RenderGL::frame() {
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width_, height_);
    }

    void RenderGL::postFrame() {

    }

    void RenderGL::swapBuffers() {
        eglSwapBuffers(display_, surface_);
    }

    void RenderGL::postLoop() {
        tire::log::info("RenderGL === postLoop()");
    }
}

