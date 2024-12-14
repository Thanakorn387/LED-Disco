// กำหนดขาที่ใช้งาน
#define SOUND_SENSOR A0    // เซนเซอร์เสียง
#define MODE_BUTTON 10     // ปุ่มเลือกโหมด
#define NUM_LEDS 8         // จำนวน LED
const int LED_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};  // ขา LED

// ตัวแปรสำหรับการประมวลผลเสียง
const int SAMPLE_SIZE = 50;
const int SOUND_THRESHOLD = 20;
const int MIN_SOUND = 100;
const int MAX_SOUND = 700;

// ตัวแปรสำหรับการควบคุมโหมด
int currentMode = 0;
const int NUM_MODES = 6;
unsigned long lastButtonPress = 0;
const int DEBOUNCE_DELAY = 200;  // ป้องกันการกดปุ่มซ้ำ

// ตัวแปรสำหรับเอฟเฟกต์พิเศษ
int chasePosition = 0;
bool chaseDirection = true;
int stackLevel = 0;
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(9600);
  
  // ตั้งค่าขา LED เป็น OUTPUT
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  // ตั้งค่าขาปุ่มกดเป็น INPUT_PULLUP
  pinMode(MODE_BUTTON, INPUT_PULLUP);
}

void loop() {
  // อ่านค่าเสียงและหาค่าเฉลี่ย
  int soundValue = 0;
  for (int i = 0; i < SAMPLE_SIZE; i++) {
    soundValue += analogRead(SOUND_SENSOR);
    delayMicroseconds(50);
  }
  soundValue /= SAMPLE_SIZE;

  // ตรวจสอบการกดปุ่ม
  if (digitalRead(MODE_BUTTON) == LOW) {
    if (millis() - lastButtonPress > DEBOUNCE_DELAY) {
      currentMode = (currentMode + 1) % NUM_MODES;
      lastButtonPress = millis();
      clearLEDs();  // ล้างไฟทั้งหมดเมื่อเปลี่ยนโหมด
      Serial.print("Mode changed to: ");
      Serial.println(currentMode);
    }
  }

  // แปลงค่าเสียงเป็นจำนวน LED
  int numLedsToLight = map(
    constrain(soundValue, MIN_SOUND, MAX_SOUND),
    MIN_SOUND, MAX_SOUND,
    0, NUM_LEDS
  );

  // เลือกรูปแบบการแสดงผลตามโหมด
  switch (currentMode) {
    case 0:
      vuMeter(numLedsToLight);          // ไฟวิ่งขึ้นลง
      break;
    case 1:
      centerExpand(numLedsToLight);     // ไฟขยายจากกลาง
      break;
    case 2:
      chaseEffect(numLedsToLight);      // ไฟวิ่งไล่
      break;
    case 3:
      stackEffect(numLedsToLight);      // ไฟสะสม
      break;
    case 4:
      pulseEffect(numLedsToLight);      // ไฟเต้นพร้อมกัน
      break;
    case 5:
      randomEffect(numLedsToLight);     // ไฟสุ่ม
      break;
  }
}

// โหมด 0: VU Meter
void vuMeter(int numLeds) {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], i < numLeds ? HIGH : LOW);
  }
}

// โหมด 1: Center Expand
void centerExpand(int numLeds) {
  int center = NUM_LEDS / 2;
  int halfLeds = numLeds / 2;
  
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i >= center - halfLeds && i <= center + halfLeds) {
      digitalWrite(LED_PINS[i], HIGH);
    } else {
      digitalWrite(LED_PINS[i], LOW);
    }
  }
}

// โหมด 2: Chase Effect
void chaseEffect(int numLeds) {
  clearLEDs();
  for (int i = 0; i < numLeds; i++) {
    int pos = (chasePosition + i) % NUM_LEDS;
    digitalWrite(LED_PINS[pos], HIGH);
  }
  
  if (millis() - lastUpdate > (110 - numLeds * 10)) {
    chasePosition = (chasePosition + 1) % NUM_LEDS;
    lastUpdate = millis();
  }
}

// โหมด 3: Stack Effect
void stackEffect(int numLeds) {
  // ปรับระดับการสะสมตามความดัง
  if (numLeds > stackLevel) {
    stackLevel = numLeds;
  } else if (millis() - lastUpdate > 50) {
    stackLevel = max(0, stackLevel - 1);
    lastUpdate = millis();
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], i < stackLevel ? HIGH : LOW);
  }
}

// โหมด 4: Pulse Effect
void pulseEffect(int numLeds) {
  static bool pulseState = false;
  
  if (millis() - lastUpdate > (110 - numLeds * 10)) {
    pulseState = !pulseState;
    lastUpdate = millis();
  }
  
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], (i < numLeds) ? pulseState : LOW);
  }
}

// โหมด 5: Random Effect
void randomEffect(int numLeds) {
  clearLEDs();
  for (int i = 0; i < numLeds; i++) {
    int randomLed = random(NUM_LEDS);
    digitalWrite(LED_PINS[randomLed], HIGH);
  }
  delay(50);
}

// ฟังก์ชั่นล้างไฟทั้งหมด
void clearLEDs() {
  for (int i = 0; i < NUM_LEDS; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
}