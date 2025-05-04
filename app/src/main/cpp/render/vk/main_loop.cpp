
#include <vulkan/vulkan.h>
#include "vulkan/vk_enum_string_helper.h"

#include "rendervk.h"

namespace tire {

    void RenderVK::preLoop() {
    };

    void RenderVK::preFrame() {

    };

    void RenderVK::frame() {
        const auto [iaSem, rfSem, ifFnc] =
                context_->getFrameSyncSet(currentFrame_);

        // NOTE: omit return code check
        vkWaitForFences(context_->device(), 1, &ifFnc, VK_TRUE, UINT64_MAX);

        // NOTE: omit return code check
        vkResetFences(context_->device(), 1, &ifFnc);

        // NOTE: omit return code check
        // May return VK_SUBOPTIMAL_KHR or even VK_ERROR_OUT_OF_DATE_KHR
        // if current surface properties are no longer matched
        // exactly or swap chain has become incompatible
        // with the surface and can no longer be used for rendering
        uint32_t imageIndex{};
        vkAcquireNextImageKHR(context_->device(), context_->swapchain(),
                              UINT64_MAX, iaSem, VK_NULL_HANDLE, &imageIndex);

        // NOTE: currentFrame_->imageIndex
        const auto currentFramebuffer = context_->framebuffer(currentFrame_);

        renderCommand_->reset();
        renderCommand_->prepare(currentFramebuffer, viewMatrix_, modelMatrix_);
        renderCommand_->submit(iaSem, rfSem, ifFnc);

        context_->present(rfSem, &currentFrame_);

        currentFrame_ = (currentFrame_ + 1) % context_->framesCount();
    };

    void RenderVK::postFrame() {

    };

    void RenderVK::swapBuffers() {

    };

    void RenderVK::postLoop() {
        // we should wait for the logical device to finish operations
        // before exiting mainLoop and destroying the window
        vkDeviceWaitIdle(context_->device());
    };

}  // namespace tire
