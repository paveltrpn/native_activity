package native_activity

import android.app.Activity
import android.os.Bundle
import android.util.Log
import android.view.Surface;
import android.view.SurfaceView;
import android.view.SurfaceHolder;


class Render : Activity(), SurfaceHolder.Callback {
    init {
        System.loadLibrary("native_render")
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.i("TinyRender", "call NativeActivity onCreate()")

        // setContentView(R.layout.main)

        // val surfaceView: SurfaceView = findViewById<SurfaceView>(R.id.surfaceview)
        // surfaceView.getHolder().addCallback(this);
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
    }

    override fun onResume() {
        super.onResume()
    }

    override fun onPause() {
        super.onPause()
    }

    override fun onStop() {
        super.onStop()
    }

    override fun onDestroy() {
        super.onDestroy()
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        // nativeSetSurface(holder.getSurface());
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
    }
}


