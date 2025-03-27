
#include "render.h"
#include "../log/log.h"

namespace tire {
    Render::Render() {
        log::info("render initialization started...");
    }

    Render::~Render() {
        log::info("Render === native render object destoyed");
    }

    void Render::run() {
        if (displayReady_) {
            preFrame();
            frame();
            swapBuffers();
            postFrame();
        }
    }

}


