
#define VK_USE_PLATFORM_ANDROID_KHR

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>
#include "vulkan/vk_enum_string_helper.h"

#include "surface.h"
#include "../../log/log.h"

namespace tire::vk {

    Surface::Surface(ANativeWindow *window,
                     const vk::Instance *instance)
            : instance_{instance} {
        VkAndroidSurfaceCreateInfoKHR surfInfo{};
        surfInfo.sType = VK_STRUCTURE_TYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        surfInfo.window = window;

        if (const auto err = vkCreateAndroidSurfaceKHR(
                    instance_->handle(), &surfInfo, nullptr, &surface_);
                err != VK_SUCCESS) {
            throw std::runtime_error(
                    std::format("failed to create android surface with code {}\n!",
                                string_VkResult(err)));
        } else {
            log::info("vk::Surface === android surface created!");
        }
    }

    Surface::~Surface() {
        vkDestroySurfaceKHR(instance_->handle(), surface_, nullptr);
    }

    VkSurfaceKHR Surface::handle() const {
        return surface_;
    }

}  // namespace tire::vk
