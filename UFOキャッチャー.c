#include <Servo.h>
//�T�[�{�I�u�W�F�N�g�쐬
Servo servo1;
Servo servo2;

int i = 0;

//�X�C�b�`�̃s���ԍ��w��
const int sw1  = 0;
const int sw2  = 1;

//���[�^�[�̃s���ԍ��w��
const int Pin1 = 2;
const int Pin2 = 3;
const int Pin3 = 4;
const int Pin4 = 5;
const int Pin5 = 7;
const int Pin6 = 8;

//pwm�o�̓s���w��
const int PWM1 = 6;

//pwm�o�͂̒l
int val1 = 100;

//�X�C�b�`��on/off�ݒ�
int swval1 = 0;
int swval2 = 0;

//cds�Z���T�[�l�̕ϐ��Fans
int ans1;
int ans2;

//�^�C���J�E���^�ݒ�
unsigned int sq_timer;
unsigned int sq_mode = 0;


/*
�ϐ��Apin�ԍ��w��
*/



void setup() {
//�s�����[�h�ݒ�iINPUT:���́@OUTPUT�F�o�́j
  pinMode(Pin1, OUTPUT);
  pinMode(Pin2, OUTPUT);
  pinMode(Pin3, OUTPUT);
  pinMode(Pin4, OUTPUT);
  pinMode(Pin5, OUTPUT);
  pinMode(Pin6, OUTPUT);


  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);

//�T�[�{���[�^�[�̃s���ԍ��w��
  servo1.attach( 9 );
  servo2.attach( 11 );
//�T�[�{���[�^�[�̒l
  servo1.write( 0 );
  servo2.write( 0 );
}


/*
pin�̏o�͐ݒ�
*/

void Sequence(void)
{
//�X�C�b�`�̒l��ǂ�
  swval1 = digitalRead(sw1);
  swval2 = digitalRead(sw2);

//cds�Z���T�[�̒l��ǂ�
  ans1 = analogRead(0);
  ans2 = analogRead(1);

  switch (sq_mode) {
//�X�C�b�`�P��������Ȃ�������   
 case 0:

      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);

//�X�C�b�`�P����������
      if (swval1 == 0) {
        sq_mode = 1;//�t���O�𗧂Ă�
      }

      break;

    case 1:

//X�����[�^�[������
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 1);
//�X�C�b�`1����������
      if (swval1 == 1) {
        sq_mode = 2;//�t���O�𗧂Ă�
      }
      break;

    case 2:

//���[�^�[����~
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);


//�X�C�b�`�Q����������
      if (swval2 == 0) {
        sq_mode = 3;//�t���O�𗧂Ă�
      }
      break;

    case 3:
//Y�����[�^�[������
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 1);
//�X�C�b�`����������
      if (swval2 == 1) {
        sq_mode = 4;//�t���O�𗧂Ă�
      }
      break;

    case 4:
//���[�^�[����~
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 0);
//UFO�L���b�`���[�܂̃T�[�{���[�^�[��60�x�܂ŊJ��
      servo1.write( 60 );
      servo2.write( 60 );

      delay(1000);
//�^�C���J�E���^������
      sq_timer = 0;

      sq_mode = 5;//�t���O�𗧂Ă�
      break;

    case 5:
//�������l�ݒ�
      val1 = 100 ;
//pwm�o��
      analogWrite(PWM1, val1);
//UFO�L���b�`���[�܂̃T�[�{���[�^�[��60�x�܂ŊJ��
      servo1.write( 60 );
      servo2.write( 60 );
//Z�����[�^�[����
      digitalWrite(Pin5, 1);
      digitalWrite(Pin6, 0);

//Z�����[�^�[���쎞�Ԏw��
      if (sq_timer > 950)
      {

        sq_mode = 6;//�t���O�𗧂Ă�
      }
      break;

    case 6:

//Z�����[�^�[��~
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 0);
//�^�C���J�E���^������
      sq_timer = 0;

      sq_mode = 9;//�t���O�𗧂Ă�
      break;

    case 7:
//�T�[�{���[�^�[�̊p�x����������0�ɂ���
      servo1.write( 60 - sq_timer );
      servo2.write( 60 - sq_timer );

      delay (100);
//sp�Qtimer��60�ɂȂ��
      if (sq_timer == 60) {
        sq_mode = 8;//�t���O�𗧂Ă�
      }
      break;

    case 8:
//�^�C���J�E���^������
      sq_timer = 0;

      sq_mode = 9;//�t���O�𗧂Ă�
      break;

    case 9:
//�������l�ݒ�
      val1 = 250 ;
//pwm�o��
      analogWrite(PWM1, val1);
//Z�����[�^�[����
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 1);

//Z�����[�^�[���쎞�Ԏw��
      if (sq_timer > 550)
      {
        sq_mode = 10;//�t���O�𗧂Ă�
      }
      break;

    case 10:
//Y�����[�^�[��~
      digitalWrite(Pin5, 0);
      digitalWrite(Pin6, 0);
//X�����[�^�[����
      digitalWrite(Pin1, 1);
      digitalWrite(Pin2, 0);
//cds�Z���T�[�P�̒l��500�ȏゾ��
      if (ans1 >= 500) {

        sq_mode = 11;//�t���O�𗧂Ă�

      }

      break;

    case 11:
//X�����[�^�[��~
      digitalWrite(Pin1, 0);
      digitalWrite(Pin2, 0);
//Y�����[�^�[����
      digitalWrite(Pin3, 1);
      digitalWrite(Pin4, 0);
//cds�Z���T�[�Q�̒l��500�ȏゾ��
      if (ans2 >= 500) {
        sq_mode = 12;//�t���O�𗧂Ă�
      }

      break;

    case 12:
//Y�����[�^�[��~
      digitalWrite(Pin3, 0);
      digitalWrite(Pin4, 0);

      sq_mode = 13;//�t���O�𗧂Ă�
      break;

    case 13:
//�T�[�{���[�^�[�p�x�w��
      servo1.write( 60 );
      servo2.write( 60 );

      sq_mode = 0;//�t���O�𗧂Ă�
      break;

  }
}

/*
�^�C���J�E���^�쐬
*/

void loop() {

  delay(10);//10ms �X�L�����^�C�~���O

  //1�T�C�N���^�C�~���O���ƂɃJ�E���g�A�b�v����J�E���^
  if (sq_timer < (unsigned int) - 1)
  {
    sq_timer++;
  }

  Sequence();
}