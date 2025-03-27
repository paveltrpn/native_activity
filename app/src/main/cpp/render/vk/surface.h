
#pragma once

#include <android/native_window.h> // requires ndk r5 or newer
#include <android/native_window_jni.h> // requires ndk r5 or newer

#include <vulkan/vulkan.h>
#include <vulkan/vulkan_core.h>

#include "instance.h"

namespace tire::vk {

    struct Surface final {
        Surface(ANativeWindow *window, const vk::Instance *instance);

        Surface(const Surface &other) = delete;

        Surface(Surface &&other) = delete;

        Surface &operator=(const Surface &other) = delete;

        Surface &operator=(Surface &&other) = delete;

        ~Surface();

        [[nodiscard]] VkSurfaceKHR handle() const;

    private:
        const vk::Instance *instance_{};

        // Vulkan etity handles
        VkSurfaceKHR surface_{VK_NULL_HANDLE};
    };

}  // namespace tire::vk
