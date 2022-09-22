const int TRIG = 4;
const int ECHO = 3;
const int ENA = 5;
const int ENB = 6;
const int IN1 = 7;
const int IN2 = 8;
const int IN3 = 9;
const int IN4 = 10;

void setup () 
{
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    Serial.begin(9600);
    
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    digitalWrite(IN1, HIGH);
    digitalWrite(IN3, HIGH);

}

void loop () 
{    
    if(distance() >= 20)
    {
      // направление колёс вперёд
      digitalWrite(IN1, HIGH);
      digitalWrite(IN3, HIGH);

      // подача мощности
      analogWrite(ENA, 100);
      analogWrite(ENB, 100);
    }
    else
    {
      // выключаем направление вперёд
      digitalWrite(IN1, LOW);
      digitalWrite(IN3, LOW);

      // убираем мощность
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);

      // ждём 1 секунду
      delay(1000);

      // объявляем и определяем переменные для отсчёта времени для поворота на ~90 градусов
      unsigned long start = millis();
      unsigned long end = start;

      while((end - start <= 300))
      {
        // включаем направления вперёд и назад для разных колёс для поворота
        digitalWrite(IN1, HIGH);
        digitalWrite(IN4, HIGH);

        // включаем мощность
        analogWrite(ENA, 130);
        analogWrite(ENB, 130);
        
        // получаем текущий момент времени для проверки
        end = millis();
      }

      // после поворта выключаем направление
      digitalWrite(IN1, LOW);
      digitalWrite(IN4, LOW);    

      // выключаем мощность
      analogWrite(ENA, 0);
      analogWrite(ENB, 0);  

    }
    
}

int distance() 
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW) ;
    long t = pulseIn(ECHO, HIGH);
    int s = t / 57;
    Serial.println(s);
    return s;
}