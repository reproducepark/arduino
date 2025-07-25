// 스위치가 연결된 디지털 핀 번호를 정의합니다.
const int SWITCH_PIN = 3; 

// 각 LED에 연결된 아두이노 핀 번호를 정의합니다.
#define RED_PIN 8
#define GREEN_PIN 9
#define BLUE_PIN 10

void setup() {
  // R, G, B 핀을 모두 출력(OUTPUT) 모드로 설정합니다.
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // 스위치 핀을 입력(INPUT) 모드로 설정하고, 내부 풀업 저항을 활성화합니다.
  // 내부 풀업 저항을 사용하면 스위치가 눌리지 않았을 때 HIGH, 눌렸을 때 LOW가 됩니다.
  pinMode(SWITCH_PIN, INPUT_PULLUP);

  // 시리얼 통신을 시작합니다 (디버깅용).
  Serial.begin(9600);
  Serial.println("Arduino Ready! Monitoring Digital Pin 3 for switch...");

}

// 원하는 색상을 출력하는 함수
// r, g, b 값은 각각 0~255 사이의 밝기를 의미합니다.
// 입력은 있지만 출력이 없는 함수입니다.
// void는 반환값이 없음을 의미합니다.
void setColor(int r, int g, int b) {
  // Cathode, Anode 두가지 종류
  // 공통 음극(Common Cathode) 방식은 값을 그대로 사용합니다.
  // 0(꺼짐) ~ 255(최대 밝기)
  analogWrite(RED_PIN, 255-r);
  analogWrite(GREEN_PIN, 255-g);
  analogWrite(BLUE_PIN, 255-b);

  // 현재 설정된 색상 값을 시리얼 모니터에 출력합니다.
  Serial.print("Setting color: R=");
  Serial.print(r);
  Serial.print(", G=");
  Serial.print(g);
  Serial.print(", B=");
  Serial.println(b);
}

void loop() {
  // 스위치 핀의 상태를 읽어옵니다.
  // INPUT_PULLUP 모드에서는 스위치가 눌리지 않으면 HIGH (1), 눌리면 LOW (0)가 됩니다.
  int switchState = digitalRead(SWITCH_PIN);

  // 시리얼 모니터에 현재 스위치 상태를 출력합니다.
  Serial.print("Switch State: ");
  Serial.println(switchState);

  // 스위치가 눌렸을 때 (상태가 LOW일 때)
  if (switchState == LOW) {
    Serial.println("Switch Pressed! LED ON.");
    setColor(255, 0, 0);
    delay(1000); // 1초 대기

    // 초록색 (Green)
    setColor(0, 255, 0);
    delay(1000);

    // 파란색 (Blue)
    setColor(0, 0, 255);
    delay(1000);

    // 노란색 (Yellow) - 빨강과 초록을 섞음
    setColor(255, 255, 0);
    delay(1000);

    // 보라색 (Purple) - 빨강과 파랑을 섞음
    setColor(255, 0, 255);
    delay(1000);

    // 하늘색 (Cyan) - 초록과 파랑을 섞음
    setColor(0, 255, 255);
    delay(1000);

    // 흰색 (White) - 모든 색을 최대로 섞음
    setColor(255, 255, 255);
    delay(1000);
    
    // LED 끄기
    setColor(0, 0, 0);
    delay(1000);
  } 
  // 스위치가 눌리지 않았을 때 (상태가 HIGH일 때)
  else {
    Serial.println("Switch Released! LED OFF.");
    setColor(0, 0, 0);
    delay(100);
  }

  delay(100); // 스위치 채터링 방지 및 안정적인 읽기를 위한 짧은 대기
}