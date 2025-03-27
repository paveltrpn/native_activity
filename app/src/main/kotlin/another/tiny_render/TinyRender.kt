package another.tiny_render

import android.app.Activity
import android.app.NativeActivity
import android.os.Bundle
import android.util.Log
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;

class TinyRender : NativeActivity(), SurfaceHolder.Callback {
    init {
        Log.i("TinyRender", "call NativeActivity constructor")
        System.loadLibrary("tiny_render")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.i("TinyRender", "call NativeActivity onCreate()")

        setContentView(R.layout.main)

        val surfaceView: SurfaceView = findViewById<SurfaceView>(R.id.surfaceview)
        surfaceView.getHolder().addCallback(this);
//        surfaceView.setOnClickListener(OnClickListener() {
//            public void onClick(View view) {
//                Toast toast = Toast.makeText(NativeEglExample.this,
//                "This demo combines Java UI and native EGL + OpenGL renderer",
//                Toast.LENGTH_LONG);
//                toast.show();
//            }});
//
        nativeInit()
    }

    override fun onStart() {
        super.onStart()
        Log.i("TinyRender", "call NativeActivity onStart()")

    }

    override fun onResume() {
        super.onResume()
        Log.i("TinyRender", "call NativeActivity onResume()")
    }

    override fun onPause() {
        super.onPause()
        Log.i("TinyRender", "call NativeActivity onPause()")
//        findViewById<SurfaceView>(R.id.surfaceview)
//            .setOnClickListener {
//                Log.d("BUTTONS", "User tapped the button")
//            }
    }

    override fun onStop() {
        super.onStop()
        Log.i("TinyRender", "call NativeActivity onStop()")
    }

    override fun onDestroy() {
        super.onDestroy()
        Log.i("TinyRender", "call NativeActivity onStop()")
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        // nativeSetSurface(holder.getSurface());
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
    }

    fun someAction() {
        Log.i("", "log from virtual world")
    }

    external fun nativeInit()
}


