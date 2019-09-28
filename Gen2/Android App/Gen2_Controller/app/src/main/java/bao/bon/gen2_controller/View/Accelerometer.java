package bao.bon.gen2_controller.View;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Context;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.media.MediaPlayer;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.provider.Settings;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import com.koushikdutta.async.future.FutureCallback;
import com.koushikdutta.ion.Ion;

import bao.bon.gen2_controller.Constructor.Common;
import bao.bon.gen2_controller.R;

public class Accelerometer extends AppCompatActivity implements SensorEventListener {

    private volatile boolean stopThread = false;
    private volatile boolean stopAudio = false;
    private volatile boolean camera_available = true;
    private volatile boolean sensor_available = true;
    ImageView btn_Mode,btn_Audio,btn_Camera,imgLight,imgBaterry,imgWiFi;
    WebView webView_send, cameraView;
    TextView txt_Battery,txtDebug,txtSpeed;
    private static String voltage,address;
    SeekBar seekBarSpeed;
    MediaPlayer background_music;
    String g_voltage,c_ipaddress;
    Common commondata;
    /*
    WiFi Animation
     */
    Animation animationAlpha;
    ConnectivityManager conManager;
    NetworkInfo _wifi;
    /*
        Sensor Listener
    */
    private SensorManager sensorManager;
    Sensor accelerometer;
    private float X_backward = (float) -1;
    private float X_forward = (float) 5;
    private float Y_left = (float) -3;
    private float Y_right = (float) 3;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_accelerometer);
        commondata = new Common("0", "5", 90, 90, "0", 100);
        innitView();
        hideSystemUI();
        selectMode();
        lightDetect();  //      --> Detect Light
        speedDetect();  //      --->Detect Speed
        musicBackground();
        ViewCamera();
        read_Voltage_API();
        wiFi_Animation();
        sensor_Listener();
    }

    /*
    Sensor Event
     */
    private void sensor_Listener() {
        sensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);
        accelerometer = sensorManager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        sensorManager.registerListener((SensorEventListener) Accelerometer.this,
                accelerometer,
                SensorManager.SENSOR_DELAY_NORMAL);

    }
    @Override
    public void onSensorChanged(SensorEvent sensorEvent) {
        if(sensor_available == true){
            float x = sensorEvent.values[0];
            float y = sensorEvent.values[1];
            if(x > X_forward){
                commondata.setDirection("3");
                send_Data();
//            start_Thread();
//                Toast.makeText(this, "Forward", Toast.LENGTH_SHORT).show();
            }else if(x < X_backward){
                commondata.setDirection("4");
                send_Data();
//            start_Thread();
//                Toast.makeText(this, "Backward", Toast.LENGTH_SHORT).show();
            }else if(y < Y_left){
                commondata.setDirection("1");
                send_Data();
//                Toast.makeText(this, "Left", Toast.LENGTH_SHORT).show();
            }else if(y > Y_right){
                commondata.setDirection("2");
                send_Data();
//                Toast.makeText(this, "Right", Toast.LENGTH_SHORT).show();
            }else{
//                Toast.makeText(this, "Stop", Toast.LENGTH_SHORT).show();
                commondata.setDirection("5");
                send_Data();
            }
        }
    }
    @Override
    public void onAccuracyChanged(Sensor sensor, int i) {
    }
    private void wiFi_Animation() {
        conManager = (ConnectivityManager) this.getSystemService(CONNECTIVITY_SERVICE);
        animationAlpha = AnimationUtils.loadAnimation(this, R.anim.anim_alpha);
        imgWiFi.startAnimation(animationAlpha);

        imgWiFi.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                checkWiFi_status();
            }
        });
    }
    private void checkWiFi_status() {
        Intent intent = new Intent(Settings.ACTION_WIFI_SETTINGS);
        Accelerometer.this.startActivity(intent);
        animationAlpha.cancel();
    }
    private void wiFiCheck() {
        _wifi = conManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (!_wifi.isAvailable()) {
            imgWiFi.setImageResource(R.drawable.wifi_connect_one);
            imgWiFi.startAnimation(animationAlpha);
        } else if(_wifi.isAvailable()){
            animationAlpha.cancel();
            imgWiFi.setImageResource(R.drawable.wifi_ok);
        }
    }
    private void innitView() {
        btn_Mode = findViewById(R.id.imageView_Mode);
        txt_Battery = findViewById(R.id.textView_Baterry);
        txtDebug = findViewById(R.id.textView_Debug);
        imgLight = findViewById(R.id.imageView_Light);
        imgBaterry  = findViewById(R.id.imageView_Baterry);
        txtSpeed = findViewById(R.id.textView_Speed);
        seekBarSpeed = findViewById(R.id.seek_Bar);
        webView_send = findViewById(R.id.webView_sendT);
        imgWiFi = findViewById(R.id.imageView_WiFi);

        cameraView = findViewById(R.id.Camera_View);
        btn_Camera = findViewById(R.id.image_Camera);
        btn_Mode = findViewById(R.id.imageView_Mode);
        btn_Audio = findViewById(R.id.img_Audio_a);
    }
    private void ViewCamera() {

        cameraView.setWebViewClient(new WebViewClient() {
            @Override
            public void onReceivedError(WebView view, WebResourceRequest request, WebResourceError error) {
                super.onReceivedError(view, request, error);
                cameraView.setVisibility(View.INVISIBLE);
            }

            @Override
            public void onPageFinished(WebView view, String url) {
                super.onPageFinished(view, url);
            }

        });
//        cameraView.loadUrl("http://"+c_ipaddress);

        btn_Camera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (cameraView.getVisibility() == View.INVISIBLE) {
                    if(c_ipaddress != null){
                        cameraView.setVisibility(View.VISIBLE);
                    }else{
                        cameraView.setVisibility(View.INVISIBLE);
                        Toast.makeText(Accelerometer.this, "Please check if the camera is connected !!!", Toast.LENGTH_SHORT).show();
                    }
//                    cameraView.setVisibility(View.VISIBLE);
                } else {
                    cameraView.setVisibility(View.INVISIBLE);
                }
            }
        });
    }
    private void read_Voltage_API() {
        final Thread readVol = new Thread() {
            @Override
            public void run() {
                while (!isInterrupted()) {
                    try {
                        Thread.sleep(2000);
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Ion.with(getApplicationContext()).load("http://192.168.4.1").asString().setCallback(new FutureCallback<String>() {
                                    @Override
                                    public void onCompleted(Exception e, String result) {
                                        g_voltage = readvoltage(result);
                                        c_ipaddress = readAddess(result);
//                                        txtDebug.setText(c_ipaddress);
                                        txt_Battery.setText(g_voltage +" ");
//                                        txtDebug.setText(c_ipaddress);
                                        if(camera_available == true){
                                            cameraView.loadUrl("http://"+c_ipaddress);
                                        }else if(camera_available == false){
                                            cameraView.loadUrl("http://192.168.4.1");
                                        }
                                        float realvoltage =  Float.parseFloat(g_voltage);
                                        if(realvoltage>8){
                                            imgBaterry.setImageResource(R.drawable.battery_full);
                                        }else if (realvoltage > 7.5 && realvoltage <8 ){
                                            imgBaterry.setImageResource(R.drawable.battery_midle);
                                        }else if(realvoltage > 7.2 && realvoltage <7.5){
                                            imgBaterry.setImageResource(R.drawable.battery_low);
                                        }else if(realvoltage < 7.2){
                                            imgBaterry.setImageResource(R.drawable.battery_emty);
                                        }

                                    }
                                });
                            }
                        });
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        readVol.start();
    }
    private void hideSystemUI() {
        // Enables regular immersive mode.
        // For "lean back" mode, remove SYSTEM_UI_FLAG_IMMERSIVE.
        // Or for "sticky immersive," replace it with SYSTEM_UI_FLAG_IMMERSIVE_STICKY
        View decorView = getWindow().getDecorView();
        decorView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE
                        // Set the content to appear under the system bars so that the
                        // content doesn't resize when the system bars hide and show.
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        // Hide the nav bar and status bar
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN);
    }
    private void send_Data() {
        webView_send.setWebViewClient(new WebViewClient());
        webView_send.loadUrl(command_Data());
    }
    private String command_Data() {
        String dataSend = "http://192.168.4.1/?Makershop=,"
                + "Speed=" + commondata.getSpeed() + ","
                + "Direction=" + commondata.getDirection() + ","
                + "Servo_one=" + commondata.getServo_one() + ","
                + "Servo_two=" + commondata.getServo_two() + ","
                + "Led=" + commondata.getLed() + ",";
        return dataSend;
    }
    private void speedDetect() {
        seekBarSpeed.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean b) {
                txtSpeed.setText("Speed " + i + "%");
                commondata.setSpeed(String.valueOf(i));

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                send_Data();
            }
        });
    }
    private void lightDetect() {
        imgLight.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
//                    Toast.makeText(G_Main.this, "Action Down", Toast.LENGTH_SHORT).show();
                    imgLight.setImageResource(R.drawable.highbeam);
                    commondata.setLed("1");
                    send_Data();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    imgLight.setImageResource(R.drawable.lowbeam);
                    commondata.setLed("0");
                    send_Data();
                }
                return true;
            }
        });
    }
    public static String readvoltage(String b_voltage) {
        try{
            b_voltage.trim();
            int vtCuoi1 = b_voltage.lastIndexOf("e=");
            int vtCuoi2 = b_voltage.lastIndexOf(",");
            voltage = b_voltage.substring(vtCuoi1 + 2, vtCuoi2);
        }catch (Exception ex){
            voltage = "0";
        }
        return voltage;
    }
    public static String readAddess(String b_ipadress_) {
        try{
            b_ipadress_.trim();
            int vtCuoi1 = b_ipadress_.lastIndexOf("s=");
            address = b_ipadress_.substring(vtCuoi1 + 2);
//            return address;
        }catch (Exception ex){
            address = null;
        }
        return address;
    }
    private void musicBackground(){
        play();
        btn_Audio.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(stopAudio == false){
                    stopAudio = true;
                    btn_Audio.setImageResource(R.drawable.muted);
                    stopPlayer();
                }else if(stopAudio == true){
                    btn_Audio.setImageResource(R.drawable.volume);
                    stopAudio = false;
                    play();
                }
            }
        });
    }
    public void play( ){
        if(background_music == null){
            background_music = MediaPlayer.create(this,R.raw.backgroundsong);
        }
        background_music.start();
        background_music.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                stopPlayer();
            }
        });
    }
    public void stopPlayer(){
        if(background_music!= null){
            background_music.release();
            background_music = null;
//            Toast.makeText(this, "Stop Music", Toast.LENGTH_SHORT).show();
        }
    }
    private void selectMode() {
        btn_Mode.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                stopPlayer();
                sensor_available = false;
                camera_available = false;
                finish();
                return false;
            }
        });
    }
    @Override
    protected void onResume() {
        super.onResume();
        play();
        camera_available = true;
        sensor_available = true;
        cameraView.setVisibility(View.INVISIBLE);
        wiFiCheck();
        hideSystemUI(); //      --> Hide Task !
    }
}
