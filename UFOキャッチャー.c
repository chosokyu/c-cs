#include <Servo.h>
//サーボオブジェクト作成
Servo servo1;
Servo servo2;

int i = 0;

//スイッチのピン番号指定
const int sw1  = 0;
const int sw2  = 1;

//モーターのピン番号指定
const int Pin1 = 2;
const int Pin2 = 3;
const int Pin3 = 4;
const int Pin4 = 5;
const int Pin5 = 7;
const int Pin6 = 8;

//pwm出力ピン指定
const int PWM1 = 6;

//pwm出力の値
int val1 = 100;

//スイッチのon/off設定
int swval1 = 0;
int swval2 = 0;

//cdsセンサー値の変数：ans
int ans1;
int ans2;

//タイムカウンタ設定
unsigned int sq_timer;
unsigned int sq_mode = 0;


/*
変数、pin番号指定
*/



void setup() {
//ピンモード設定（INPUT:入力　OUTPUT：出力）
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  pinMode(Pin5, OUTPUT);
  pinMode(Pin6, OUTPUT);


  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);

//サーボモーターのピン番号指定
  servo1.attach( 9 );
  servo2.attach( 11 );
//サーボモーターの値
  servo1.write( 0 );
  servo2.write( 0 );
}


/*
pinの出力設定
*/

void Sequence(void)
{
//スイッチの値を読む
  swval1 = digitalRead(sw1);
  swval2 = digitalRead(sw2);

//cdsセンサーの値を読む
  ans1 = analogRead(0);
  ans2 = analogRead(1);

  switch (sq_mode) {
//スイッチ１が押されなかったら   
 case 0:

      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);

//スイッチ１が押されると
      if (swval1 == 0) {
        sq_mode = 1;//フラグを立てる
      }

      break;

    case 1:

//X軸モーターが動作
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 1);
//スイッチ1が離されると
      if (swval1 == 1) {
        sq_mode = 2;//フラグを立てる
      }
      break;

    case 2:

//モーターが停止
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);


//スイッチ２が押されると
      if (swval2 == 0) {
        sq_mode = 3;//フラグを立てる
      }
      break;

    case 3:
//Y軸モーターが動作
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 1);
//スイッチが離されると
      if (swval2 == 1) {
        sq_mode = 4;//フラグを立てる
      }
      break;

    case 4:
//モーターが停止
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 0);
//UFOキャッチャー爪のサーボモーターが60度まで開く
      servo1.write( 60 );
      servo2.write( 60 );

      delay(1000);
//タイムカウンタ初期化
      sq_timer = 0;

      sq_mode = 5;//フラグを立てる
      break;

    case 5:
//ｐｗｍ値設定
      val1 = 100 ;
//pwm出力
      analogWrite(PWM1, val1);
//UFOキャッチャー爪のサーボモーターが60度まで開く
      servo1.write( 60 );
      servo2.write( 60 );
//Z軸モーター動作
      digitalWrite(Pin5, 1);
      digitalWrite(Pin6, 0);

//Z軸モーター動作時間指定
      if (sq_timer > 950)
      {

        sq_mode = 6;//フラグを立てる
      }
      break;

    case 6:

//Z軸モーター停止
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 0);
//タイムカウンタ初期化
      sq_timer = 0;

      sq_mode = 9;//フラグを立てる
      break;

    case 7:
//サーボモーターの角度を少しずつ0にする
      servo1.write( 60 - sq_timer );
      servo2.write( 60 - sq_timer );

      delay (100);
//sp＿timerが60になると
      if (sq_timer == 60) {
        sq_mode = 8;//フラグを立てる
      }
      break;

    case 8:
//タイムカウンタ初期化
      sq_timer = 0;

      sq_mode = 9;//フラグを立てる
      break;

    case 9:
//ｐｗｍ値設定
      val1 = 250 ;
//pwm出力
      analogWrite(PWM1, val1);
//Z軸モーター動作
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 1);

//Z軸モーター動作時間指定
      if (sq_timer > 550)
      {
        sq_mode = 10;//フラグを立てる
      }
      break;

    case 10:
//Y軸モーター停止
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 0);
//X軸モーター動作
      digitalWrite(Pin1, 1);
      digitalWrite(Pin2, 0);
//cdsセンサー１の値が500以上だと
      if (ans1 >= 500) {

        sq_mode = 11;//フラグを立てる

      }

      break;

    case 11:
//X軸モーター停止
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);
//Y軸モーター動作
      digitalWrite(Pin3, 1);
      digitalWrite(Pin4, 0);
//cdsセンサー２の値が500以上だと
      if (ans2 >= 500) {
        sq_mode = 12;//フラグを立てる
      }

      break;

    case 12:
//Y軸モーター停止
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 0);

      sq_mode = 13;//フラグを立てる
      break;

    case 13:
//サーボモーター角度指定
      servo1.write( 60 );
      servo2.write( 60 );

      sq_mode = 0;//フラグを立てる
      break;

  }
}

/*
タイムカウンタ作成
*/

void loop() {

  delay(10);//10ms スキャンタイミング

  //1サイクルタイミングごとにカウントアップするカウンタ
  if (sq_timer < (unsigned int) - 1)
  {
    sq_timer++;
  }

  Sequence();
}