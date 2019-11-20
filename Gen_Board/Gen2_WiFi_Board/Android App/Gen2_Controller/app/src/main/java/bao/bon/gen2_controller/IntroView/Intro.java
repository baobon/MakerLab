package bao.bon.gen2_controller.IntroView;

import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.TableLayout;

import com.google.android.material.tabs.TabLayout;

import java.util.ArrayList;
import java.util.List;

import bao.bon.gen2_controller.R;
import bao.bon.gen2_controller.View.G_Main;

public class Intro extends AppCompatActivity {

    private ViewPager screenPaper;
    bao.bon.gen2_controller.IntroView.IntroViewPageAdapter introViewPageAdapter;
    TabLayout tabIndicator;
    Button btnNext,btngetStarted;
    int position = 0;
    Animation btnAnim;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
                WindowManager.LayoutParams.FLAG_FULLSCREEN);
        setContentView(R.layout.activity_intro);

//        getSupportActionBar().hide();
        hideSystemUI();
        btnAnim = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.button_animation);
        btngetStarted = findViewById(R.id.button_stated);
        btnNext = findViewById(R.id.buttonNext);
        tabIndicator = findViewById(R.id.tab_inducator);


        //initView
        btnAnim = AnimationUtils.loadAnimation(getApplicationContext(), R.anim.button_animation);
        btngetStarted = findViewById(R.id.button_stated);
        btnNext = findViewById(R.id.buttonNext);
        tabIndicator = findViewById(R.id.tab_inducator);


        // fill list screen
        final List<ScreenItem> mList = new ArrayList<>();
        mList.add(new ScreenItem("Make yourself a controlled car", "---Makershop.vn---", R.drawable.imgintro1));
        mList.add(new ScreenItem("Display images via camera", "---Makershop.vn---", R.drawable.imgintro2));
        mList.add(new ScreenItem("Let's get started", "---Makershop.vn---", R.drawable.imgintro3));

        // setup Viewpaper
        screenPaper = findViewById(R.id.screen_viewpaper);
        introViewPageAdapter = new IntroViewPageAdapter(this, mList);
        screenPaper.setAdapter(introViewPageAdapter);

        //setup table with viewpaper

        tabIndicator.setupWithViewPager(screenPaper);

        // Next button click listener

        btnNext.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {

                position = screenPaper.getCurrentItem();
                if (position < mList.size()) {
                    position++;
                    screenPaper.setCurrentItem(position);
                }

                if (position == mList.size() - 1) {
                    // TODO :  show the get Started button and hide the indicator and the next button
                    loadLastScreen();
                }
            }
        });

        tabIndicator.addOnTabSelectedListener(new TabLayout.OnTabSelectedListener() {
            @Override
            public void onTabSelected(TabLayout.Tab tab) {

                if(tab.getPosition() == mList.size() -1){
                    loadLastScreen();
                }
            }

            @Override
            public void onTabUnselected(TabLayout.Tab tab) {

            }

            @Override
            public void onTabReselected(TabLayout.Tab tab) {

            }
        });

        btngetStarted.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intentMain = new Intent(Intro.this, G_Main.class);
                startActivity(intentMain);
                /* TODO : also we need to save a boolean value of storge so next time when the user run the app
                     We could know the he/she is already checked the intro screen activity
                     I'm going to use shared prefernces to that process
                */

                savePrefsData();
            }
        });

}

    private void loadLastScreen() {
        btnNext.setVisibility(View.INVISIBLE);
        btngetStarted.setVisibility(View.VISIBLE);
        tabIndicator.setVisibility(View.INVISIBLE);

        // TODO : ADD an animation the getstarted button
        btngetStarted.setAnimation(btnAnim);
    }

    private boolean restorePrefData() {

        SharedPreferences pref = getApplicationContext().getSharedPreferences("myPrefs",MODE_PRIVATE);
        Boolean isIntroAcitivtyOpenedBefore  = pref.getBoolean("isIntroOpened",false);
        return isIntroAcitivtyOpenedBefore;
    }

    private void savePrefsData() {

        SharedPreferences pref = getApplicationContext().getSharedPreferences("myPrefs", MODE_PRIVATE);
        SharedPreferences.Editor editor = pref.edit();
        editor.putBoolean("isIntroOpened", true);
        editor.commit();

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
