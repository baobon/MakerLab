package bao.bon.gen2_controller.Constructor;

public class Common {

    private String speed;
    private String direction;
    private int servo_one;
    private int servo_two;
    private String led;
    private int baterry;

    public Common(String speed, String direction, int servo_one, int servo_two, String led, int baterry) {
        this.speed = speed;
        this.direction = direction;
        this.servo_one = servo_one;
        this.servo_two = servo_two;
        this.led = led;
        this.baterry = baterry;
    }

    public String getSpeed() {
        return speed;
    }

    public void setSpeed(String speed) {
        this.speed = speed;
    }

    public String getDirection() {
        return direction;
    }

    public void setDirection(String direction) {
        this.direction = direction;
    }

    public int getServo_one() {
        return servo_one;
    }

    public void setServo_one(int servo_one) {
        this.servo_one = servo_one;
    }

    public int getServo_two() {
        return servo_two;
    }

    public void setServo_two(int getServo_two) {
        this.servo_two = servo_two;
    }

    public String getLed() {
        return led;
    }

    public void setLed(String led) {
        this.led = led;
    }

    public int getBaterry() {
        return baterry;
    }

    public void setBaterry(int baterry) {
        this.baterry = baterry;
    }
}
