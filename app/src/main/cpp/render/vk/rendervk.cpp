
#include "rendervk.h"
#include "pipelines/shader_source.h"

namespace tire {
    RenderVK::RenderVK() = default;

    RenderVK::~RenderVK() = default;

    void RenderVK::init() {
        try {
            instance_ = std::make_unique<vk::Instance>();
            surface_ = std::make_unique<vk::Surface>(window_, instance_.get());
            device_ = std::make_unique<vk::Device>(instance_.get(), surface_.get());
            device_->pickAndCreateDevice();
            swapchain_ =
                    std::make_unique<vk::Swapchain>(device_.get(), surface_.get());
            swapchain_->createSwapchain();
            swapchain_->createImageViews();
            piplineMatrixReady_ =
                    std::make_unique<vk::PiplineMatrixReady>(device_.get());
            piplineMatrixReady_->initPipeline(
                    {{vk::vk_simple_box_VERTEX,   "vk_simple_box_VERTEX"},
                     {vk::vk_simple_box_FRAGMENT, "vk_simple_box_FRAGMENT"}});

            swapchain_->createFramebuffers(piplineMatrixReady_.get());

            commandPool_ = std::make_unique<vk::CommandPool>(device_.get());

            // Create command buffers for each frame
            cBufs_.reserve(FRAMES_IN_FLIGHT_COUNT);
            for (auto i = 0; i < cBufs_.capacity(); ++i) {
                cBufs_.push_back(std::make_unique<vk::RenderFromShader>(
                        device_.get(), commandPool_.get()));
            }

            present_ =
                    std::make_unique<vk::Present>(device_.get(), swapchain_.get());

            presentSync_ = std::make_unique<
                    vk::PresentSynchronization<FRAMES_IN_FLIGHT_COUNT>>(
                    device_.get());

            ready_ = true;
        } catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
    }

    void RenderVK::clean() {
        ready_ = false;
    }
}

