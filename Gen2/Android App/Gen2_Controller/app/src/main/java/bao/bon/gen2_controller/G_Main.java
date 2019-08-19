package bao.bon.gen2_controller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.os.Handler;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Toast;

import bao.bon.gen2_controller.Constructor.Common;

public class G_Main extends AppCompatActivity {

    ImageView imgLight;
    TextView txtSpeed;
    SeekBar seekBarSpeed;

    ImageView btn_Backward, btn_Forward, btn_Left, btn_Right;
    ImageView btn_servoUp, btn_servoDown, btn_servoLeft, btn_servoRight;

    Common commondata;

    /*
    Webview Send
     */

    WebView webView_send;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.g_main);

        /*
            Default data
         */
        commondata = new Common("0", "5", 90, 90, "0", 100);

        hideSystemUI(); //      --> Hide Task !
        innitView();
        lightDetect();  //      --> Detect Light
        speedDetect();  //      --->Detect Speed
        /*
        Send_data to Gen2_Board
         */
        command_Data();
        send_Data();

        /*
        Controller Data
         */
        handing_direction();

    }

    private void handing_direction() {

        /*
        Button DirecForward
         */
        btn_Forward.setOnTouchListener(new View.OnTouchListener() {
            private Handler mHandler;
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_Forward.setImageResource(R.drawable.top_on);
//                    Toast.makeText(G_Main.this, "Action Down", Toast.LENGTH_SHORT).show();
                    commondata.setDirection("3");
                    send_Data();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    btn_Forward.setImageResource(R.drawable.top);
                    commondata.setDirection("5");
                    send_Data();
                }
                return true;
            }
        });

        btn_Left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_Left.setImageResource(R.drawable.left_on);
//                    Toast.makeText(G_Main.this, "Action Down", Toast.LENGTH_SHORT).show();
                    commondata.setDirection("1");
                    send_Data();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_Left.setImageResource(R.drawable.left);
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    commondata.setDirection("5");
                    send_Data();
                }
                return true;
            }
        });

        btn_Right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_Right.setImageResource(R.drawable.right_on);
//                    Toast.makeText(G_Main.this, "Action Down", Toast.LENGTH_SHORT).show();
                    commondata.setDirection("2");
                    send_Data();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_Right.setImageResource(R.drawable.right);
                    commondata.setDirection("5");
                    send_Data();
                }
                return true;
            }
        });


        btn_Backward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_Backward.setImageResource(R.drawable.bottom_on);
//                    Toast.makeText(G_Main.this, "Action Down", Toast.LENGTH_SHORT).show();
                    commondata.setDirection("4");
                    send_Data();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    btn_Backward.setImageResource(R.drawable.bottom);
                    commondata.setDirection("5");
                    send_Data();

                }
                return true;
            }
        });

        btn_servoLeft.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoLeft.setImageResource(R.drawable.btnleft_on);
                    if (commondata.getServo_one() >= 5 && commondata.getServo_one() <= 180) {
                        commondata.setServo_one(commondata.getServo_one() - 5);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoLeft.setImageResource(R.drawable.btnleft);
                }
                return true;
            }
        });

        btn_servoRight.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoRight.setImageResource(R.drawable.btnright_on);
                    if (commondata.getServo_one() >= 0 && commondata.getServo_one() <= 175) {
                        commondata.setServo_one(commondata.getServo_one() + 5);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoRight.setImageResource(R.drawable.btnright);
                }
                return true;
            }
        });

        btn_servoUp.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoUp.setImageResource(R.drawable.btntop_on);
                    if (commondata.getGetServo_two() >= 0 && commondata.getGetServo_two() <= 175) {
                        commondata.setGetServo_two(commondata.getGetServo_two() + 5);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoUp.setImageResource(R.drawable.btntop);
                }
                return true;
            }
        });

        btn_servoDown.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                btn_servoDown.setImageResource(R.drawable.btnbottom_on);
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if (commondata.getGetServo_two() >= 5 && commondata.getGetServo_two() <= 180) {
                        commondata.setGetServo_two(commondata.getGetServo_two() - 5);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoDown.setImageResource(R.drawable.btnbottom);
                }
                return true;
            }
        });


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
                + "Servo_two=" + commondata.getGetServo_two() + ","
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

    private void innitView() {
        imgLight = findViewById(R.id.imageViewLight);
        txtSpeed = findViewById(R.id.textViewSpeed);
        seekBarSpeed = findViewById(R.id.seekBar);
        webView_send = findViewById(R.id.webView_send);

        btn_Backward = findViewById(R.id.imgDirec_Down);
        btn_Forward = findViewById(R.id.imgDirec_Up);
        btn_Left = findViewById(R.id.imgDirec_Left);
        btn_Right = findViewById(R.id.imgDirec_Right);

        btn_servoDown = findViewById(R.id.imageBottom);
        btn_servoUp = findViewById(R.id.imageTop);
        btn_servoRight = findViewById(R.id.imageRight);
        btn_servoLeft = findViewById(R.id.imageLeft);
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


}
