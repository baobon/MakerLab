package bao.bon.makershop_rccar;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.RelativeLayout;

import bao.bon.makershop_rccar.JoyStick.JoyStickClass;

public class MainActivity extends AppCompatActivity {

    RelativeLayout lt_joystick;
    JoyStickClass js;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }
}
