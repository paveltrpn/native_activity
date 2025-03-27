
#include "vulkan/vk_enum_string_helper.h"

#include "../../log/log.h"

#include "command_pool.h"

namespace tire::vk {

    CommandPool::CommandPool(const vk::Device *device)
            : device_{device} {
        poolInfo_.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo_.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo_.queueFamilyIndex = device->graphicsFamily();

        if (const auto err = vkCreateCommandPool(device_->handle(), &poolInfo_,
                                                 nullptr, &commandPool_);
                err != VK_SUCCESS) {
            throw std::runtime_error(
                    std::format("vk::CommandPool === failed to create command pool with code {}!",
                                string_VkResult(err)));
        } else {
            log::debug(
                    "vk::CommandPool === command pool created!");
        }
    }

}  // namespace tire::vk
