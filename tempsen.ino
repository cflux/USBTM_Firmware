#include <SPI.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>;


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Constants
#define DHTPIN 21    // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino



//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.display();
}

void loop() {
  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp= dht.readTemperature();
  //Serial.print("Humidity: ");
  Serial.print("1.0,"); // ver
  Serial.print(hum);
  Serial.print(",");
  //Serial.print(" %, Temp: ");
  Serial.println(temp);
  //Serial.print(" Celsius");
  float f = (temp * 1.8) + 32;
  //Serial.print("(");
  //Serial.print(f);
  //Serial.println("F)");
  char tempc[8];
  dtostrf(f,6,2,tempc);
  char humc[8];
  dtostrf(hum,6,2,humc);
  display.clearDisplay();
  display.setCursor(0, 0);     // Start at top-left corner
  // put your main code here, to run repeatedly:
  display.write("T:");
  // get temp and put here:
  display.write(tempc);
  display.write("F\n");
  display.write("H:");
  display.write(humc);
  display.write("%");
  display.display();
  delay(2000); // Pause for 2 seconds
}
