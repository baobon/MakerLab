package bao.bon.gen2_controller.View;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.media.MediaPlayer;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Handler;
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
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.SeekBar;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.koushikdutta.async.future.FutureCallback;
import com.koushikdutta.ion.Ion;

import bao.bon.gen2_controller.Constructor.Common;
import bao.bon.gen2_controller.R;

public class G_Main extends AppCompatActivity {

    private static String voltage, address;
    ImageView imgLight, imgBaterry, imgWiFi, imgSetting;
    TextView txtSpeed;
    SeekBar seekBarSpeed;
    ImageView btn_Mode;
    ImageView btn_Backward, btn_Forward, btn_Left, btn_Right;
    ImageView btn_servoUp, btn_servoDown, btn_servoLeft, btn_servoRight;
    ImageView btn_Audio;
    ImageView btn_Camera;
    TextView txt_Battery, txtDebug;
    Common commondata;
    private volatile boolean stopThread = false;
    private volatile boolean stopAudio = false;
    private volatile boolean camera_available = true;
    int servo_post_one,servo_post_two;
    String g_voltage;
    String c_ipaddress;
    MediaPlayer background_music;
    /*
    Webview Send
     */
    WebView webView_send, cameraView;
    /*
        WiFi Animation
     */
    Animation animationAlpha;
    ConnectivityManager conManager;
    NetworkInfo _wifi;
    /*
    Prefersences shared
     */
    private final String SHARED_PREFERSENCES_NAME = "Makershop";
    private final String SERVO_POST_ONE = "ServoPostOne";
    private final String SERVO_POST_TWO = "ServoPostTwo";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.g_main);
        innitView();
        Toast.makeText(G_Main.this, "Select Mode Run Manual !!!", Toast.LENGTH_LONG).show();
        /*
            WiFi Animaiton
        */
        wiFi_Animation();
        readData();
        /*
            Default data
        */
        commondata = new Common("0", "5", 90, 90, "0", 100);
        /*
            Hide UI
        */
        hideSystemUI(); //      --> Hide Task !
        lightDetect();  //      --> Detect Light
        speedDetect();  //      --->Detect Speed
        /*
            Send_data to Gen2_Board
        */
        command_Data();
        send_Data();
        /*
            Music for App
        */
        musicBackground();
        /*
            Controller Data
        */
        handing_direction();
        /*
            Read Voltage && IP Address
         */
        read_Voltage_API();
        /*
            Open Camera
        */
        ViewCamera();
        /*
            Mode intent Activity !!!!
        */
//        selectMode();

        /*
            Preferences Data servo_post intent
        */
        SettingDialog();


    }

    private void SettingDialog() {
        imgSetting.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                AlertDialog.Builder mBuilder = new AlertDialog.Builder(G_Main.this);
                View mView = getLayoutInflater().inflate(R.layout.dialog_postive, null);

                final TextView txtLastPostionOne = mView.findViewById(R.id.lastposition_one);
                final TextView txtLastPostionTwo = mView.findViewById(R.id.lastposition_two);
                final Spinner spinnerServoOne = mView.findViewById(R.id.spinner_postive_one);
                final Spinner spinnerServoTwo = mView.findViewById(R.id.spinner_postive_two);
                readData();
                txtLastPostionOne.setText(String.valueOf(servo_post_one));
                txtLastPostionTwo.setText(String.valueOf(servo_post_two));

                ArrayAdapter<String> adapter = new ArrayAdapter<String>(G_Main.this,
                        android.R.layout.simple_spinner_item,
                        getResources().getStringArray(R.array.postiveList));
                adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
                spinnerServoOne.setAdapter(adapter);
                spinnerServoTwo.setAdapter(adapter);
                mBuilder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        if (!spinnerServoOne.getSelectedItem().toString().equalsIgnoreCase("Select..")
                                & !spinnerServoTwo.getSelectedItem().toString().equalsIgnoreCase("Select..")) {
                            addData(Integer.parseInt(spinnerServoOne.getSelectedItem().toString()),
                                    Integer.parseInt(spinnerServoTwo.getSelectedItem().toString()));
                            commondata.setServo_one(Integer.parseInt(spinnerServoOne.getSelectedItem().toString()));
                            commondata.setServo_two(Integer.parseInt(spinnerServoTwo.getSelectedItem().toString()));
                            Toast.makeText(G_Main.this, "Servo One Postive to " + spinnerServoOne.getSelectedItem().toString()
                                    + "\nServo Two Postive to " + spinnerServoTwo.getSelectedItem().toString()
                                    , Toast.LENGTH_SHORT).show();
                            dialogInterface.dismiss();
                        } else {
                            Toast.makeText(G_Main.this, "Please select any empty fields ", Toast.LENGTH_SHORT).show();
                        }
                    }
                });
                mBuilder.setNegativeButton("Dismiss", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialogInterface, int i) {
                        dialogInterface.dismiss();
                    }
                });
                mBuilder.setView(mView);
                AlertDialog dialog = mBuilder.create();
                dialog.show();
            }
        });
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
        G_Main.this.startActivity(intent);
        animationAlpha.cancel();
    }

    private void wiFiCheck() {
        _wifi = conManager.getNetworkInfo(ConnectivityManager.TYPE_WIFI);
        if (!_wifi.isAvailable()) {
            imgWiFi.setImageResource(R.drawable.wifi_connect_one);
            imgWiFi.startAnimation(animationAlpha);
        } else if (_wifi.isAvailable()) {
            animationAlpha.cancel();
            imgWiFi.setImageResource(R.drawable.wifi_ok);
        }
    }

    public void play() {
        if (background_music == null) {
            background_music = MediaPlayer.create(this, R.raw.backgroundsong);
        }
        background_music.start();
        background_music.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                stopPlayer();
            }
        });
    }

    public void stopPlayer() {
        if (background_music != null) {
            background_music.release();
            background_music = null;
//            Toast.makeText(this, "Stop Music", Toast.LENGTH_SHORT).show();
        }
    }

    private void musicBackground() {
        play();
        btn_Audio.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (stopAudio == false) {
                    stopAudio = true;
                    btn_Audio.setImageResource(R.drawable.muted);
                    stopPlayer();
                } else if (stopAudio == true) {
                    btn_Audio.setImageResource(R.drawable.volume);
                    stopAudio = false;
                    play();
                }
            }
        });
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
                    if (c_ipaddress != null) {
                        cameraView.setVisibility(View.VISIBLE);
                    } else {
                        cameraView.setVisibility(View.INVISIBLE);
                        Toast.makeText(G_Main.this, "Please check if the camera is connected !!!", Toast.LENGTH_SHORT).show();
                    }
