native_activity
===============

This is a simple Android application that renders a spinning cube using Vulkan. Despite its name, the app does 
not utilize Android's NativeActivity. Instead, it spawns a separate native thread to instantiate Android's 
Vulkan facilities and launch the main rendering loop.

The Vulkan surface is created from an ANativeWindow, which is obtained via a standard Android Activity (implemented in Kotlin). 
The Kotlin code provides the surface to the native thread, enabling Vulkan rendering within the traditional Activity lifecycle.

The core concept of this implementation is inspired by the example 
at https://github.com/tsaarni/android-native-egl-example , adapted for Vulkan.

![alt text](https://github.com/[username]/[reponame]/blob/[branch]/image.jpg?raw=true)
