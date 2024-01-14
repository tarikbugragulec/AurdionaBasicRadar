import processing.serial.*;

Serial myPort;

String angle = "";
String distance = "";
String noObject;
float pixsDistance;
int iAngle, iDistance;

void setup() {
  size(540, 720);  // Genişlik ve yükseklik değerleri yer değiştirdi
  smooth();
  myPort = new Serial(this, "COM3", 9600);
  myPort.bufferUntil('.');
}

void draw() {
  background(255);

  processData();

  fill(98, 245, 31);
  noStroke();
  rect(0, 0, width, 1010);

  fill(98, 245, 31);
  drawRadar();
  drawLine();
  drawObject();
  drawText();
}

void processData() {
  while (myPort.available() > 0) {
    String data = myPort.readStringUntil('.');
    if (data != null) {
      data = data.substring(0, data.length() - 1);
      int index1 = data.indexOf(",");
      
      if (index1 != -1) {
        angle = data.substring(0, index1);
        distance = data.substring(index1 + 1);
        
        iAngle = Integer.parseInt(angle);
        iDistance = Integer.parseInt(distance);
      }
    }
  }
}

void drawRadar() {
  pushMatrix();
  translate(960, 1000);
  fill(0, 50);
  strokeWeight(2);
  stroke(98, 245, 31);
  ellipse(0, 0, 1800, 1800);
  ellipse(0, 0, 1400, 1400);
  ellipse(0, 0, 1000, 1000);
  ellipse(0, 0, 600, 600);
  line(-960, 0, 960, 0);
  line(0, 0, -960 * cos(radians(30)), -960 * sin(radians(30)));
  line(0, 0, -960 * cos(radians(60)), -960 * sin(radians(60)));
  line(0, 0, -960 * cos(radians(90)), -960 * sin(radians(90)));
  line(0, 0, -960 * cos(radians(120)), -960 * sin(radians(120)));
  line(0, 0, -960 * cos(radians(150)), -960 * sin(radians(150)));
  line(-960 * cos(radians(30)), 0, 960, 0);
  popMatrix();
}

void drawObject() {
  pushMatrix();
  translate(960, 1000);
  strokeWeight(9);
  stroke(255, 10, 10);
  pixsDistance = iDistance * 22.5;
  if (iDistance < 40) {
    line(pixsDistance * cos(radians(iAngle)), -pixsDistance * sin(radians(iAngle)), 
         950 * cos(radians(iAngle)), -950 * sin(radians(iAngle)));
  }
  popMatrix();
}

void drawLine() {
  pushMatrix();
  translate(960, 1000);
  strokeWeight(9);
  stroke(30, 250, 60);
  line(0, 0, 950 * cos(radians(iAngle)), -950 * sin(radians(iAngle)));
  popMatrix();
}

void drawText() {
  pushMatrix();
  if (iDistance > 40) {
    noObject = "Out of Range";
  } else {
    noObject = "In Range";
  }
  fill(0);
  noStroke();
  rect(0, 1010, width, 1080);
  fill(98, 245, 31);
  textSize(25);
  text("10cm", 1180, 990);
  text("20cm", 1380, 990);
  text("30cm", 1580, 990);
  text("40cm", 1780, 990);
  textSize(40);
  text("Object: " + noObject, 240, 1050);
  text("Angle: " + iAngle + " °", 1050, 1050);
}
