// References:
// http://www.tshopping.com.tw/thread-262497-1-1.html

// I had found another library, so you can ignore this experiment.

int PWMA = 33;
int INA2 = 25;
int INA1 = 26;
int STBY = 27;
int INB1 = 14;
int INB2 = 12;
int PWMB = 13;
const int ledPin = 2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT); //設定腳位為輸出
  pinMode(INA1,OUTPUT);
  pinMode(INA2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(INB1,OUTPUT);
  pinMode(INB2,OUTPUT);
  pinMode(PWMB,OUTPUT);
  //digital output test
  digitalWrite(INA1,HIGH); //設定腳位HIGH LOW
  digitalWrite(INA2,LOW);
  digitalWrite(PWMA,LOW);
  digitalWrite(STBY,HIGH);
  digitalWrite(INB1,HIGH);
  digitalWrite(INB2,LOW);
  digitalWrite(PWMB,LOW);
  delay(1000);
  
  //analog output(PWM) test 設定LED Channel PWM 頻率
  ledcSetup(0, 10000, 8);
  ledcSetup(1, 10000, 8);
  ledcSetup(2, 10000, 8);
  ledcSetup(3, 10000, 8);
  ledcSetup(4, 10000, 8);
  ledcSetup(5, 10000, 8);
  ledcSetup(6, 10000, 8);
  //設定腳位Channel
  ledcAttachPin(INA1, 0);
  ledcAttachPin(INA2, 1);
  ledcAttachPin(PWMA, 2);
  ledcAttachPin(STBY, 3);
  ledcAttachPin(INB1, 4);
  ledcAttachPin(INB2, 5);
  ledcAttachPin(PWMB, 6);
  
}

void loop() {
  // 開始前先閃動ESP32板子上LED
//  digitalWrite(ledPin,LOW);
//  delay(500);
//  digitalWrite(ledPin,HIGH);
//  delay(500);
//  digitalWrite(ledPin,LOW);
//  //設定馬達1為正轉
//  ledcWrite(0, 255); //INA1
//  ledcWrite(1, 0);   //INA2
//  ledcWrite(2, 255); //PWMA
//  ledcWrite(3, 255); //STBY
//  //設定馬達2為正轉
//  ledcWrite(4, 255); //INB1
//  ledcWrite(5, 0); //INB2
//  ledcWrite(6, 255); //PWMB
//  delay(50);
//  ledcWrite(3, 0); //STBY
//  delay(1000);
  
//  digitalWrite(ledPin,LOW);
//  delay(500);
//  digitalWrite(ledPin,HIGH);
//  delay(500);
//  digitalWrite(ledPin,LOW);
//  //設定馬達1為反轉
//  ledcWrite(0, 0);   //INA1
//  ledcWrite(1, 255); //INA2
//  ledcWrite(2, 255); //PWMA
//  ledcWrite(3, 255); //STBY
//  //設定馬達2為反轉
//  ledcWrite(4, 0);   //INB1
//  ledcWrite(5, 255); //INB2
//  ledcWrite(6, 255); //PWMB
//  delay(50);
}
