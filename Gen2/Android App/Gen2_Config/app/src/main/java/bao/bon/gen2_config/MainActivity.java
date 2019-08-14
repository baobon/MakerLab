package bao.bon.gen2_config;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.Toast;

import com.rengwuxian.materialedittext.MaterialEditText;

public class MainActivity extends AppCompatActivity {

    MaterialEditText edtId, edtPw;
    Button btnWrite;
    WebView webViewAPI;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        innitView();

        btnWrite.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                /*
                        WiFi ID --- > 4 character --> length >=6
                        WiFi Password ---> 8 charater ---> length >= 8
                 */
//                if (edtId.getText().toString().isEmpty() == false && edtPw.getText().toString().length() >= 6) {
//                    if (edtPw.getText().toString().isEmpty() == false && edtPw.getText().toString().length() >= 8) {
//                        sendAPI(edtId.getText().toString(),edtPw.getText().toString());
//                        Toast.makeText(MainActivity.this, "Write Sucessfully", Toast.LENGTH_SHORT).show();
//                        edtPw.setText("");
//                        edtId.setText("");
//                    } else {
//                        Toast.makeText(MainActivity.this, "Please input 8 charater Password", Toast.LENGTH_SHORT).show();
//                        edtPw.setText("");
//                    }
//                } else {
//                    Toast.makeText(MainActivity.this, "Please input 6 charater ID", Toast.LENGTH_SHORT).show();
//                    edtPw.setText("");
//                }
                if (edtId.getText().toString().isEmpty() == false) {
                    if (edtId.getText().toString().length() >= 4) {
                        if (edtPw.getText().toString().isEmpty() == false) {
                            if (edtPw.getText().toString().length() >= 8) {
                                sendAPI(edtId.getText().toString(), edtPw.getText().toString());
                                Toast.makeText(MainActivity.this, "Write Sucessfully", Toast.LENGTH_SHORT).show();
                                edtPw.setText("");
                                edtId.setText("");
                            } else {
                                Toast.makeText(MainActivity.this, "Password must be at least 8 characters long !", Toast.LENGTH_SHORT).show();
                                edtPw.setText("");
                            }
                        } else {
                            Toast.makeText(MainActivity.this, "Please input your password", Toast.LENGTH_SHORT).show();
                        }
                    } else {
                        Toast.makeText(MainActivity.this, "Ssid must be at least 4 characters long !", Toast.LENGTH_SHORT).show();
                        edtPw.setText("");
                    }

                } else {
                    Toast.makeText(MainActivity.this, "Please input your ssid", Toast.LENGTH_SHORT).show();
                    edtPw.setText("");
                }

            }
        });

    }

    private void innitView() {
        edtId = findViewById(R.id.edt_id);
        edtPw = findViewById(R.id.edt_pw);
        btnWrite = findViewById(R.id.buttonWrite);
        webViewAPI = findViewById(R.id.webView_Data);
    }

    private void sendAPI(String ssid, String pass) {
        webViewAPI.setWebViewClient(new WebViewClient());
//        http://192.168.4.1/?Makershop=,RunSet=99,SSID=DemoSSID,PASS=DEMOPASSSS,Confirm=99,
        webViewAPI.loadUrl("http://192.168.4.1/?Makershop=,RunSet=99,SSID=" + ssid + ",PASS=" + pass
                + ",Confirm=99,");
    }
}
