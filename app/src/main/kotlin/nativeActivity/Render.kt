package nativeActivity

import android.app.Activity
import android.os.Bundle
import android.util.Log
import android.view.Surface
import android.view.SurfaceView
import android.view.SurfaceHolder
import nativeActivity.Render.R

class Render : Activity(), SurfaceHolder.Callback {
    init {
        System.loadLibrary("native_render")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        setContentView(R.layout.main)

        val surfaceView: SurfaceView = findViewById<SurfaceView>(R.id.surfaceview)
        surfaceView.holder.addCallback(this)
//        surfaceView.setOnClickListener(OnClickListener() {
//            public void onClick(View view) {
//                Toast toast = Toast.makeText(NativeEglExample.this,
//                "This demo combines Java UI and native EGL + OpenGL renderer",
//                Toast.LENGTH_LONG);
//                toast.show();
//            }});
    }

    override fun onStart() {
        super.onStart()
        nativeOnStart()
    }

    override fun onResume() {
        super.onResume()
        nativeOnResume()
    }

    override fun onPause() {
        super.onPause()
        nativeOnPause()
    }

    override fun onStop() {
        super.onStop()
        nativeOnStop()
    }

    override fun onDestroy() {
        super.onDestroy()
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        nativeSetSurface(holder.getSurface())
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        nativeSetSurface(null)
    }

    external fun nativeOnStart()
    external fun nativeOnResume()
    external fun nativeOnPause()
    external fun nativeOnStop()
    external fun nativeSetSurface(surface: Surface?)
}


