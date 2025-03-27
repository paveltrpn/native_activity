
#include "rendergl.h"
#include "../../log/log.h"

namespace tire {
    RenderGL::RenderGL() : Render{} {}

    RenderGL::~RenderGL() {}

    void RenderGL::init(ANativeWindow *window) {
        window_ = window;

        const EGLint attribs[] = {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_NONE
        };
        EGLDisplay display;
        EGLConfig config;
        EGLint numConfigs;
        EGLint format;
        EGLSurface surface;
        EGLContext context;
        EGLint width;
        EGLint height;
        GLfloat ratio;

        log::info("RenderGL == Initializing context");

        if ((display = eglGetDisplay(EGL_DEFAULT_DISPLAY)) == EGL_NO_DISPLAY) {
            log::error("eglGetDisplay() returned error %d", eglGetError());
            return;
        }

        EGLint major{};
        EGLint minor{};

        if (!eglInitialize(display, &major, &minor)) {
            log::error("eglInitialize() returned error {}", eglGetError());
            return;
        } else {
            log::info("RenderGL === egl version {}.{}", major, minor);
        }

        if (!eglChooseConfig(display, attribs, &config, 1, &numConfigs)) {
            log::error("eglChooseConfig() returned error {}", eglGetError());
            return;
        }

        if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format)) {
            log::error("eglGetConfigAttrib() returned error %d", eglGetError());
            return;
        }

        ANativeWindow_setBuffersGeometry(window_, 0, 0, format);

        if (!(surface = eglCreateWindowSurface(display, config, window_, nullptr))) {
            log::error("eglCreateWindowSurface() returned error {}", eglGetError());
            return;
        }

        if (!(context = eglCreateContext(display, config, nullptr, nullptr))) {
            log::error("eglCreateContext() returned error {}", eglGetError());
            return;
        }

        if (!eglMakeCurrent(display, surface, surface, context)) {
            log::error("eglMakeCurrent() returned error {}", eglGetError());
            return;
        }

        if (!eglQuerySurface(display, surface, EGL_WIDTH, &width) ||
            !eglQuerySurface(display, surface, EGL_HEIGHT, &height)) {
            log::error("eglQuerySurface() returned error {}", eglGetError());
            return;
        }

        display_ = display;
        surface_ = surface;
        context_ = context;
        width_ = width;
        height_ = height;

        glDisable(GL_DITHER);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);

        /*glEnable(GL_CULL_FACE);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        glViewport(0, 0, width, height);

        ratio = (GLfloat) width / height;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustumf(-ratio, ratio, -1, 1, 1, 10);
         */
        displayReady_ = true;
    }
}
