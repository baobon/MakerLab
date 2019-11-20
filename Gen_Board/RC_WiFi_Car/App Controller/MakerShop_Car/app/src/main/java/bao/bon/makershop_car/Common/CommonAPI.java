package bao.bon.makershop_car.Common;

public class CommonAPI {

    String Speed;
    String Buzzer;
    String Controller;
    String LedCam;


    public CommonAPI(String speed, String buzzer, String controller, String ledCam) {
        Speed = speed;
        Buzzer = buzzer;
        Controller = controller;
        LedCam = ledCam;
    }

    public CommonAPI() {
    }

    public String getSpeed() {
        return Speed;
    }

    public void setSpeed(String speed) {
        Speed = speed;
    }

    public String getBuzzer() {
        return Buzzer;
    }

    public void setBuzzer(String buzzer) {
        Buzzer = buzzer;
    }

    public String getController() {
        return Controller;
    }

    public void setController(String controller) {
        Controller = controller;
    }

    public String getLedCam() {
        return LedCam;
    }

    public void setLedCam(String ledCam) {
        LedCam = ledCam;
    }
}