//                    cameraView.setVisibility(View.VISIBLE);
                } else {
                    cameraView.setVisibility(View.INVISIBLE);
                }
            }
        });
    }

    private void read_Voltage_API() {
        Thread readVol = new Thread() {
            @Override
            public void run() {
                while (!isInterrupted()) {
                    try {
                        Thread.sleep(5000);
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Ion.with(getApplicationContext()).load("http://192.168.4.1").asString().setCallback(new FutureCallback<String>() {
                                    @Override
                                    public void onCompleted(Exception e, String result) {
                                        g_voltage = readvoltage(result);
                                        c_ipaddress = readAddess(result);
//                                        txtDebug.setText(c_ipaddress);
                                        txt_Battery.setText(g_voltage + " ");
                                        if (c_ipaddress != null) {
//                                            wiFiAnimation.start();
                                        } else if (c_ipaddress == null) {
//                                            wiFiAnimation.start();
                                        }
                                        if (camera_available == true) {
                                            cameraView.loadUrl("http://" + c_ipaddress);
                                        } else if (camera_available == false) {
                                            cameraView.loadUrl("http://192.168.4.1");
                                        }
                                        float realvoltage = Float.parseFloat(g_voltage);
                                        if (realvoltage > 8) {
                                            imgBaterry.setImageResource(R.drawable.battery_full);
                                        } else if (realvoltage > 7.5 && realvoltage < 8) {
                                            imgBaterry.setImageResource(R.drawable.battery_midle);
                                        } else if (realvoltage > 7.2 && realvoltage < 7.5) {
                                            imgBaterry.setImageResource(R.drawable.battery_low);
                                        } else if (realvoltage < 7.2) {
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
                    start_Thread();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    btn_Forward.setImageResource(R.drawable.top);
                    stop_Thread();
                    commondata.setDirection("5");
                    send_Data();
//                    st
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
//                    start_Thread();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_Right.setImageResource(R.drawable.right);
//                    stop_Thread();
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
//                    send_Data();
                    start_Thread();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
//                    Toast.makeText(G_Main.this, "Action Up", Toast.LENGTH_SHORT).show();
                    btn_Backward.setImageResource(R.drawable.bottom);
                    stop_Thread();
                    commondata.setDirection("5");
                    send_Data();

                }
                return true;
            }
        });

        btn_servoRight.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoRight.setImageResource(R.drawable.btnright_on);
                    if (commondata.getServo_one() >= servo_post_one && commondata.getServo_one() <= 180) {
                        commondata.setServo_one(commondata.getServo_one() - servo_post_one);
                        send_Data();
//                        Toast.makeText(G_Main.this, String.valueOf(servo_post_one), Toast.LENGTH_SHORT).show();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoRight.setImageResource(R.drawable.btnright);
                }
                return true;
            }
        });

        btn_servoLeft.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoLeft.setImageResource(R.drawable.btnleft_on);
                    if (commondata.getServo_one() >= 0 && commondata.getServo_one() <= 180 - servo_post_one) {
                        commondata.setServo_one(commondata.getServo_one() + servo_post_one);
                        send_Data();
//                        Toast.makeText(G_Main.this, String.valueOf(servo_post_one), Toast.LENGTH_SHORT).show();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoLeft.setImageResource(R.drawable.btnleft);
                }
                return true;
            }
        });

        btn_servoDown.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    btn_servoDown.setImageResource(R.drawable.btnbottom_on);
                    if (commondata.getServo_two() >= 0 && commondata.getServo_two() <= 180 - servo_post_two) {
                        commondata.setServo_two(commondata.getServo_two() + servo_post_two);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoDown.setImageResource(R.drawable.btnbottom);
                }
                return true;
            }
        });

        btn_servoUp.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                btn_servoUp.setImageResource(R.drawable.btntop_on);
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    if (commondata.getServo_two() >= servo_post_two && commondata.getServo_two() <= 180) {
                        commondata.setServo_two(commondata.getServo_two() - servo_post_two);
                        send_Data();
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    btn_servoUp.setImageResource(R.drawable.btntop);
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

    private void innitView() {
        txt_Battery = findViewById(R.id.textViewBaterry);
        txtDebug = findViewById(R.id.textViewDebug);
        imgLight = findViewById(R.id.imageViewLight);
        imgBaterry = findViewById(R.id.imageViewBaterry);


        txtSpeed = findViewById(R.id.textViewSpeed);
        seekBarSpeed = findViewById(R.id.seekBar);
        webView_send = findViewById(R.id.webView_send);

        btn_Backward = findViewById(R.id.imgDirec_Down);
        btn_Forward = findViewById(R.id.imgDirec_Up);
        btn_Left = findViewById(R.id.imgDirec_Left);
        btn_Right = findViewById(R.id.imgDirec_Right);
        btn_Audio = findViewById(R.id.img_Audio);

        btn_servoDown = findViewById(R.id.imageBottom);
        btn_servoUp = findViewById(R.id.imageTop);
        btn_servoRight = findViewById(R.id.imageRight);
        btn_servoLeft = findViewById(R.id.imageLeft);

        cameraView = findViewById(R.id.CameraView);
        btn_Camera = findViewById(R.id.imageCamera);
        btn_Mode = findViewById(R.id.imageViewMode);
        imgWiFi = findViewById(R.id.imageViewWiFi);
        imgSetting = findViewById(R.id.imageViewSetting);

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

    private void selectMode() {
        btn_Mode.setOnLongClickListener(new View.OnLongClickListener() {
            @Override
            public boolean onLongClick(View view) {
                Toast.makeText(G_Main.this, "Select Mode Accelerometer !!!", Toast.LENGTH_SHORT).show();
                camera_available = false;
                stopPlayer();
                Intent intentAccelerometer = new Intent(G_Main.this, Accelerometer.class);
                startActivity(intentAccelerometer);
                return false;
            }
        });
    }

    void start_Thread() {
        stopThread = false;
        SendRunable runable = new SendRunable(10000);
        new Thread(runable).start();
    }

    void stop_Thread() {
        stopThread = true;
    }

    public static String readvoltage(String b_voltage) {
        try {
            b_voltage.trim();
            int vtCuoi1 = b_voltage.lastIndexOf("e=");
            int vtCuoi2 = b_voltage.lastIndexOf(",");
            voltage = b_voltage.substring(vtCuoi1 + 2, vtCuoi2);
        } catch (Exception ex) {
            voltage = "0";
        }
        return voltage;
    }

    public static String readAddess(String b_ipadress_) {
        try {
            b_ipadress_.trim();
            int vtCuoi1 = b_ipadress_.lastIndexOf("s=");
            address = b_ipadress_.substring(vtCuoi1 + 2);
        } catch (Exception ex) {
            address = null;
        }
        return address;
    }

    class SendRunable implements Runnable {
        int seconds;

        SendRunable(int seconds) {
            this.seconds = seconds;
        }

        @Override
        public void run() {
            for (int i = 0; i < seconds; i++) {
                if (stopThread) return;
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        send_Data();
                    }
                });
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    /*
    References
     */
    public void addData(int postive_one,int postive_two) {
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFERSENCES_NAME, MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPreferences.edit(); //Open file shared
        editor.putInt(SERVO_POST_ONE, postive_one);
        editor.putInt(SERVO_POST_TWO, postive_two);
        editor.apply();
    }

    public void readData() {
        SharedPreferences sharedPreferences = getSharedPreferences(SHARED_PREFERSENCES_NAME, MODE_PRIVATE);
        servo_post_one = sharedPreferences.getInt(SERVO_POST_ONE, 5);
        servo_post_two = sharedPreferences.getInt(SERVO_POST_TWO, 5);
    }



    /*
    Override
     */
    @Override
    protected void onStop() {
        super.onStop();
        stopPlayer();
    }

    @Override
    protected void onPostCreate(@Nullable Bundle savedInstanceState) {
        super.onPostCreate(savedInstanceState);
    }

    @Override
    protected void onResume() {
        super.onResume();
        play();
        camera_available = true;
        cameraView.setVisibility(View.INVISIBLE);
        wiFiCheck();
        hideSystemUI(); //      --> Hide Task !
    }
}
