
#include <DFPlayerMini_Fast.h>

// Khai báo các chân kết nối với cảm biến và module phát nhạc
const int trigPin1 = 9;
const int echoPin1 = 10;
const int trigPin2 = 6;
const int echoPin2 = 7;
const int trigPin3 = 4;
const int echoPin3 = 5;

// Khai báo chân TX, RX kết nối với module phát nhạc
const int TX = 1;
const int RX = 0;

// Khởi tạo đối tượng HardwareSerial để giao tiếp với module phát nhạc
HardwareSerial mySerial(1); // Sử dụng Serial1 với chân TX=1, RX=0 trên Arduino Nano

// Khởi tạo đối tượng DFPlayerMini_Fast để điều khiển module phát nhạc
DFPlayerMini_Fast myDFPlayer;

void setup() {
  // Khởi tạo chế độ giao tiếp Serial với tốc độ 9600 baud
  Serial.begin(9600);

  // Thiết lập các chân kết nối với cảm biến và loa báo động
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  // Khởi tạo kết nối với module phát nhạc
  mySerial.begin(9600, SERIAL_8N1, RX, TX); // Baud rate, data format, RX pin, TX pin
  delay(1000);
  if (!myDFPlayer.begin(mySerial)) {  
    Serial.println("Error initializing DFPlayer!");
    while (true);
  }
  Serial.println("DFPlayer initialized!");
}

void loop() {
  // Khai báo biến để lưu trữ thời gian và khoảng cách đo được từ từng cảm biến
  long duration1, distance1, duration2, distance2, duration3, distance3;

  // Đo khoảng cách từ cảm biến 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // Đo khoảng cách từ cảm biến 2
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2 = duration2 * 0.034 / 2;

 // Đo khoảng cách từ cảm biến 3
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
duration3 = pulseIn(echoPin3, HIGH);
distance3 = duration3 * 0.034 / 2;

// Hiển thị khoảng cách lên Serial Monitor để kiểm tra
Serial.print("Distance 1: ");
Serial.print(distance1);
Serial.print(" cm | Distance 2: ");
Serial.print(distance2);
Serial.print(" cm | Distance 3: ");
Serial.print(distance3);
Serial.println(" cm");

// Nếu khoảng cách đo được từ cảm biến 1, 2 hoặc 3 nhỏ hơn 30cm thì bật loa báo động và phát nhạc
if (distance1 < 50 || distance2 < 50 || distance3 < 50) {
  myDFPlayer.play(1);
  delay(500);
}

// Đợi 500ms để đo khoảng cách tiếp theo
delay(500);
}

// Chú thích:

// - Hàm pulseIn(pin, value) sẽ trả về thời gian tính bằng micro giây mà tín hiệu trên chân pin nằm ở trạng thái "value"
// - Khoảng cách tính bằng công thức: khoảng cách = thời gian x vận tốc âm thanh / 2
// - myDFPlayer.play(1) sẽ phát nhạc từ thẻ nhớ SD ở file số 0001.mp3 trên module phát nhạc. Chú ý rằng file nhạc phải được đặt tên theo định dạng bốn chữ số (vd: 0001.mp3)






