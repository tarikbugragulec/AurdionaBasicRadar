
import processing.serial.*;

Serial myPort;  // Serial port nesnesi
float[] distances = new float[180];
float currentDistance = 0;

void setup() {
  size(800, 400);
  myPort = new Serial(this, "COM3", 9600);
  surface.setTitle("Control");
  for (int i = 0; i < 180; i++) {
    distances[i] = 0;
  }
}

void draw() {
  background(255);
  textAlign(CENTER, TOP);
  textSize(16);

  while (myPort.available() > 0) {
    String incomingData = myPort.readStringUntil('\n');
    if (incomingData != null) {
      float distance = float(trim(incomingData));
      updateDistances(distance);
      currentDistance = distance;
    }
  }

  drawGraph();
  drawCurrentDistance();
}

void updateDistances(float newDistance) {
  for (int i = 0; i < 179; i++) {
    distances[i] = distances[i + 1];
  }
  distances[179] = newDistance;
}

void drawGraph() {
  float scaleFactor = 2;
  float yOffset = height / 2;

  for (int i = 0; i < 179; i++) {
    float x1 = i * scaleFactor;
    float x2 = (i + 1) * scaleFactor;
    float y1 = yOffset - distances[i];
    float y2 = yOffset - distances[i + 1];

    // Grafik çizgilerinin rengini ayarla
    if (distances[i] > 100 || distances[i + 1] > 100) {
      stroke(0, 255, 0);  // Yeşil
    } else if (distances[i] > 30 || distances[i + 1] > 30) {
      stroke(0,0,255);  // Sarı
    } else {
      stroke(255, 0, 0);  // Kırmızı
    }

    line(x1, y1 + yOffset, x2, y2 + yOffset);
  }
}

void drawCurrentDistance() {
  // Mesafe eşik değerleri
  float yellowThreshold = 30;
  float redThreshold = 100;

  // Mesafe eşiğine göre renk belirle
  if (currentDistance > redThreshold) {
    fill(0, 255, 0);  // Yeşil
  } else if (currentDistance > yellowThreshold) {
    fill(0,0,255);  // Sarı
  } else {
    fill(255, 0, 0);  // Kırmızı
  }

  text("Mevcut Mesafe: " + nf(currentDistance, 0, 2) + " cm", width / 2, 10);

  // Arayüzü daha estetik hale getirmek için
  noStroke();
  ellipse(width / 2, height / 2, 30, 30);  // Uzaklık sembolü
}
