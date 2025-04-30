package nativeActivity

import android.util.Log

class TestLibrary {
    fun nonStaticMethod() {
        Log.i("", "NonStaticMethod() from jvm world")
    }

    fun nonStaticArgInt(arg: Int) {
        Log.i("", "NonStaticArgInt() from jvm world, arg")
    }
}
