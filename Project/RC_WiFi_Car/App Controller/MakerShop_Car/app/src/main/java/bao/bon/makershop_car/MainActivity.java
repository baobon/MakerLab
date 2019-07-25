package bao.bon.makershop_car;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebResourceError;
import android.webkit.WebResourceRequest;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import bao.bon.makershop_car.Common.CommonAPI;
import bao.bon.makershop_car.JoyStick.JoyStickClass;

public class MainActivity extends AppCompatActivity {

    // Camera View
    WebView cameraView;
    WebView webViewSend;
    // Joystick
    RelativeLayout lt_joystick;
    JoyStickClass js;
    //CommonAPI
    CommonAPI commonAPI;
    //Led & Buzzer & Speed
    ImageView imgLed,imgBuzzer;
    TextView txtSpeed;
    SeekBar seekBarSpeed;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_main);

        InnitView();
        /*  --> View Camera --> Screen Camera <--  */
        ViewCamera();
        /*  --> JoyStick HandingData <--    */
        commonAPI = new CommonAPI("100", "0", "9", "0");
        JoyStickHanding();
        /* --> Speed <-- */
        SpeedHanding();
        /* --> Buzzer <-- */
        BuzzerHanding();
        /* --> Led <-- */
        LedHanding();

    }

    private void LedHanding() {
        imgLed.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(commonAPI.getLedCam() == "0"){
                    imgLed.setImageResource(R.drawable.lighton);
                    commonAPI.setLedCam("1");
                    sendAPI();
                }else if (commonAPI.getLedCam() == "1"){
                    imgLed.setImageResource(R.drawable.lightoff);
                    commonAPI.setLedCam("0");
                    sendAPI();
                }
            }
        });
    }
    private void BuzzerHanding() {
        imgBuzzer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if(commonAPI.getBuzzer() == "0") {
                    commonAPI.setBuzzer("1");
                    sendAPI();
                    commonAPI.setBuzzer("0");
                }else if (commonAPI.getBuzzer() == "1"){
                    commonAPI.setBuzzer("0");
                    sendAPI();
                }
            }
        });
    }
    private void SpeedHanding() {
        seekBarSpeed.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                txtSpeed.setText("Car Speed : " + progress);
                commonAPI.setSpeed(progress + "");
                sendAPI();
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }

    /*
    ----------------------------******************************--------------------------------------
    ----------------------------******************************--------------------------------------
    ----------------------------******************************--------------------------------------
    ----------------------------******************************--------------------------------------
     */
    private void JoyStickHanding() {
        js = new JoyStickClass(getApplicationContext(), lt_joystick, R.drawable.circlegrey);
        js.setStickSize(150, 150);
        js.setLayoutSize(600, 600);
        js.setLayoutAlpha(150);
        js.setStickAlpha(100);
        js.setOffset(90);
        js.setMinimumDistance(50);
        lt_joystick.setOnTouchListener(onTouchListener());

    }
    private View.OnTouchListener onTouchListener() {
        return new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                js.drawStick(motionEvent);
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN
                        || motionEvent.getAction() == MotionEvent.ACTION_MOVE) {
                    int direction = js.get8Direction();
                    if (direction == JoyStickClass.STICK_UP) {
                        commonAPI.setController("1");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_UPRIGHT) {
                        commonAPI.setController("6");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_RIGHT) {
                        commonAPI.setController("3");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_DOWNRIGHT) {
                        commonAPI.setController("8");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_DOWN) {
                        commonAPI.setController("2");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_DOWNLEFT) {
                        commonAPI.setController("7");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_LEFT) {
                        commonAPI.setController("4");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_UPLEFT) {
                        commonAPI.setController("5");
                        sendAPI();
                    } else if (direction == JoyStickClass.STICK_NONE) {
                        commonAPI.setController("9");
                        sendAPI();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    commonAPI.setController("9");
                    sendAPI();
                }
                return true;
            }
        };
    }
    private void sendAPI() {
        webViewSend.setWebViewClient(new WebViewClient());
        webViewSend.loadUrl("http://192.168.4.1/?MakerCar=" + convertString());
    }
    private String convertString() {
        return
                "Speed=" + commonAPI.getSpeed() +
                        ",Buzzer=" + commonAPI.getBuzzer() +
                        ",Controller=" + commonAPI.getController() +
                        ",LedCam=" + commonAPI.getLedCam() + ",";
    }
    private void InnitView() {
        lt_joystick = findViewById(R.id.layout_joystick);
        cameraView = findViewById(R.id.CameraView);
        webViewSend = findViewById(R.id.WebViewSend);
        imgLed = findViewById(R.id.imageViewLed);
        imgBuzzer = findViewById(R.id.imageViewHorn);
        txtSpeed = findViewById(R.id.TextViewCarSpeed);
        seekBarSpeed = findViewById(R.id.seekbarSpeed);
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
                cameraView.setVisibility(View.VISIBLE);
            }
        });
        
        cameraView.loadUrl("http://192.168.4.2");
        cameraView.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                return (motionEvent.getAction() == MotionEvent.ACTION_MOVE);
            }
        });
    }
}
