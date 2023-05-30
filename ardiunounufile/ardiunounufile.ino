#include <Servo.h>

#define in1 6 // 4 icin
#define in2 7 // 1 icin
const int irPin = A0;  // Connect the IR sensor's output pin to analog pin A0
const int servoPin = 9;  // Connect the signal pin of the servo to digital pin 9

Servo servo;
void setup() {
  Serial.begin(9600);  // Set the baud rate to match the computer's serial monitor
  servo.attach(servoPin);  // Attach the servo to the specified pin

  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // put your setup code here, to run once:
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}

void right() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
}

void front() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
}

void readData() {
  for (int n =0; n <= 45; n+=5) {
    servo.write(n);
    delay(300);
    int sensorValue = analogRead(irPin);
    float distance = 4800.0 / (sensorValue - 20.0);
    Serial.print(distance);
    Serial.print(",");
  }
  Serial.print("@");
}

void loop() {
  // put your main code here, to run repeatedly:
    if (Serial.available()) {
    char data = Serial.read();  // Read the incoming data

    if (data == 'f') { 
      front();
    } else if (data == "r") {
      right();
    } else if (data == "l") {
      left();
    }
    delay(500);
    stop();
    readData();

    //Serial.print("Received data: ");
    //Serial.println(data);
  }

  // Move the servo to the end position (180 degrees)

  delay(1000); 


}
