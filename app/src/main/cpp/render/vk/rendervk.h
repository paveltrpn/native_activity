
#pragma once

#include "../render.h"
#include "instance.h"
#include "surface.h"
#include "device.h"
#include "swapchain.h"
#include "pipelines/pipeline.h"
#include "command_pool.h"
#include "commands/commands.h"
#include "present.h"

#include "../../log/log.h"

#define FRAMES_IN_FLIGHT_COUNT 3

namespace tire {
    struct RenderVK final : Render {
        RenderVK();

        ~RenderVK();

        void init() override;

        void clean() override;

        void preLoop() override;

        void postLoop() override;

    protected:

        void preFrame() override;

        void frame() override;

        void postFrame() override;

        void swapBuffers() override;

    private:
        std::unique_ptr<vk::Instance> instance_{};
        std::unique_ptr<vk::Surface> surface_{};
        std::unique_ptr<vk::Device> device_{};
        std::unique_ptr<vk::Swapchain> swapchain_{};
        std::unique_ptr<vk::Pipeline> piplineMatrixReady_{};
        std::unique_ptr<vk::CommandPool> commandPool_{};
        std::vector<std::unique_ptr<vk::RenderFromShader>> cBufs_{};
        std::unique_ptr<vk::Present> present_{};
        std::unique_ptr<vk::PresentSynchronization<FRAMES_IN_FLIGHT_COUNT>>
                presentSync_{};

        uint32_t currentFrame_{0};
    };

}