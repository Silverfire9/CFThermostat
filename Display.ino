// Screen Dimensions
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

// TNG LCARS colour scheme
// #define RGB8BIT
#define RGB565
#ifdef RGB8BIT
  #define AFRICAN_VIOLET (204, 136, 255)
  #define ALMOND (255, 170, 144)
  #define ALMOND_CREME (255, 187, 170)
  #define BEIGE (255, 204, 153)
  #define BLACK (0, 0, 0)
  #define BLACK_BROWN (204, 102, 102)

  #define BLUE (68, 85, 255)
  #define BUTTERSCOTCH (255, 153, 102)
  #define GOLD (255, 170, 0)
  #define GREEN (51, 204, 153)
  #define GREY (102, 102, 136)
  #define GREY_BLUE (153, 153, 204)

  #define ICE_BLUE (136, 204, 255)
  #define LIGHT_BLUE (119, 136, 255)
  #define LIGHT_PEACH (255, 153, 102)
  #define LILAC (204, 51, 255)
  #define MAGENTA (204, 68, 153)
  #define MARS (255, 34, 0)

  #define ORANGE (255, 119, 0)
  #define PEACH (255, 136, 102)
  #define PINK (204, 102, 153)
  #define PURPLE (204, 153, 204)
  #define RED (221, 68, 68)
  #define SKY (170, 170, 255)

  #define SPACE_WHITE (245, 246, 250)
  #define SUNFLOWER (255, 204, 102)
  #define TEXT (204, 119, 255)
  #define TOMATO (255, 85, 85)
  #define VIOLET (153, 68, 255)
  #define VIOLET_CREME (221, 187, 255)
  #define WHITE (255, 255, 225)
  #define YELLOW (255, 204, 51)
#endif
#ifdef RGB565
  #define AFRICAN_VIOLET 0xCC5F
  #define ALMOND 0xFD52
  #define ALMOND_CREME 0xFDD5
  #define BEIGE 0xFE73
  #define BLACK 0x0000
  #define BLACK_BROWN 0xCB2C

  #define BLUE 0x42BF
  #define BUTTERSCOTCH 0xFCCC
  #define GOLD 0xFD40
  #define GREEN 0x3663
  #define GREY 0x6331
  #define GREY_BLUE 0x9CD9

  #define ICE_BLUE 0x8E7F
  #define LIGHT_BLUE 0x7C5F
  #define LIGHT_PEACH 0xFCCC
  #define LILAC 0xC99F
  #define MAGENTA 0xCA32
  #define MARS 0xF900

  #define ORANGE 0xFBA0
  #define PEACH 0xFC4C
  #define PINK 0xCB33
  #define PURPLE 0xCCD9
  #define RED 0xDA28
  #define SKY 0xAD5F

  #define SPACE_WHITE 0xF7BE
  #define SUNFLOWER 0xFE6C
  #define TEXT 0xCBBF
  #define TOMATO 0xFAAA
  #define VIOLET 0x9A3F
  #define VIOLET_CREME 0xD5FF
  #define WHITE 0xFFFC
  #define YELLOW 0xFE66
#endif

void setScreenBrightness(char bright) {

  ledcWrite(pin_BL, bright);
  Serial.print("Setting screen brightness to ");
  Serial.print(int(bright));
  Serial.println("/15");
}

void drawBottomBar() {
  int buffer = 4;
  int barHeight = 15;
  int barTop = SCREEN_HEIGHT - 15;

  // Serial.print("Drawing a border bar "); Serial.print(barHeight); Serial.print("px thick with the top corner @ (0,"); Serial.print(barTop); Serial.print(") and a "); Serial.print(buffer); Serial.println("px buffer.");
  screen.fillCircle(((barHeight - 1) / 2) + buffer, barTop + ((barHeight - 1) / 2), (barHeight - 1) / 2, LIGHT_PEACH);  // Bottom Bar
  screen.fillRect(((barHeight - 1) / 2) + buffer + 1, barTop, (barHeight - 1) / 2, barHeight, LIGHT_PEACH);
  screen.fillRect(barHeight + (buffer * 2), barTop, SCREEN_WIDTH - (barHeight * 2) - (buffer * 4), barHeight, AFRICAN_VIOLET);
  screen.fillRect(SCREEN_WIDTH - barHeight - buffer, barTop, (barHeight - 1) / 2, barHeight, LIGHT_PEACH);
  screen.fillCircle(SCREEN_WIDTH - ((barHeight - 1) / 2) - buffer, barTop + ((barHeight - 1) / 2), (barHeight - 1) / 2, LIGHT_PEACH);
}

void drawTopBar(char text[5]) {
  int XPos = 19;
  int YPos = 0;
  int barHeight = 15;
  int buffer = 4;
  char substring[4];

  strncpy(substring, text, 3);
  // Serial.print("Text: "); Serial.print(text); Serial.print(", Substring: ");Serial.println(substring);
  screen.fillCircle(((barHeight - 1) / 2) + buffer, ((barHeight - 1) / 2), (barHeight - 1) / 2, LIGHT_PEACH);  // Top Bar
  screen.fillRect(((barHeight - 1) / 2) + buffer + 1, 0, (barHeight - 1) / 2, barHeight, LIGHT_PEACH);
  screen.fillRect(SCREEN_WIDTH - barHeight - buffer, 0, (barHeight - 1) / 2, barHeight, LIGHT_PEACH);
  screen.fillCircle(SCREEN_WIDTH - ((barHeight - 1) / 2) - buffer, ((barHeight - 1) / 2), (barHeight - 1) / 2, LIGHT_PEACH);
  screen.fillRect(barHeight + (buffer * 2), 0, SCREEN_WIDTH - (barHeight * 2) - (buffer * 4), barHeight, AFRICAN_VIOLET);
  screen.drawFastVLine(XPos, YPos, 15, BLACK);
  screen.drawFastVLine(XPos + 1, YPos, 15, BLACK);
  screen.drawFastVLine(XPos + 2, YPos, 15, BLACK);
  screen.drawFastVLine(XPos + 3, YPos, 15, BLACK);
  if (strcmp(text, "Booting") == 0) {
    screen.drawFastVLine(XPos + 4, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 4, YPos + 13, 2, BLACK);  // B
    screen.drawFastVLine(XPos + 5, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 5, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 6, YPos, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 6, YPos + 2, 3, BLACK); screen.drawFastVLine(XPos + 6, YPos + 5, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 6, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 6, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 6, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 7, YPos, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 7, YPos + 2, 3, BLACK); screen.drawFastVLine(XPos + 7, YPos + 5, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 7, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 7, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 7, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 8, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 8, YPos + 13, 2, BLACK);
    screen.drawPixel(XPos + 9, YPos, BLACK); screen.drawFastVLine(XPos + 9, YPos + 1, 4, LIGHT_PEACH); screen.drawPixel(XPos + 9, YPos + 5, BLACK); screen.drawFastVLine(XPos + 9, YPos + 6, 6, LIGHT_PEACH); screen.drawFastVLine(XPos + 9, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 10, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 11, YPos, 3, BLACK); screen.drawFastVLine(XPos + 11, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 11, YPos + 12, 3, BLACK);  // o
    screen.drawFastVLine(XPos + 12, YPos, 2, BLACK); screen.drawFastVLine(XPos + 12, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 12, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 13, YPos, 2, BLACK); screen.drawFastVLine(XPos + 13, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 13, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 13, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 13, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 14, YPos, 2, BLACK); screen.drawFastVLine(XPos + 14, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 14, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 14, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 14, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 15, YPos, 2, BLACK); screen.drawFastVLine(XPos + 15, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 15, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 16, YPos, 3, BLACK); screen.drawFastVLine(XPos + 16, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 16, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 17, YPos, 15, BLACK); screen.drawFastVLine(XPos + 18, YPos, 3, BLACK); screen.drawFastVLine(XPos + 18, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 18, YPos + 12, 3, BLACK);  // o
    screen.drawFastVLine(XPos + 19, YPos, 2, BLACK); screen.drawFastVLine(XPos + 19, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 19, YPos + 13, 2, BLACK); 
    screen.drawFastVLine(XPos + 20, YPos, 2, BLACK); screen.drawFastVLine(XPos + 20, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 20, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 20, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 20, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 21, YPos, 2, BLACK); screen.drawFastVLine(XPos + 21, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 21, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 21, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 21, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 22, YPos, 2, BLACK); screen.drawFastVLine(XPos + 22, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 22, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 23, YPos, 3, BLACK); screen.drawFastVLine(XPos + 23, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 23, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 24, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 25, YPos, 2, BLACK); screen.drawFastVLine(XPos + 25, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 25, YPos + 4, 11, BLACK);  // t
    screen.drawFastVLine(XPos + 26, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 26, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 27, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 27, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 28, YPos, 2, BLACK); screen.drawFastVLine(XPos + 28, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 28, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 28, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 28, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 29, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 30, YPos, 2, LIGHT_PEACH); screen.drawPixel(XPos + 30, YPos + 2, BLACK); screen.drawFastVLine(XPos + 30, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 30, YPos + 13, 2, BLACK);  // i
    screen.drawFastVLine(XPos + 31, YPos, 2, LIGHT_PEACH); screen.drawPixel(XPos + 31, YPos + 2, BLACK); screen.drawFastVLine(XPos + 31, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 31, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 32, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 33, YPos, 2, BLACK); screen.drawFastVLine(XPos + 33, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 33, YPos + 13, 2, BLACK);  // n
    screen.drawFastVLine(XPos + 34, YPos, 3, BLACK); screen.drawFastVLine(XPos + 34, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 34, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 35, YPos + 4, 11, BLACK);
    screen.drawFastVLine(XPos + 36, YPos, 2, BLACK); screen.drawFastVLine(XPos + 36, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 36, YPos + 4, 11, BLACK);
    screen.drawFastVLine(XPos + 37, YPos, 2, BLACK); screen.drawFastVLine(XPos + 37, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 37, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 38, YPos, 3, BLACK); screen.drawFastVLine(XPos + 38, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 38, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 39, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 40, YPos, 3, BLACK); screen.drawFastVLine(XPos + 40, YPos + 3, 6, LIGHT_PEACH); screen.drawFastVLine(XPos + 40, YPos + 9, 2, BLACK); screen.drawFastVLine(XPos + 40, YPos + 11, 3, LIGHT_PEACH); screen.drawPixel(XPos + 40, YPos + 14, BLACK);  // g
    screen.drawFastVLine(XPos + 41, YPos, 2, BLACK); screen.drawFastVLine(XPos + 41, YPos + 2, 8, LIGHT_PEACH); screen.drawPixel(XPos + 41, YPos + 10, BLACK); screen.drawFastVLine(XPos + 41, YPos + 11, 4, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 42, YPos, 2, BLACK); screen.drawFastVLine(XPos + 42, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 42, YPos + 4, 4, BLACK); screen.drawFastVLine(XPos + 42, YPos + 8, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 42, YPos + 10, 3, BLACK); screen.drawFastVLine(XPos + 42, YPos + 13, 2, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 43, YPos, 2, BLACK); screen.drawFastVLine(XPos + 43, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 43, YPos + 4, 4, BLACK); screen.drawFastVLine(XPos + 43, YPos + 8, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 43, YPos + 10, 3, BLACK); screen.drawFastVLine(XPos + 43, YPos + 13, 2, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 44, YPos, 2, BLACK); screen.drawFastVLine(XPos + 44, YPos + 2, 13, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 45, YPos, 3, BLACK); screen.drawFastVLine(XPos + 45, YPos + 3, 11, LIGHT_PEACH); screen.drawPixel(XPos + 45, YPos + 14, BLACK);
    screen.drawFastVLine(XPos + 46, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 47, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 48, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 49, YPos, 15, BLACK);
  } else if (strcmp(text, "Main") == 0) {
    screen.drawFastVLine(XPos, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 1, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 2, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 3, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 4, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 4, YPos + 13, 2, BLACK);  // L
    screen.drawFastVLine(XPos + 5, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 5, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 6, YPos, 11, BLACK); screen.drawFastVLine(XPos + 6, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 6, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 7, YPos, 11, BLACK); screen.drawFastVLine(XPos + 7, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 7, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 8, YPos, 11, BLACK); screen.drawFastVLine(XPos + 8, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 8, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 9, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 10, YPos, 2, LIGHT_PEACH); screen.drawPixel(XPos + 10, YPos + 2, BLACK); screen.drawFastVLine(XPos + 10, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 10, YPos + 13, 2, BLACK);  // i
    screen.drawFastVLine(XPos + 11, YPos, 2, LIGHT_PEACH); screen.drawPixel(XPos + 11, YPos + 2, BLACK); screen.drawFastVLine(XPos + 11, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 11, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 12, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 13, YPos, 2, BLACK); screen.drawFastVLine(XPos + 13, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 13, YPos + 4, 11, BLACK);  // f
    screen.drawPixel(XPos + 14, YPos, BLACK); screen.drawFastVLine(XPos + 14, YPos + 1, 12, LIGHT_PEACH); screen.drawFastVLine(XPos + 14, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 15, YPos, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 15, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 16, YPos, 4, LIGHT_PEACH); screen.drawFastVLine(XPos + 16, YPos + 4, 11, BLACK);
    screen.drawFastVLine(XPos + 17, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 18, YPos, 3, BLACK); screen.drawFastVLine(XPos + 18, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 18, YPos + 12, 3, BLACK);  // e
    screen.drawFastVLine(XPos + 19, YPos, 2, BLACK); screen.drawFastVLine(XPos + 19, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 19, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 20, YPos, 2, BLACK); screen.drawFastVLine(XPos + 20, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 20, YPos + 4, 2, BLACK); screen.drawFastVLine(XPos + 20, YPos + 6, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 20, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos + 20, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 20, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 21, YPos, 2, BLACK); screen.drawFastVLine(XPos + 21, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 21, YPos + 4, 2, BLACK); screen.drawFastVLine(XPos + 21, YPos + 6, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 21, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos + 21, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 21, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 22, YPos, 2, BLACK); screen.drawFastVLine(XPos + 22, YPos + 2, 6, LIGHT_PEACH); screen.drawPixel(XPos + 22, YPos + 8, BLACK); screen.drawFastVLine(XPos + 22, YPos + 9, 4, LIGHT_PEACH); screen.drawFastVLine(XPos + 22, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 23, YPos, 3, BLACK); screen.drawFastVLine(XPos + 23, YPos + 3, 5, LIGHT_PEACH); screen.drawPixel(XPos + 23, YPos + 8, BLACK); screen.drawFastVLine(XPos + 23, YPos + 9, 3, LIGHT_PEACH); screen.drawFastVLine(XPos + 23, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 24, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 25, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 26, YPos, 15, BLACK);
    screen.drawPixel(XPos + 27, YPos, BLACK); screen.drawFastVLine(XPos + 27, YPos + 1, 5, LIGHT_PEACH); screen.drawFastVLine(XPos + 27, YPos + 6, 2, BLACK); screen.drawFastVLine(XPos + 27, YPos + 8, 4, LIGHT_PEACH); screen.drawFastVLine(XPos + 27, YPos + 12, 3, BLACK);  // S
    screen.drawFastVLine(XPos + 28, YPos, 7, LIGHT_PEACH); screen.drawPixel(XPos + 28, YPos + 7, BLACK); screen.drawFastVLine(XPos + 28, YPos + 8, 5, LIGHT_PEACH); screen.drawFastVLine(XPos + 28, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 29, YPos, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 29, YPos + 2, 3, BLACK); screen.drawFastVLine(XPos + 29, YPos + 5, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 29, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 29, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 29, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 30, YPos, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 30, YPos + 2, 4, BLACK); screen.drawFastVLine(XPos + 30, YPos + 6, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 30, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos + 30, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 30, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 31, YPos, 5, LIGHT_PEACH); screen.drawPixel(XPos + 31, YPos + 5, BLACK); screen.drawFastVLine(XPos + 31, YPos + 6, 7, LIGHT_PEACH); screen.drawFastVLine(XPos + 31, YPos + 13, 2, BLACK);
    screen.drawPixel(XPos + 32, YPos + 8, BLACK); screen.drawFastVLine(XPos + 32, YPos + 1, 4, LIGHT_PEACH); screen.drawFastVLine(XPos + 32, YPos + 5, 2, BLACK); screen.drawFastVLine(XPos + 32, YPos + 7, 5, LIGHT_PEACH); screen.drawFastVLine(XPos + 32, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 33, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 34, YPos, 2, BLACK); screen.drawFastVLine(XPos + 34, YPos + 2, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 34, YPos + 12, 3, BLACK);  // u
    screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 35, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 36, YPos, 11, BLACK); screen.drawFastVLine(XPos + 36, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 36, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 37, YPos, 11, BLACK); screen.drawFastVLine(XPos + 37, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 37, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 38, YPos, 2, BLACK); screen.drawFastVLine(XPos + 38, YPos + 2, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 38, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 39, YPos, 2, BLACK); screen.drawFastVLine(XPos + 39, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 39, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 40, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 41, YPos, 2, BLACK); screen.drawFastVLine(XPos + 41, YPos + 2, 13, LIGHT_PEACH);  // p
    screen.drawFastVLine(XPos + 42, YPos, 2, BLACK); screen.drawFastVLine(XPos + 42, YPos + 2, 13, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 43, YPos, 2, BLACK); screen.drawFastVLine(XPos + 43, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 43, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 43, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 43, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 44, YPos, 2, BLACK); screen.drawFastVLine(XPos + 44, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 44, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 44, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 44, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 45, YPos, 2, BLACK); screen.drawFastVLine(XPos + 45, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 45, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 46, YPos, 3, BLACK); screen.drawFastVLine(XPos + 46, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 46, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 47, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 48, YPos, 2, BLACK); screen.drawFastVLine(XPos + 48, YPos + 2, 13, LIGHT_PEACH);  // p
    screen.drawFastVLine(XPos + 49, YPos, 2, BLACK); screen.drawFastVLine(XPos + 49, YPos + 2, 13, LIGHT_PEACH);
    screen.drawFastVLine(XPos + 50, YPos, 2, BLACK); screen.drawFastVLine(XPos + 50, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 50, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 50, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 50, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 51, YPos, 2, BLACK); screen.drawFastVLine(XPos + 51, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 51, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 51, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 51, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 52, YPos, 2, BLACK); screen.drawFastVLine(XPos + 52, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 52, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 53, YPos, 3, BLACK); screen.drawFastVLine(XPos + 53, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 53, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 54, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 55, YPos, 3, BLACK); screen.drawFastVLine(XPos + 55, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 55, YPos + 12, 3, BLACK);  // o
    screen.drawFastVLine(XPos + 56, YPos, 2, BLACK); screen.drawFastVLine(XPos + 56, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 56, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 57, YPos, 2, BLACK); screen.drawFastVLine(XPos + 57, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 57, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 57, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 57, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 58, YPos, 2, BLACK); screen.drawFastVLine(XPos + 58, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 58, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 58, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 58, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 59, YPos, 2, BLACK); screen.drawFastVLine(XPos + 59, YPos + 2, 11, LIGHT_PEACH); screen.drawFastVLine(XPos + 59, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 60, YPos, 3, BLACK); screen.drawFastVLine(XPos + 60, YPos + 3, 9, LIGHT_PEACH); screen.drawFastVLine(XPos + 60, YPos + 12, 3, BLACK);
    screen.drawFastVLine(XPos + 61, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 62, YPos, 2, BLACK); screen.drawFastVLine(XPos + 62, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 62, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 63, YPos, 3, BLACK); screen.drawFastVLine(XPos + 63, YPos + 3, 10, LIGHT_PEACH); screen.drawFastVLine(XPos + 63, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 64, YPos, 2, BLACK); screen.drawFastVLine(XPos + 64, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 64, YPos + 4, 11, BLACK);
    screen.drawFastVLine(XPos + 65, YPos, 2, BLACK); screen.drawFastVLine(XPos + 65, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 65, YPos + 4, 11, BLACK);
    screen.drawFastVLine(XPos + 66, YPos, 2, BLACK); screen.drawFastVLine(XPos + 66, YPos + 2, 6, LIGHT_PEACH); screen.drawFastVLine(XPos + 66, YPos + 8, 7, BLACK);
    screen.drawFastVLine(XPos + 67, YPos, 3, BLACK); screen.drawFastVLine(XPos + 67, YPos + 3, 5, LIGHT_PEACH); screen.drawFastVLine(XPos + 67, YPos + 8, 7, BLACK);
    screen.drawFastVLine(XPos + 68, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 69, YPos, 2, BLACK); screen.drawFastVLine(XPos + 69, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 69, YPos + 4, 11, BLACK);  // t
    screen.drawFastVLine(XPos + 70, YPos + 2, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 70, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 71, YPos + 2, 13, LIGHT_PEACH); screen.drawFastVLine(XPos + 71, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 72, YPos, 2, BLACK); screen.drawFastVLine(XPos + 72, YPos + 2, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 72, YPos + 4, 7, BLACK); screen.drawFastVLine(XPos + 72, YPos + 11, 2, LIGHT_PEACH); screen.drawFastVLine(XPos + 72, YPos + 13, 2, BLACK);
    screen.drawFastVLine(XPos + 73, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 74, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 75, YPos, 15, BLACK);
    screen.drawFastVLine(XPos + 76, YPos, 15, BLACK);
  } else if (strcmp(substring, "Set") == 0) {
    char slice[2];

    screen.fillRect(XPos, YPos + 3, 2, 5, LIGHT_PEACH);        // S
    screen.fillRect(XPos + 8, YPos + 4, 2, 9, LIGHT_PEACH);    // e
    screen.fillRect(XPos + 16, YPos + 1, 2, 13, LIGHT_PEACH);  // t
    screen.fillRect(XPos + 22, YPos + 1, 2, 13, LIGHT_PEACH);  // t
    screen.fillRect(XPos + 28, YPos + 1, 2, 2, LIGHT_PEACH);   // i
    screen.fillRect(XPos + 32, YPos + 3, 2, 11, LIGHT_PEACH);  // n
    screen.fillRect(XPos + 40, YPos + 3, 2, 9, LIGHT_PEACH);   // g
    screen.fillRect(XPos + 48, YPos + 4, 2, 4, LIGHT_PEACH);   // s
    // Serial.print(", Slice: "); Serial.println(text[3]);
    strncpy(slice, text + 3, 2);
    if (strcmp(slice, "1") == 0) {  // 1
      // Serial.println("Adding #1 to title");
      screen.fillRect(XPos, YPos + 2, 2, 2, PEACH);
    } else if (strcmp(slice, "2") == 0) {  // 2
      // Serial.println("Adding #2 to title");
      screen.fillRect(XPos, YPos + 1, 2, 4, PEACH);
    } else if (strcmp(slice, "3") == 0) {  // 3
      // Serial.println("Adding #3 to title");
      screen.fillRect(XPos, YPos + 1, 2, 4, PEACH);
    } else if (strcmp(slice, "4") == 0) {  // 4
      screen.fillRect(XPos, YPos + 6, 2, 5, PEACH);
    } else if (strcmp(slice, "5") == 0) {  // 5
      screen.fillRect(XPos, YPos, 2, 6, PEACH);

    } else {
      screen.print("Coding not done for #");
      screen.println(slice);
    }
  }
}

void drawHistoryGraph() {
  int graph_height = 50;
  int graph_width = HISTORY_SIZE;
  int graph_top = SCREEN_HEIGHT - 15 - 4 - graph_height;
  int temp_max = settings.tempSet + 10;
  int temp_min = 0;
  int plot_loc = graph_top + graph_height;

  screen.drawRect(0, graph_top - 1, graph_width + 2, graph_height + 2, PEACH);
  for (int y = 0; y < HISTORY_SIZE; y++) {
    if (!isnan(tempHistory[y])) {
      // Humidity reading
      int bar_height = map(humidHistory[y], 0, 100, 0, graph_height);
      plot_loc = graph_top + graph_height - bar_height;
      screen.setCursor(4, graph_top + graph_height - 11);
      screen.setTextColor(WHITE, BLUE);
      screen.setTextSize(1);
      // Serial.print("Humidity max: "); Serial.print(100); Serial.print(" - Graph top:         "); Serial.println(graph_top);
      // Serial.print("Humidity act: "); Serial.print(humidHistory[y]); Serial.print(" - Graph plot height: "); Serial.println(plot_loc);
      // Serial.print("Humidity min: "); Serial.print(0); Serial.print(" - Graph bottom:      "); Serial.println(graph_top+graph_height);
      screen.drawFastVLine(y + 1, graph_top, graph_height - bar_height, BLACK);
      screen.drawFastVLine(y + 1, plot_loc, bar_height, BLUE);
      screen.print("Humidity: "); screen.print(humidityCurr, 0); screen.println("%");
      // Temperature setting
      plot_loc = graph_top + graph_height - map(settings.tempSet, temp_min, temp_max, 0, graph_height);
      // Serial.print("Value max: "); Serial.print(temp_max); Serial.print(" - Graph top:         "); Serial.println(graph_top);
      // Serial.print("Value set: "); Serial.print(settings.tempSet); Serial.print(" - Graph plot height: "); Serial.println(plot_loc);
      // Serial.print("Value min: "); Serial.print(temp_min); Serial.print(" - Graph bottom:      "); Serial.println(graph_top+graph_height);
      screen.drawPixel(y + 1, plot_loc, LIGHT_BLUE);
      // screen.drawPixel(y*2+1, plot_loc, LIGHT_BLUE);
      // Temperature reading
      plot_loc = graph_top + graph_height - map(tempHistory[y], temp_min, temp_max, 0, graph_height);
      // Serial.print("Temp max: "); Serial.print(temp_max); Serial.print(" - Graph top:         "); Serial.println(graph_top);
      // Serial.print("Temp act: "); Serial.print(tempHistory[y]); Serial.print(" - Graph plot height: "); Serial.println(plot_loc);
      // Serial.print("Temp min: "); Serial.print(temp_min); Serial.print(" - Graph bottom:      "); Serial.println(graph_top+graph_height);
      screen.drawPixel(y + 1, plot_loc, VIOLET_CREME);
      // screen.drawPixel(y*2+1, plot_loc, ICE_BLUE);
    }
  }
}

void drawBigNum(float number, int XPos, int YPos, uint16_t colour) {
  char num[6];
  char digit[2];
  int space = 4;

  dtostrf(number, 6, 1, num);
  #ifdef PROGTEXT
  Serial.print("Number to display: ");
  Serial.println(num);
  #endif
  for (int count = 0; count < 6; count++) {
    int width;
    // Serial.print("Character "); Serial.print(count); Serial.print(": "); Serial.print(num[count]); Serial.print(", Position: "); Serial.print(XPos); Serial.print(","); Serial.println(YPos);
    if (num[count] == '-') {
      for (int i = 0; i <= 20; i++) {screen.drawFastVLine(XPos + i, YPos, 46, BLACK); screen.drawFastVLine(XPos + i, YPos + 46, 13, colour); screen.drawFastVLine(XPos + i, YPos + 59, 46, BLACK);}
      screen.fillRect(XPos + 21, YPos, space, 105, BLACK);
      XPos = XPos + 21 + space;
    } else if (num[count] == '.') {
      for (int i = 0; i <= 17; i++) {screen.drawFastVLine(XPos + i, YPos, 91, BLACK); screen.drawFastVLine(XPos + i, YPos + 91, 14, colour);}
      screen.fillRect(XPos + 18, YPos, space, 105, BLACK);
      XPos = XPos + 18 + space;
    } else if (num[count] == '0') {
      screen.drawFastVLine(XPos, YPos, 17, BLACK); screen.drawFastVLine(XPos, YPos + 17, 71, colour); screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK); screen.drawFastVLine(XPos + 1, YPos + 13, 79, colour); screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK); screen.drawFastVLine(XPos + 2, YPos + 11, 83, colour); screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 9, BLACK); screen.drawFastVLine(XPos + 3, YPos + 9, 89, colour); screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK); screen.drawFastVLine(XPos + 4, YPos + 7, 91, colour); screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK); screen.drawFastVLine(XPos + 5, YPos + 6, 93, colour); screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK); screen.drawFastVLine(XPos + 6, YPos + 5, 95, colour); screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK); screen.drawFastVLine(XPos + 7, YPos + 4, 97, colour); screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK); screen.drawFastVLine(XPos + 8, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK); screen.drawFastVLine(XPos + 9, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK); screen.drawFastVLine(XPos + 10, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK); screen.drawFastVLine(XPos + 11, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawPixel(XPos + 12, YPos, BLACK); screen.drawFastVLine(XPos + 12, YPos + 1, 103, colour); screen.drawPixel(XPos + 12, YPos + 104, BLACK);
      screen.drawPixel(XPos + 13, YPos, BLACK); screen.drawFastVLine(XPos + 13, YPos + 1, 103, colour); screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawPixel(XPos + 14, YPos, BLACK); screen.drawFastVLine(XPos + 14, YPos + 1, 103, colour); screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawPixel(XPos + 15, YPos, BLACK); screen.drawFastVLine(XPos + 15, YPos + 1, 103, colour); screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawPixel(XPos + 16, YPos, BLACK); screen.drawFastVLine(XPos + 16, YPos + 1, 103, colour); screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 105, colour);
      screen.drawFastVLine(XPos + 18, YPos, 105, colour);
      screen.drawFastVLine(XPos + 19, YPos, 105, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour); screen.drawFastVLine(XPos + 20, YPos + 16, 73, BLACK); screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour); screen.drawFastVLine(XPos + 21, YPos + 15, 75, BLACK); screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour); screen.drawFastVLine(XPos + 22, YPos + 14, 77, BLACK); screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour); screen.drawFastVLine(XPos + 23, YPos + 14, 77, BLACK); screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour); screen.drawFastVLine(XPos + 24, YPos + 14, 77, BLACK); screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour); screen.drawFastVLine(XPos + 25, YPos + 15, 75, BLACK); screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour); screen.drawFastVLine(XPos + 26, YPos + 16, 73, BLACK); screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK); screen.drawFastVLine(XPos + 30, YPos + 1, 103, colour); screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawPixel(XPos + 31, YPos, BLACK); screen.drawFastVLine(XPos + 31, YPos + 1, 103, colour); screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawPixel(XPos + 32, YPos, BLACK); screen.drawFastVLine(XPos + 32, YPos + 1, 103, colour); screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawPixel(XPos + 33, YPos, BLACK); screen.drawFastVLine(XPos + 33, YPos + 1, 103, colour); screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawPixel(XPos + 34, YPos, BLACK); screen.drawFastVLine(XPos + 34, YPos + 1, 103, colour); screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK); screen.drawFastVLine(XPos + 36, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK); screen.drawFastVLine(XPos + 37, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK); screen.drawFastVLine(XPos + 38, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK); screen.drawFastVLine(XPos + 39, YPos + 4, 97, colour); screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK); screen.drawFastVLine(XPos + 40, YPos + 5, 95, colour); screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK); screen.drawFastVLine(XPos + 41, YPos + 6, 93, colour); screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 7, BLACK); screen.drawFastVLine(XPos + 42, YPos + 7, 91, colour); screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK); screen.drawFastVLine(XPos + 43, YPos + 9, 89, colour); screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK); screen.drawFastVLine(XPos + 44, YPos + 11, 83, colour); screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK); screen.drawFastVLine(XPos + 45, YPos + 13, 79, colour); screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 17, BLACK); screen.drawFastVLine(XPos + 46, YPos + 17, 71, colour); screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

      screen.fillRect(XPos + 46, YPos, space, 105, BLACK);
      XPos = XPos + 46 + space;
    } else if (num[count] == '1') {
      screen.drawFastVLine(XPos, YPos, 11, BLACK);
      screen.drawFastVLine(XPos, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos + 1, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos + 2, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos + 3, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos + 4, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 11, 12, colour);
      screen.drawFastVLine(XPos + 5, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 10, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 10, 13, colour);
      screen.drawFastVLine(XPos + 6, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 10, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 10, 13, colour);
      screen.drawFastVLine(XPos + 7, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 9, 14, colour);
      screen.drawFastVLine(XPos + 8, YPos + 9, 10, colour);
      screen.drawFastVLine(XPos + 8, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 9, 14, colour);
      screen.drawFastVLine(XPos + 9, YPos + 9, 10, colour);
      screen.drawFastVLine(XPos + 9, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 8, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 8, 15, colour);
      screen.drawFastVLine(XPos + 10, YPos + 23, 82, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 7, 98, colour);
      screen.drawFastVLine(XPos + 12, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 6, 99, colour);
      screen.drawFastVLine(XPos + 13, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 5, 100, colour);
      screen.drawFastVLine(XPos + 14, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 3, 102, colour);
      screen.drawPixel(XPos + 15, YPos, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 1, 104, colour);
      screen.drawFastVLine(XPos + 16, YPos, 105, colour);
      screen.drawFastVLine(XPos + 17, YPos, 105, colour);
      screen.drawFastVLine(XPos + 18, YPos, 105, colour);
      screen.drawFastVLine(XPos + 19, YPos, 105, colour);
      screen.drawFastVLine(XPos + 20, YPos, 105, colour);
      screen.drawFastVLine(XPos + 21, YPos, 105, colour);
      screen.drawFastVLine(XPos + 22, YPos, 105, colour);
      screen.drawFastVLine(XPos + 23, YPos, 105, colour);
      screen.drawFastVLine(XPos + 24, YPos, 105, colour);
      screen.drawFastVLine(XPos + 25, YPos, 105, colour);
      screen.drawFastVLine(XPos + 26, YPos, 105, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawFastVLine(XPos + 30, YPos, 105, colour);
      screen.drawFastVLine(XPos + 31, YPos, 105, colour);

      screen.fillRect(XPos + 31, YPos, space, 105, BLACK);
      XPos = XPos + 31 + space;
    } else if (num[count] == '2') {
      screen.drawFastVLine(XPos, YPos, 17, BLACK);
      screen.drawFastVLine(XPos, YPos + 17, 15, colour);
      screen.drawFastVLine(XPos, YPos + 32, 50, BLACK);
      screen.drawFastVLine(XPos, YPos + 82, 23, colour);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 13, 19, colour);
      screen.drawFastVLine(XPos + 1, YPos + 32, 50, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 78, 27, colour);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 11, 21, colour);
      screen.drawFastVLine(XPos + 2, YPos + 32, 46, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 76, 29, colour);
      screen.drawFastVLine(XPos + 3, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 9, 23, colour);
      screen.drawFastVLine(XPos + 3, YPos + 32, 44, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 7, 25, colour);
      screen.drawFastVLine(XPos + 4, YPos + 32, 41, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 72, 33, colour);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 6, 26, colour);
      screen.drawFastVLine(XPos + 5, YPos + 32, 40, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 69, 36, colour);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 5, 27, colour);
      screen.drawFastVLine(XPos + 6, YPos + 32, 37, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 67, 38, colour);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 4, 28, colour);
      screen.drawFastVLine(XPos + 7, YPos + 32, 35, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 65, 40, colour);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 3, 29, colour);
      screen.drawFastVLine(XPos + 8, YPos + 32, 33, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 64, 41, colour);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 3, 29, colour);
      screen.drawFastVLine(XPos + 9, YPos + 32, 32, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 62, 43, colour);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 2, 30, colour);
      screen.drawFastVLine(XPos + 10, YPos + 32, 30, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 60, 45, colour);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 2, 30, colour);
      screen.drawFastVLine(XPos + 11, YPos + 32, 28, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 59, 46, colour);
      screen.drawPixel(XPos + 12, YPos, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 1, 31, colour);
      screen.drawFastVLine(XPos + 12, YPos + 32, 27, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 57, 48, colour);
      screen.drawPixel(XPos + 13, YPos, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 1, 31, colour);
      screen.drawFastVLine(XPos + 13, YPos + 32, 25, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 56, 49, colour);
      screen.drawPixel(XPos + 14, YPos, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 1, 31, colour);
      screen.drawFastVLine(XPos + 14, YPos + 32, 24, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 54, 51, colour);
      screen.drawPixel(XPos + 15, YPos, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 1, 31, colour);
      screen.drawFastVLine(XPos + 15, YPos + 32, 22, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 53, 52, colour);
      screen.drawPixel(XPos + 16, YPos, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 1, 31, colour);
      screen.drawFastVLine(XPos + 16, YPos + 32, 21, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 51, 54, colour);
      screen.drawFastVLine(XPos + 17, YPos, 32, colour);
      screen.drawFastVLine(XPos + 17, YPos + 32, 19, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 50, 55, colour);
      screen.drawFastVLine(XPos + 18, YPos, 32, colour);
      screen.drawFastVLine(XPos + 18, YPos + 32, 18, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 48, 57, colour);
      screen.drawFastVLine(XPos + 19, YPos, 32, colour);
      screen.drawFastVLine(XPos + 19, YPos + 32, 14, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 46, 59, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour);
      screen.drawFastVLine(XPos + 20, YPos + 16, 29, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 45, 39, colour);
      screen.drawFastVLine(XPos + 20, YPos + 84, 7, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour);
      screen.drawFastVLine(XPos + 21, YPos + 15, 28, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 43, 38, colour);
      screen.drawFastVLine(XPos + 21, YPos + 81, 10, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 14, 27, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 41, 38, colour);
      screen.drawFastVLine(XPos + 22, YPos + 79, 12, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 14, 25, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 39, 38, colour);
      screen.drawFastVLine(XPos + 23, YPos + 77, 14, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 14, 23, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 37, 38, colour);
      screen.drawFastVLine(XPos + 24, YPos + 75, 16, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour);
      screen.drawFastVLine(XPos + 25, YPos + 15, 20, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 35, 38, colour);
      screen.drawFastVLine(XPos + 25, YPos + 73, 18, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour);
      screen.drawFastVLine(XPos + 26, YPos + 16, 17, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 33, 39, colour);
      screen.drawFastVLine(XPos + 26, YPos + 72, 19, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 27, YPos, 70, colour);
      screen.drawFastVLine(XPos + 27, YPos + 70, 14, BLACK);
      screen.drawFastVLine(XPos + 27, YPos + 46, 59, colour);
      screen.drawFastVLine(XPos + 27, YPos + 70, 21, BLACK);
      screen.drawFastVLine(XPos + 27, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 28, YPos, 68, colour);
      screen.drawFastVLine(XPos + 28, YPos + 68, 14, BLACK);
      screen.drawFastVLine(XPos + 28, YPos + 46, 59, colour);
      screen.drawFastVLine(XPos + 28, YPos + 68, 23, BLACK);
      screen.drawFastVLine(XPos + 28, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 29, YPos, 67, colour);
      screen.drawFastVLine(XPos + 29, YPos + 67, 14, BLACK);
      screen.drawFastVLine(XPos + 29, YPos + 46, 59, colour);
      screen.drawFastVLine(XPos + 29, YPos + 67, 24, BLACK);
      screen.drawFastVLine(XPos + 29, YPos + 91, 14, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 1, 64, colour);
      screen.drawFastVLine(XPos + 30, YPos + 65, 26, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 91, 14, colour);
      screen.drawPixel(XPos + 31, YPos, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 1, 63, colour);
      screen.drawFastVLine(XPos + 31, YPos + 64, 27, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 91, 14, colour);
      screen.drawPixel(XPos + 32, YPos, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 1, 61, colour);
      screen.drawFastVLine(XPos + 32, YPos + 62, 29, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 91, 14, colour);
      screen.drawPixel(XPos + 33, YPos, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 1, 60, colour);
      screen.drawFastVLine(XPos + 33, YPos + 61, 30, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 91, 14, colour);
      screen.drawPixel(XPos + 34, YPos, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 1, 58, colour);
      screen.drawFastVLine(XPos + 34, YPos + 59, 32, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 2, 55, colour);
      screen.drawFastVLine(XPos + 35, YPos + 57, 34, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 2, 54, colour);
      screen.drawFastVLine(XPos + 36, YPos + 56, 35, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 3, 51, colour);
      screen.drawFastVLine(XPos + 37, YPos + 54, 37, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 3, 49, colour);
      screen.drawFastVLine(XPos + 38, YPos + 52, 39, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 4, 46, colour);
      screen.drawFastVLine(XPos + 39, YPos + 50, 41, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 5, 43, colour);
      screen.drawFastVLine(XPos + 40, YPos + 48, 43, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 6, 40, colour);
      screen.drawFastVLine(XPos + 41, YPos + 46, 45, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 42, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 7, 37, colour);
      screen.drawFastVLine(XPos + 42, YPos + 44, 47, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 9, 33, colour);
      screen.drawFastVLine(XPos + 43, YPos + 42, 49, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 11, 28, colour);
      screen.drawFastVLine(XPos + 44, YPos + 39, 52, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 13, 23, colour);
      screen.drawFastVLine(XPos + 45, YPos + 36, 55, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 46, YPos, 17, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 17, 16, colour);
      screen.drawFastVLine(XPos + 46, YPos + 33, 58, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 91, 14, colour);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    } else if (num[count] == '3') {
      screen.drawFastVLine(XPos, YPos, 18, BLACK);
      screen.drawFastVLine(XPos, YPos + 18, 15, colour);
      screen.drawFastVLine(XPos, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos, YPos + 72, 15, colour);
      screen.drawFastVLine(XPos, YPos + 87, 18, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 13, 20, colour);
      screen.drawFastVLine(XPos + 1, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 72, 20, colour);
      screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 11, 22, colour);
      screen.drawFastVLine(XPos + 2, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 72, 22, colour);
      screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 9, 24, colour);
      screen.drawFastVLine(XPos + 3, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 72, 24, colour);
      screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 7, 26, colour);
      screen.drawFastVLine(XPos + 4, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 72, 26, colour);
      screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 6, 27, colour);
      screen.drawFastVLine(XPos + 5, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 72, 27, colour);
      screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 5, 28, colour);
      screen.drawFastVLine(XPos + 6, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 72, 28, colour);
      screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 4, 29, colour);
      screen.drawFastVLine(XPos + 7, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 72, 29, colour);
      screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 3, 30, colour);
      screen.drawFastVLine(XPos + 8, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 72, 30, colour);
      screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 3, 30, colour);
      screen.drawFastVLine(XPos + 9, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 72, 30, colour);
      screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 2, 31, colour);
      screen.drawFastVLine(XPos + 10, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 72, 31, colour);
      screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 2, 31, colour);
      screen.drawFastVLine(XPos + 11, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 72, 31, colour);
      screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawPixel(XPos + 12, YPos, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 1, 32, colour);
      screen.drawFastVLine(XPos + 12, YPos + 33, 39, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 72, 32, colour);
      screen.drawFastVLine(XPos + 12, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 72, 32, colour);
      screen.drawPixel(XPos + 12, YPos + 104, BLACK);
      screen.drawPixel(XPos + 13, YPos, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 1, 32, colour);
      screen.drawFastVLine(XPos + 13, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 13, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 72, 32, colour);
      screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawPixel(XPos + 14, YPos, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 1, 32, colour);
      screen.drawFastVLine(XPos + 14, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 14, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 72, 32, colour);
      screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawPixel(XPos + 15, YPos, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 1, 32, colour);
      screen.drawFastVLine(XPos + 15, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 15, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 72, 32, colour);
      screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawPixel(XPos + 16, YPos, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 1, 32, colour);
      screen.drawFastVLine(XPos + 16, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 16, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 72, 32, colour);
      screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 33, colour);
      screen.drawFastVLine(XPos + 17, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 17, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 72, 33, colour);
      screen.drawFastVLine(XPos + 18, YPos, 33, colour);
      screen.drawFastVLine(XPos + 18, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 18, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 72, 33, colour);
      screen.drawFastVLine(XPos + 19, YPos, 33, colour);
      screen.drawFastVLine(XPos + 19, YPos + 33, 11, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 19, YPos + 58, 14, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 72, 33, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour);
      screen.drawFastVLine(XPos + 20, YPos + 16, 28, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 20, YPos + 58, 31, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour);
      screen.drawFastVLine(XPos + 21, YPos + 15, 29, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 21, YPos + 58, 32, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 14, 30, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 58, 33, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 14, 30, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 58, 33, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 14, 30, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 44, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 58, 33, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour);
      screen.drawFastVLine(XPos + 25, YPos + 15, 28, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 43, 16, colour);
      screen.drawFastVLine(XPos + 25, YPos + 59, 31, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour);
      screen.drawFastVLine(XPos + 26, YPos + 16, 26, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 42, 18, colour);
      screen.drawFastVLine(XPos + 26, YPos + 60, 29, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawPixel(XPos + 31, YPos, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawPixel(XPos + 32, YPos, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawPixel(XPos + 33, YPos, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 1, 49, colour);
      screen.drawPixel(XPos + 33, YPos + 50, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 51, 53, colour);
      screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawPixel(XPos + 34, YPos, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 1, 49, colour);
      screen.drawPixel(XPos + 34, YPos + 50, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 51, 53, colour);
      screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 2, 47, colour);
      screen.drawFastVLine(XPos + 35, YPos + 49, 3, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 52, 51, colour);
      screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 2, 47, colour);
      screen.drawFastVLine(XPos + 36, YPos + 49, 3, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 52, 51, colour);
      screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 3, 45, colour);
      screen.drawFastVLine(XPos + 37, YPos + 48, 5, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 53, 49, colour);
      screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 3, 45, colour);
      screen.drawFastVLine(XPos + 38, YPos + 48, 5, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 53, 49, colour);
      screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 4, 43, colour);
      screen.drawFastVLine(XPos + 39, YPos + 47, 7, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 54, 47, colour);
      screen.drawFastVLine(XPos + 39, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 5, 41, colour);
      screen.drawFastVLine(XPos + 40, YPos + 46, 9, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 55, 45, colour);
      screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 6, 39, colour);
      screen.drawFastVLine(XPos + 41, YPos + 45, 11, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 56, 43, colour);
      screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 7, 37, colour);
      screen.drawFastVLine(XPos + 42, YPos + 44, 13, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 57, 41, colour);
      screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 9, 33, colour);
      screen.drawFastVLine(XPos + 43, YPos + 42, 17, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 59, 37, colour);
      screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 11, 29, colour);
      screen.drawFastVLine(XPos + 44, YPos + 40, 21, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 61, 33, colour);
      screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 13, 25, colour);
      screen.drawFastVLine(XPos + 45, YPos + 38, 25, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 63, 29, colour);
      screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 18, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 18, 16, colour);
      screen.drawFastVLine(XPos + 46, YPos + 34, 33, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 67, 20, colour);
      screen.drawFastVLine(XPos + 46, YPos + 87, 18, BLACK);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    } else if (num[count] == '4') {
      screen.drawFastVLine(XPos, YPos, 57, BLACK);
      screen.drawFastVLine(XPos, YPos + 57, 19, colour);
      screen.drawFastVLine(XPos, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 53, 23, colour);
      screen.drawFastVLine(XPos + 1, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 50, 26, colour);
      screen.drawFastVLine(XPos + 2, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 47, 29, colour);
      screen.drawFastVLine(XPos + 3, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 44, 32, colour);
      screen.drawFastVLine(XPos + 4, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 41, 35, colour);
      screen.drawFastVLine(XPos + 5, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 37, 39, colour);
      screen.drawFastVLine(XPos + 6, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 34, 42, colour);
      screen.drawFastVLine(XPos + 7, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 31, 45, colour);
      screen.drawFastVLine(XPos + 8, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 28, 48, colour);
      screen.drawFastVLine(XPos + 9, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 25, 51, colour);
      screen.drawFastVLine(XPos + 10, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 21, 55, colour);
      screen.drawFastVLine(XPos + 11, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 12, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 18, 58, colour);
      screen.drawFastVLine(XPos + 12, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 13, YPos, 57, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 15, 61, colour);
      screen.drawFastVLine(XPos + 13, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 14, YPos, 12, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 12, 64, colour);
      screen.drawFastVLine(XPos + 14, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 15, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 9, 41, colour);
      screen.drawFastVLine(XPos + 15, YPos + 50, 12, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 15, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 16, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 5, 41, colour);
      screen.drawFastVLine(XPos + 16, YPos + 46, 16, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 16, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 2, 41, colour);
      screen.drawFastVLine(XPos + 17, YPos + 43, 19, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 17, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 18, YPos, 39, colour);
      screen.drawFastVLine(XPos + 18, YPos + 40, 22, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 18, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 19, YPos, 37, colour);
      screen.drawFastVLine(XPos + 19, YPos + 37, 25, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 19, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 20, YPos, 34, colour);
      screen.drawFastVLine(XPos + 20, YPos + 34, 28, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 20, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 21, YPos, 31, colour);
      screen.drawFastVLine(XPos + 21, YPos + 31, 31, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 21, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 22, YPos, 28, colour);
      screen.drawFastVLine(XPos + 22, YPos + 28, 34, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 23, YPos, 24, colour);
      screen.drawFastVLine(XPos + 23, YPos + 24, 38, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 24, YPos, 21, colour);
      screen.drawFastVLine(XPos + 24, YPos + 21, 41, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 25, YPos, 18, colour);
      screen.drawFastVLine(XPos + 25, YPos + 18, 44, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 26, YPos, 105, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawFastVLine(XPos + 30, YPos, 105, colour);
      screen.drawFastVLine(XPos + 31, YPos, 105, colour);
      screen.drawFastVLine(XPos + 32, YPos, 105, colour);
      screen.drawFastVLine(XPos + 33, YPos, 105, colour);
      screen.drawFastVLine(XPos + 34, YPos, 105, colour);
      screen.drawFastVLine(XPos + 35, YPos, 105, colour);
      screen.drawFastVLine(XPos + 36, YPos, 105, colour);
      screen.drawFastVLine(XPos + 37, YPos, 105, colour);
      screen.drawFastVLine(XPos + 38, YPos, 105, colour);
      screen.drawFastVLine(XPos + 39, YPos, 105, colour);
      screen.drawFastVLine(XPos + 40, YPos, 105, colour);
      screen.drawFastVLine(XPos + 41, YPos, 105, colour);
      screen.drawFastVLine(XPos + 42, YPos, 105, colour);
      screen.drawFastVLine(XPos + 43, YPos, 105, colour);
      screen.drawFastVLine(XPos + 44, YPos, 105, colour);
      screen.drawFastVLine(XPos + 45, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 45, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 46, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 47, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 47, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 47, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 48, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 48, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 48, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 49, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 49, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 49, YPos + 76, 29, BLACK);
      screen.drawFastVLine(XPos + 50, YPos, 62, BLACK);
      screen.drawFastVLine(XPos + 50, YPos + 62, 14, colour);
      screen.drawFastVLine(XPos + 50, YPos + 76, 29, BLACK);

      screen.fillRect(XPos + 51, YPos, space, 105, BLACK);
      XPos = XPos + 51 + space;
    } else if (num[count] == '5') {
      screen.drawFastVLine(XPos, YPos, 54, colour);
      screen.drawFastVLine(XPos, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos, YPos + 73, 15, colour);
      screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 54, colour);
      screen.drawFastVLine(XPos + 1, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 73, 19, colour);
      screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 54, colour);
      screen.drawFastVLine(XPos + 2, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 73, 21, colour);
      screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 54, colour);
      screen.drawFastVLine(XPos + 3, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 73, 23, colour);
      screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 54, colour);
      screen.drawFastVLine(XPos + 4, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 73, 25, colour);
      screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 54, colour);
      screen.drawFastVLine(XPos + 5, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 73, 26, colour);
      screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 54, colour);
      screen.drawFastVLine(XPos + 6, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 73, 27, colour);
      screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 54, colour);
      screen.drawFastVLine(XPos + 7, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 73, 28, colour);
      screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 54, colour);
      screen.drawFastVLine(XPos + 8, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 73, 29, colour);
      screen.drawFastVLine(XPos + 8, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 54, colour);
      screen.drawFastVLine(XPos + 9, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 73, 29, colour);
      screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 54, colour);
      screen.drawFastVLine(XPos + 10, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 73, 30, colour);
      screen.drawFastVLine(XPos + 10, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 54, colour);
      screen.drawFastVLine(XPos + 11, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 73, 30, colour);
      screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 12, YPos, 54, colour);
      screen.drawFastVLine(XPos + 12, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 73, 31, colour);
      screen.drawFastVLine(XPos + 12, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 13, YPos, 54, colour);
      screen.drawFastVLine(XPos + 13, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 73, 31, colour);
      screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 14, YPos, 54, colour);
      screen.drawFastVLine(XPos + 14, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 73, 31, colour);
      screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 15, YPos, 54, colour);
      screen.drawFastVLine(XPos + 15, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 73, 31, colour);
      screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 16, YPos, 54, colour);
      screen.drawFastVLine(XPos + 16, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 73, 31, colour);
      screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 54, colour);
      screen.drawFastVLine(XPos + 17, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 18, YPos, 54, colour);
      screen.drawFastVLine(XPos + 18, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 19, YPos, 54, colour);
      screen.drawFastVLine(XPos + 19, YPos + 54, 19, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 20, YPos, 14, colour);
      screen.drawFastVLine(XPos + 20, YPos + 14, 20, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 34, 18, colour);
      screen.drawFastVLine(XPos + 20, YPos + 52, 37, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 14, colour);
      screen.drawFastVLine(XPos + 21, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 33, 18, colour);
      screen.drawFastVLine(XPos + 21, YPos + 51, 39, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 33, 17, colour);
      screen.drawFastVLine(XPos + 22, YPos + 50, 41, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 33, 17, colour);
      screen.drawFastVLine(XPos + 23, YPos + 50, 41, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 33, 17, colour);
      screen.drawFastVLine(XPos + 24, YPos + 50, 41, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 32, 19, colour);
      screen.drawFastVLine(XPos + 25, YPos + 51, 39, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 14, colour);
      screen.drawFastVLine(XPos + 26, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 32, 20, colour);
      screen.drawFastVLine(XPos + 26, YPos + 52, 37, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 14, colour);
      screen.drawFastVLine(XPos + 27, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 27, YPos + 32, 73, colour);
      screen.drawFastVLine(XPos + 28, YPos, 14, colour);
      screen.drawFastVLine(XPos + 28, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 28, YPos + 32, 73, colour);
      screen.drawFastVLine(XPos + 29, YPos, 14, colour);
      screen.drawFastVLine(XPos + 29, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 29, YPos + 32, 73, colour);
      screen.drawFastVLine(XPos + 30, YPos, 14, colour);
      screen.drawFastVLine(XPos + 30, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 32, 72, colour);
      screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 31, YPos, 14, colour);
      screen.drawFastVLine(XPos + 31, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 32, 72, colour);
      screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 32, YPos, 14, colour);
      screen.drawFastVLine(XPos + 32, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 32, 72, colour);
      screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 33, YPos, 14, colour);
      screen.drawFastVLine(XPos + 33, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 32, 72, colour);
      screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 34, YPos, 14, colour);
      screen.drawFastVLine(XPos + 34, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 32, 72, colour);
      screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 14, colour);
      screen.drawFastVLine(XPos + 35, YPos + 14, 18, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 32, 71, colour);
      screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 14, colour);
      screen.drawFastVLine(XPos + 36, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 33, 70, colour);
      screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 14, colour);
      screen.drawFastVLine(XPos + 37, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 33, 69, colour);
      screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 14, colour);
      screen.drawFastVLine(XPos + 38, YPos + 14, 19, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 33, 69, colour);
      screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 14, colour);
      screen.drawFastVLine(XPos + 39, YPos + 14, 20, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 34, 67, colour);
      screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 14, colour);
      screen.drawFastVLine(XPos + 40, YPos + 14, 20, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 34, 66, colour);
      screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 14, colour);
      screen.drawFastVLine(XPos + 41, YPos + 14, 21, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 35, 64, colour);
      screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 14, colour);
      screen.drawFastVLine(XPos + 42, YPos + 14, 22, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 36, 62, colour);
      screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 14, colour);
      screen.drawFastVLine(XPos + 43, YPos + 14, 23, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 37, 59, colour);
      screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 14, colour);
      screen.drawFastVLine(XPos + 44, YPos + 14, 24, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 38, 56, colour);
      screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 14, colour);
      screen.drawFastVLine(XPos + 45, YPos + 14, 26, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 40, 52, colour);
      screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 14, colour);
      screen.drawFastVLine(XPos + 46, YPos + 14, 29, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 43, 45, colour);
      screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    } else if (num[count] == '6') {
      screen.drawFastVLine(XPos, YPos, 17, BLACK);
      screen.drawFastVLine(XPos, YPos + 17, 71, colour);
      screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 1, YPos + 13, 79, colour);
      screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 2, YPos + 11, 83, colour);
      screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 8, BLACK);
      screen.drawFastVLine(XPos + 3, YPos + 8, 87, colour);
      screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 7, 91, colour);
      screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 6, 93, colour);
      screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 5, 95, colour);
      screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 4, 97, colour);
      screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 3, 99, colour);
      screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 3, 99, colour);
      screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 2, 101, colour);
      screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 2, 101, colour);
      screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawPixel(XPos + 12, YPos, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 12, YPos + 104, BLACK);
      screen.drawPixel(XPos + 13, YPos, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawPixel(XPos + 14, YPos, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawPixel(XPos + 15, YPos, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawPixel(XPos + 16, YPos, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 1, 103, colour);
      screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 105, colour);
      screen.drawFastVLine(XPos + 18, YPos, 105, colour);
      screen.drawFastVLine(XPos + 19, YPos, 105, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour);
      screen.drawFastVLine(XPos + 20, YPos + 16, 30, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 46, 16, colour);
      screen.drawFastVLine(XPos + 20, YPos + 62, 27, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour);
      screen.drawFastVLine(XPos + 21, YPos + 15, 31, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 46, 15, colour);
      screen.drawFastVLine(XPos + 21, YPos + 61, 29, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 14, 31, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 45, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos + 60, 31, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 14, 30, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 44, 16, colour);
      screen.drawFastVLine(XPos + 23, YPos + 60, 31, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 14, 30, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 44, 16, colour);
      screen.drawFastVLine(XPos + 24, YPos + 60, 31, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour);
      screen.drawFastVLine(XPos + 25, YPos + 15, 28, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 43, 18, colour);
      screen.drawFastVLine(XPos + 25, YPos + 61, 29, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour);
      screen.drawFastVLine(XPos + 26, YPos + 16, 27, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 43, 19, colour);
      screen.drawFastVLine(XPos + 26, YPos + 62, 27, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 37, colour);
      screen.drawFastVLine(XPos + 27, YPos + 37, 6, BLACK);
      screen.drawFastVLine(XPos + 27, YPos + 43, 62, colour);
      screen.drawFastVLine(XPos + 28, YPos, 37, colour);
      screen.drawFastVLine(XPos + 28, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 28, YPos + 42, 63, colour);
      screen.drawFastVLine(XPos + 29, YPos, 37, colour);
      screen.drawFastVLine(XPos + 29, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 29, YPos + 42, 63, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 1, 36, colour);
      screen.drawFastVLine(XPos + 30, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 30, YPos + 42, 62, colour);
      screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawPixel(XPos + 31, YPos, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 1, 36, colour);
      screen.drawFastVLine(XPos + 31, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 31, YPos + 42, 62, colour);
      screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawPixel(XPos + 32, YPos, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 1, 36, colour);
      screen.drawFastVLine(XPos + 32, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 32, YPos + 42, 62, colour);
      screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawPixel(XPos + 33, YPos, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 1, 36, colour);
      screen.drawFastVLine(XPos + 33, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 33, YPos + 42, 62, colour);
      screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawPixel(XPos + 34, YPos, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 1, 36, colour);
      screen.drawFastVLine(XPos + 34, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 34, YPos + 42, 62, colour);
      screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 2, 35, colour);
      screen.drawFastVLine(XPos + 35, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 35, YPos + 42, 61, colour);
      screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 2, 35, colour);
      screen.drawFastVLine(XPos + 36, YPos + 37, 5, BLACK);
      screen.drawFastVLine(XPos + 36, YPos + 42, 61, colour);
      screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 3, 34, colour);
      screen.drawFastVLine(XPos + 37, YPos + 37, 6, BLACK);
      screen.drawFastVLine(XPos + 37, YPos + 43, 59, colour);
      screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 3, 34, colour);
      screen.drawFastVLine(XPos + 38, YPos + 37, 6, BLACK);
      screen.drawFastVLine(XPos + 38, YPos + 43, 59, colour);
      screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 4, 33, colour);
      screen.drawFastVLine(XPos + 39, YPos + 37, 7, BLACK);
      screen.drawFastVLine(XPos + 39, YPos + 44, 57, colour);
      screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 5, 32, colour);
      screen.drawFastVLine(XPos + 40, YPos + 37, 7, BLACK);
      screen.drawFastVLine(XPos + 40, YPos + 44, 56, colour);
      screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 6, 31, colour);
      screen.drawFastVLine(XPos + 41, YPos + 37, 8, BLACK);
      screen.drawFastVLine(XPos + 41, YPos + 45, 54, colour);
      screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 7, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 7, 30, colour);
      screen.drawFastVLine(XPos + 42, YPos + 37, 9, BLACK);
      screen.drawFastVLine(XPos + 42, YPos + 46, 52, colour);
      screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 9, 28, colour);
      screen.drawFastVLine(XPos + 43, YPos + 37, 10, BLACK);
      screen.drawFastVLine(XPos + 43, YPos + 47, 49, colour);
      screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 11, 26, colour);
      screen.drawFastVLine(XPos + 44, YPos + 37, 11, BLACK);
      screen.drawFastVLine(XPos + 44, YPos + 48, 46, colour);
      screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 13, 24, colour);
      screen.drawFastVLine(XPos + 45, YPos + 37, 13, BLACK);
      screen.drawFastVLine(XPos + 45, YPos + 50, 42, colour);
      screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 17, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 17, 20, colour);
      screen.drawFastVLine(XPos + 46, YPos + 37, 16, BLACK);
      screen.drawFastVLine(XPos + 46, YPos + 53, 35, colour);
      screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    } else if (num[count] == '7') {
      screen.drawFastVLine(XPos, YPos, 14, colour);
      screen.drawFastVLine(XPos, YPos + 14, 91, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 14, colour);
      screen.drawFastVLine(XPos + 1, YPos + 14, 91, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 14, colour);
      screen.drawFastVLine(XPos + 2, YPos + 14, 91, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 14, colour);
      screen.drawFastVLine(XPos + 3, YPos + 14, 91, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 14, colour);
      screen.drawFastVLine(XPos + 4, YPos + 14, 87, BLACK);
      screen.drawFastVLine(XPos + 4, YPos + 101, 4, colour);
      screen.drawFastVLine(XPos + 5, YPos, 14, colour);
      screen.drawFastVLine(XPos + 5, YPos + 14, 83, BLACK);
      screen.drawFastVLine(XPos + 5, YPos + 97, 8, colour);
      screen.drawFastVLine(XPos + 6, YPos, 14, colour);
      screen.drawFastVLine(XPos + 6, YPos + 14, 80, BLACK);
      screen.drawFastVLine(XPos + 6, YPos + 93, 12, colour);
      screen.drawFastVLine(XPos + 7, YPos, 14, colour);
      screen.drawFastVLine(XPos + 7, YPos + 14, 77, BLACK);
      screen.drawFastVLine(XPos + 7, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 8, YPos, 14, colour);
      screen.drawFastVLine(XPos + 8, YPos + 14, 73, BLACK);
      screen.drawFastVLine(XPos + 8, YPos + 87, 18, colour);
      screen.drawFastVLine(XPos + 9, YPos, 14, colour);
      screen.drawFastVLine(XPos + 9, YPos + 14, 70, BLACK);
      screen.drawFastVLine(XPos + 9, YPos + 84, 21, colour);
      screen.drawFastVLine(XPos + 10, YPos, 14, colour);
      screen.drawFastVLine(XPos + 10, YPos + 14, 67, BLACK);
      screen.drawFastVLine(XPos + 10, YPos + 81, 24, colour);
      screen.drawFastVLine(XPos + 11, YPos, 14, colour);
      screen.drawFastVLine(XPos + 11, YPos + 14, 63, BLACK);
      screen.drawFastVLine(XPos + 11, YPos + 77, 28, colour);
      screen.drawFastVLine(XPos + 12, YPos, 14, colour);
      screen.drawFastVLine(XPos + 12, YPos + 14, 60, BLACK);
      screen.drawFastVLine(XPos + 12, YPos + 74, 31, colour);
      screen.drawFastVLine(XPos + 13, YPos, 14, colour);
      screen.drawFastVLine(XPos + 13, YPos + 14, 56, BLACK);
      screen.drawFastVLine(XPos + 13, YPos + 70, 35, colour);
      screen.drawFastVLine(XPos + 14, YPos, 14, colour);
      screen.drawFastVLine(XPos + 14, YPos + 14, 53, BLACK);
      screen.drawFastVLine(XPos + 14, YPos + 68, 37, colour);
      screen.drawFastVLine(XPos + 15, YPos, 14, colour);
      screen.drawFastVLine(XPos + 15, YPos + 14, 50, BLACK);
      screen.drawFastVLine(XPos + 15, YPos + 64, 41, colour);
      screen.drawFastVLine(XPos + 16, YPos, 14, colour);
      screen.drawFastVLine(XPos + 16, YPos + 14, 46, BLACK);
      screen.drawFastVLine(XPos + 16, YPos + 60, 45, colour);
      screen.drawFastVLine(XPos + 17, YPos, 14, colour);
      screen.drawFastVLine(XPos + 17, YPos + 14, 43, BLACK);
      screen.drawFastVLine(XPos + 17, YPos + 57, 48, colour);
      screen.drawFastVLine(XPos + 18, YPos, 14, colour);
      screen.drawFastVLine(XPos + 18, YPos + 14, 39, BLACK);
      screen.drawFastVLine(XPos + 18, YPos + 53, 52, colour);
      screen.drawFastVLine(XPos + 19, YPos, 14, colour);
      screen.drawFastVLine(XPos + 19, YPos + 14, 36, BLACK);
      screen.drawFastVLine(XPos + 19, YPos + 50, 55, colour);
      screen.drawFastVLine(XPos + 20, YPos, 14, colour);
      screen.drawFastVLine(XPos + 20, YPos + 14, 33, BLACK);
      screen.drawFastVLine(XPos + 20, YPos + 47, 58, colour);
      screen.drawFastVLine(XPos + 21, YPos, 14, colour);
      screen.drawFastVLine(XPos + 21, YPos + 14, 29, BLACK);
      screen.drawFastVLine(XPos + 21, YPos + 43, 62, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour);
      screen.drawFastVLine(XPos + 22, YPos + 14, 26, BLACK);
      screen.drawFastVLine(XPos + 22, YPos + 40, 65, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos + 14, 23, BLACK);
      screen.drawFastVLine(XPos + 23, YPos + 37, 68, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos + 14, 25, BLACK);
      screen.drawFastVLine(XPos + 24, YPos + 33, 72, colour);
      screen.drawFastVLine(XPos + 25, YPos, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos + 14, 16, BLACK);
      screen.drawFastVLine(XPos + 25, YPos + 30, 73, colour);
      screen.drawFastVLine(XPos + 25, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 26, YPos, 14, colour);
      screen.drawFastVLine(XPos + 26, YPos + 14, 12, BLACK);
      screen.drawFastVLine(XPos + 26, YPos + 26, 73, colour);
      screen.drawFastVLine(XPos + 26, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 27, YPos, 14, colour);
      screen.drawFastVLine(XPos + 27, YPos + 14, 9, BLACK);
      screen.drawFastVLine(XPos + 27, YPos + 23, 73, colour);
      screen.drawFastVLine(XPos + 27, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 28, YPos, 14, colour);
      screen.drawFastVLine(XPos + 28, YPos + 14, 6, BLACK);
      screen.drawFastVLine(XPos + 28, YPos + 20, 72, colour);
      screen.drawFastVLine(XPos + 28, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 29, YPos, 14, colour);
      screen.drawFastVLine(XPos + 29, YPos + 14, 2, BLACK);
      screen.drawFastVLine(XPos + 29, YPos + 16, 72, colour);
      screen.drawFastVLine(XPos + 29, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 30, YPos, 85, colour);
      screen.drawFastVLine(XPos + 30, YPos + 85, 20, BLACK);
      screen.drawFastVLine(XPos + 31, YPos, 81, colour);
      screen.drawFastVLine(XPos + 31, YPos + 81, 24, BLACK);
      screen.drawFastVLine(XPos + 32, YPos, 78, colour);
      screen.drawFastVLine(XPos + 32, YPos + 78, 27, BLACK);
      screen.drawFastVLine(XPos + 33, YPos, 74, colour);
      screen.drawFastVLine(XPos + 33, YPos + 74, 31, BLACK);
      screen.drawFastVLine(XPos + 34, YPos, 71, colour);
      screen.drawFastVLine(XPos + 34, YPos + 71, 34, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 67, colour);
      screen.drawFastVLine(XPos + 35, YPos + 67, 38, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 64, colour);
      screen.drawFastVLine(XPos + 36, YPos + 64, 41, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 60, colour);
      screen.drawFastVLine(XPos + 37, YPos + 60, 45, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 56, colour);
      screen.drawFastVLine(XPos + 38, YPos + 56, 49, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 53, colour);
      screen.drawFastVLine(XPos + 39, YPos + 53, 52, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 49, colour);
      screen.drawFastVLine(XPos + 40, YPos + 49, 56, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 46, colour);
      screen.drawFastVLine(XPos + 41, YPos + 46, 59, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 42, colour);
      screen.drawFastVLine(XPos + 42, YPos + 42, 63, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 39, colour);
      screen.drawFastVLine(XPos + 43, YPos + 39, 66, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 35, colour);
      screen.drawFastVLine(XPos + 44, YPos + 35, 70, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 32, colour);
      screen.drawFastVLine(XPos + 45, YPos + 32, 73, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 28, colour);
      screen.drawFastVLine(XPos + 46, YPos + 28, 77, BLACK);
      screen.drawFastVLine(XPos + 47, YPos, 24, colour);
      screen.drawFastVLine(XPos + 47, YPos + 24, 81, BLACK);
      screen.drawFastVLine(XPos + 48, YPos, 21, colour);
      screen.drawFastVLine(XPos + 48, YPos + 21, 84, BLACK);
      screen.drawFastVLine(XPos + 49, YPos, 17, colour);
      screen.drawFastVLine(XPos + 49, YPos + 17, 88, BLACK);
      screen.drawFastVLine(XPos + 50, YPos, 15, colour);
      screen.drawFastVLine(XPos + 50, YPos + 15, 90, BLACK);

      screen.fillRect(XPos + 51, YPos, space, 105, BLACK);
      XPos = XPos + 51 + space;
    } else if (num[count] == '8') {
      screen.drawFastVLine(XPos, YPos, 17, BLACK); screen.drawFastVLine(XPos, YPos + 17, 16, colour); screen.drawFastVLine(XPos, YPos + 33, 33, BLACK); screen.drawFastVLine(XPos, YPos + 66, 22, colour); screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK); screen.drawFastVLine(XPos + 1, YPos + 13, 24, colour); screen.drawFastVLine(XPos + 1, YPos + 37, 25, BLACK); screen.drawFastVLine(XPos + 1, YPos + 62, 30, colour); screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK); screen.drawFastVLine(XPos + 2, YPos + 11, 28, colour); screen.drawFastVLine(XPos + 2, YPos + 38, 21, BLACK); screen.drawFastVLine(XPos + 2, YPos + 60, 34, colour); screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 9, BLACK); screen.drawFastVLine(XPos + 3, YPos + 9, 32, colour); screen.drawFastVLine(XPos + 3, YPos + 41, 17, BLACK); screen.drawFastVLine(XPos + 3, YPos + 58, 38, colour); screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK); screen.drawFastVLine(XPos + 4, YPos + 7, 36, colour); screen.drawFastVLine(XPos + 4, YPos + 43, 13, BLACK); screen.drawFastVLine(XPos + 4, YPos + 56, 42, colour); screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK); screen.drawFastVLine(XPos + 5, YPos + 6, 38, colour); screen.drawFastVLine(XPos + 5, YPos + 44, 11, BLACK); screen.drawFastVLine(XPos + 5, YPos + 55, 44, colour); screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK); screen.drawFastVLine(XPos + 6, YPos + 5, 40, colour); screen.drawFastVLine(XPos + 6, YPos + 45, 9, BLACK); screen.drawFastVLine(XPos + 6, YPos + 54, 46, colour); screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK); screen.drawFastVLine(XPos + 7, YPos + 4, 42, colour); screen.drawFastVLine(XPos + 7, YPos + 46, 7, BLACK); screen.drawFastVLine(XPos + 7, YPos + 53, 48, colour); screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK); screen.drawFastVLine(XPos + 8, YPos + 3, 44, colour); screen.drawFastVLine(XPos + 8, YPos + 47, 5, BLACK); screen.drawFastVLine(XPos + 8, YPos + 52, 50, colour); screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK); screen.drawFastVLine(XPos + 9, YPos + 3, 44, colour); screen.drawFastVLine(XPos + 9, YPos + 47, 5, BLACK); screen.drawFastVLine(XPos + 9, YPos + 52, 50, colour); screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK); screen.drawFastVLine(XPos + 10, YPos + 2, 46, colour); screen.drawFastVLine(XPos + 10, YPos + 48, 3, BLACK);  screen.drawFastVLine(XPos + 10, YPos + 51, 52, colour); screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK); screen.drawFastVLine(XPos + 11, YPos + 2, 46, colour); screen.drawFastVLine(XPos + 11, YPos + 48, 3, BLACK); screen.drawFastVLine(XPos + 11, YPos + 51, 52, colour); screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawPixel(XPos + 12, YPos, BLACK); screen.drawFastVLine(XPos + 12, YPos + 1, 48, colour); screen.drawPixel(XPos + 12, YPos + 49, BLACK); screen.drawFastVLine(XPos + 12, YPos + 50, 54, colour); screen.drawPixel(XPos + 12, YPos + 104, BLACK);
      screen.drawPixel(XPos + 13, YPos, BLACK); screen.drawFastVLine(XPos + 13, YPos + 1, 103, colour); screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawPixel(XPos + 14, YPos, BLACK); screen.drawFastVLine(XPos + 14, YPos + 1, 103, colour); screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawPixel(XPos + 15, YPos, BLACK); screen.drawFastVLine(XPos + 15, YPos + 1, 103, colour); screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawPixel(XPos + 16, YPos, BLACK); screen.drawFastVLine(XPos + 16, YPos + 1, 103, colour); screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 105, colour);
      screen.drawFastVLine(XPos + 18, YPos, 105, colour);
      screen.drawFastVLine(XPos + 19, YPos, 105, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour); screen.drawFastVLine(XPos + 20, YPos + 16, 18, BLACK); screen.drawFastVLine(XPos + 20, YPos + 34, 38, colour); screen.drawFastVLine(XPos + 20, YPos + 65, 24, BLACK); screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour); screen.drawFastVLine(XPos + 21, YPos + 15, 20, BLACK); screen.drawFastVLine(XPos + 21, YPos + 35, 36, colour); screen.drawFastVLine(XPos + 21, YPos + 64, 26, BLACK); screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour); screen.drawFastVLine(XPos + 22, YPos + 14, 22, BLACK); screen.drawFastVLine(XPos + 22, YPos + 36, 34, colour); screen.drawFastVLine(XPos + 22, YPos + 63, 28, BLACK); screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour); screen.drawFastVLine(XPos + 23, YPos + 14, 22, BLACK); screen.drawFastVLine(XPos + 23, YPos + 36, 34, colour); screen.drawFastVLine(XPos + 23, YPos + 63, 28, BLACK); screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour); screen.drawFastVLine(XPos + 24, YPos + 14, 22, BLACK); screen.drawFastVLine(XPos + 24, YPos + 36, 34, colour); screen.drawFastVLine(XPos + 24, YPos + 63, 28, BLACK); screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour); screen.drawFastVLine(XPos + 25, YPos + 15, 20, BLACK); screen.drawFastVLine(XPos + 25, YPos + 35, 36, colour); screen.drawFastVLine(XPos + 25, YPos + 64, 26, BLACK); screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour); screen.drawFastVLine(XPos + 26, YPos + 16, 18, BLACK); screen.drawFastVLine(XPos + 26, YPos + 34, 38, colour); screen.drawFastVLine(XPos + 26, YPos + 65, 24, BLACK); screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK); screen.drawFastVLine(XPos + 30, YPos + 1, 103, colour); screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawPixel(XPos + 31, YPos, BLACK); screen.drawFastVLine(XPos + 31, YPos + 1, 103, colour); screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawPixel(XPos + 32, YPos, BLACK); screen.drawFastVLine(XPos + 32, YPos + 1, 103, colour); screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawPixel(XPos + 33, YPos, BLACK); screen.drawFastVLine(XPos + 33, YPos + 1, 103, colour);  screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawPixel(XPos + 34, YPos, BLACK); screen.drawFastVLine(XPos + 34, YPos + 1, 48, colour); screen.drawPixel(XPos + 34, YPos + 49, BLACK); screen.drawFastVLine(XPos + 34, YPos + 50, 54, colour); screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 48, colour); screen.drawFastVLine(XPos + 35, YPos + 49, 3, BLACK); screen.drawFastVLine(XPos + 35, YPos + 51, 52, colour); screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK); screen.drawFastVLine(XPos + 36, YPos + 2, 46, colour); screen.drawFastVLine(XPos + 36, YPos + 48, 3, BLACK); screen.drawFastVLine(XPos + 36, YPos + 51, 52, colour); screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK); screen.drawFastVLine(XPos + 37, YPos + 3, 44, colour); screen.drawFastVLine(XPos + 37, YPos + 47, 5, BLACK); screen.drawFastVLine(XPos + 37, YPos + 52, 50, colour); screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK); screen.drawFastVLine(XPos + 38, YPos + 3, 44, colour); screen.drawFastVLine(XPos + 38, YPos + 47, 5, BLACK); screen.drawFastVLine(XPos + 38, YPos + 52, 50, colour); screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK); screen.drawFastVLine(XPos + 39, YPos + 4, 42, colour); screen.drawFastVLine(XPos + 39, YPos + 46, 7, BLACK); screen.drawFastVLine(XPos + 39, YPos + 53, 48, colour); screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK); screen.drawFastVLine(XPos + 40, YPos + 5, 40, colour); screen.drawFastVLine(XPos + 40, YPos + 45, 9, BLACK); screen.drawFastVLine(XPos + 40, YPos + 54, 46, colour); screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK); screen.drawFastVLine(XPos + 41, YPos + 6, 38, colour); screen.drawFastVLine(XPos + 41, YPos + 44, 11, BLACK); screen.drawFastVLine(XPos + 41, YPos + 55, 44, colour); screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 8, BLACK); screen.drawFastVLine(XPos + 42, YPos + 8, 35, colour); screen.drawFastVLine(XPos + 42, YPos + 43, 13, BLACK); screen.drawFastVLine(XPos + 42, YPos + 56, 42, colour); screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK); screen.drawFastVLine(XPos + 43, YPos + 9, 32, colour); screen.drawFastVLine(XPos + 43, YPos + 41, 17, BLACK); screen.drawFastVLine(XPos + 43, YPos + 58, 38, colour); screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK); screen.drawFastVLine(XPos + 44, YPos + 11, 28, colour); screen.drawFastVLine(XPos + 44, YPos + 39, 21, BLACK); screen.drawFastVLine(XPos + 44, YPos + 60, 34, colour); screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK); screen.drawFastVLine(XPos + 45, YPos + 13, 24, colour); screen.drawFastVLine(XPos + 45, YPos + 37, 25, BLACK); screen.drawFastVLine(XPos + 45, YPos + 62, 30, colour); screen.drawFastVLine(XPos + 45, YPos + 93, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 17, BLACK); screen.drawFastVLine(XPos + 46, YPos + 17, 16, colour); screen.drawFastVLine(XPos + 46, YPos + 33, 33, BLACK); screen.drawFastVLine(XPos + 46, YPos + 66, 22, colour); screen.drawFastVLine(XPos + 46, YPos + 88, 12, BLACK);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    } else if (num[count] == '9') {
      screen.drawFastVLine(XPos, YPos, 17, BLACK); screen.drawFastVLine(XPos, YPos + 17, 40, colour); screen.drawFastVLine(XPos, YPos + 57, 16, BLACK); screen.drawFastVLine(XPos, YPos + 73, 15, colour); screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 13, BLACK); screen.drawFastVLine(XPos + 1, YPos + 13, 46, colour); screen.drawFastVLine(XPos + 1, YPos + 59, 14, BLACK); screen.drawFastVLine(XPos + 1, YPos + 73, 19, colour); screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 11, BLACK); screen.drawFastVLine(XPos + 2, YPos + 11, 50, colour); screen.drawFastVLine(XPos + 2, YPos + 61, 12, BLACK); screen.drawFastVLine(XPos + 2, YPos + 73, 21, colour); screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 9, BLACK); screen.drawFastVLine(XPos + 3, YPos + 9, 54, colour); screen.drawFastVLine(XPos + 3, YPos + 63, 10, BLACK); screen.drawFastVLine(XPos + 3, YPos + 73, 23, colour); screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 7, BLACK); screen.drawFastVLine(XPos + 4, YPos + 7, 57, colour); screen.drawFastVLine(XPos + 4, YPos + 64, 9, BLACK); screen.drawFastVLine(XPos + 4, YPos + 73, 25, colour); screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 6, BLACK); screen.drawFastVLine(XPos + 5, YPos + 6, 59, colour); screen.drawFastVLine(XPos + 5, YPos + 65, 8, BLACK); screen.drawFastVLine(XPos + 5, YPos + 73, 26, colour); screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, BLACK); screen.drawFastVLine(XPos + 6, YPos + 5, 60, colour); screen.drawFastVLine(XPos + 6, YPos + 65, 8, BLACK); screen.drawFastVLine(XPos + 6, YPos + 73, 27, colour); screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 4, BLACK); screen.drawFastVLine(XPos + 7, YPos + 4, 62, colour); screen.drawFastVLine(XPos + 7, YPos + 66, 7, BLACK); screen.drawFastVLine(XPos + 7, YPos + 73, 28, colour); screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 8, YPos, 3, BLACK); screen.drawFastVLine(XPos + 8, YPos + 3, 63, colour); screen.drawFastVLine(XPos + 8, YPos + 66, 7, BLACK); screen.drawFastVLine(XPos + 8, YPos + 73, 29, colour); screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 9, YPos, 3, BLACK); screen.drawFastVLine(XPos + 9, YPos + 3, 64, colour); screen.drawFastVLine(XPos + 9, YPos + 67, 6, BLACK); screen.drawFastVLine(XPos + 9, YPos + 73, 29, colour); screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 10, YPos, 2, BLACK); screen.drawFastVLine(XPos + 10, YPos + 2, 65, colour); screen.drawFastVLine(XPos + 10, YPos + 67, 6, BLACK); screen.drawFastVLine(XPos + 10, YPos + 73, 30, colour); screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 11, YPos, 2, BLACK); screen.drawFastVLine(XPos + 11, YPos + 2, 65, colour); screen.drawFastVLine(XPos + 11, YPos + 67, 6, BLACK); screen.drawFastVLine(XPos + 11, YPos + 73, 30, colour); screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
      screen.drawPixel(XPos + 12, YPos, BLACK); screen.drawFastVLine(XPos + 12, YPos + 1, 67, colour); screen.drawFastVLine(XPos + 12, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 12, YPos + 73, 31, colour); screen.drawPixel(XPos + 12, YPos + 104, BLACK);
      screen.drawPixel(XPos + 13, YPos, BLACK); screen.drawFastVLine(XPos + 13, YPos + 1, 67, colour); screen.drawFastVLine(XPos + 13, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 13, YPos + 73, 31, colour); screen.drawPixel(XPos + 13, YPos + 104, BLACK);
      screen.drawPixel(XPos + 14, YPos, BLACK); screen.drawFastVLine(XPos + 14, YPos + 1, 67, colour); screen.drawFastVLine(XPos + 14, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 14, YPos + 73, 31, colour); screen.drawPixel(XPos + 14, YPos + 104, BLACK);
      screen.drawPixel(XPos + 15, YPos, BLACK); screen.drawFastVLine(XPos + 15, YPos + 1, 67, colour); screen.drawFastVLine(XPos + 15, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 15, YPos + 73, 31, colour); screen.drawPixel(XPos + 15, YPos + 104, BLACK);
      screen.drawPixel(XPos + 16, YPos, BLACK); screen.drawFastVLine(XPos + 16, YPos + 1, 67, colour); screen.drawFastVLine(XPos + 16, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 16, YPos + 73, 31, colour); screen.drawPixel(XPos + 16, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 17, YPos, 68, colour); screen.drawFastVLine(XPos + 17, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 17, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 18, YPos, 68, colour); screen.drawFastVLine(XPos + 18, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 18, YPos + 73, 32, colour); screen.drawFastVLine(XPos + 19, YPos, 68, colour); screen.drawFastVLine(XPos + 19, YPos + 68, 5, BLACK); screen.drawFastVLine(XPos + 19, YPos + 73, 32, colour);
      screen.drawFastVLine(XPos + 20, YPos, 16, colour); screen.drawFastVLine(XPos + 20, YPos + 16, 33, BLACK); screen.drawFastVLine(XPos + 20, YPos + 49, 18, colour); screen.drawFastVLine(XPos + 20, YPos + 67, 22, BLACK); screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 21, YPos, 15, colour); screen.drawFastVLine(XPos + 21, YPos + 15, 35, BLACK); screen.drawFastVLine(XPos + 21, YPos + 50, 17, colour); screen.drawFastVLine(XPos + 21, YPos + 67, 23, BLACK); screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 22, YPos, 14, colour); screen.drawFastVLine(XPos + 22, YPos + 14, 37, BLACK); screen.drawFastVLine(XPos + 22, YPos + 51, 16, colour); screen.drawFastVLine(XPos + 22, YPos + 67, 24, BLACK); screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 23, YPos, 14, colour); screen.drawFastVLine(XPos + 23, YPos + 14, 37, BLACK); screen.drawFastVLine(XPos + 23, YPos + 51, 15, colour); screen.drawFastVLine(XPos + 23, YPos + 66, 25, BLACK); screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 24, YPos, 14, colour); screen.drawFastVLine(XPos + 24, YPos + 14, 37, BLACK); screen.drawFastVLine(XPos + 24, YPos + 51, 15, colour); screen.drawFastVLine(XPos + 24, YPos + 66, 25, BLACK); screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
      screen.drawFastVLine(XPos + 25, YPos, 15, colour); screen.drawFastVLine(XPos + 25, YPos + 15, 35, BLACK); screen.drawFastVLine(XPos + 25, YPos + 50, 15, colour); screen.drawFastVLine(XPos + 25, YPos + 65, 25, BLACK); screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
      screen.drawFastVLine(XPos + 26, YPos, 16, colour); screen.drawFastVLine(XPos + 26, YPos + 16, 33, BLACK); screen.drawFastVLine(XPos + 26, YPos + 49, 16, colour); screen.drawFastVLine(XPos + 26, YPos + 65, 24, BLACK); screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
      screen.drawFastVLine(XPos + 27, YPos, 105, colour);
      screen.drawFastVLine(XPos + 28, YPos, 105, colour);
      screen.drawFastVLine(XPos + 29, YPos, 105, colour);
      screen.drawPixel(XPos + 30, YPos, BLACK); screen.drawFastVLine(XPos + 30, YPos + 1, 103, colour); screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      screen.drawPixel(XPos + 31, YPos, BLACK); screen.drawFastVLine(XPos + 31, YPos + 1, 103, colour); screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      screen.drawPixel(XPos + 32, YPos, BLACK); screen.drawFastVLine(XPos + 32, YPos + 1, 103, colour); screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      screen.drawPixel(XPos + 33, YPos, BLACK); screen.drawFastVLine(XPos + 33, YPos + 1, 103, colour); screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      screen.drawPixel(XPos + 34, YPos, BLACK); screen.drawFastVLine(XPos + 34, YPos + 1, 103, colour); screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 36, YPos, 2, BLACK); screen.drawFastVLine(XPos + 36, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      screen.drawFastVLine(XPos + 37, YPos, 3, BLACK); screen.drawFastVLine(XPos + 37, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 38, YPos, 3, BLACK); screen.drawFastVLine(XPos + 38, YPos + 3, 99, colour); screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      screen.drawFastVLine(XPos + 39, YPos, 4, BLACK); screen.drawFastVLine(XPos + 39, YPos + 4, 97, colour); screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      screen.drawFastVLine(XPos + 40, YPos, 5, BLACK); screen.drawFastVLine(XPos + 40, YPos + 5, 95, colour); screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      screen.drawFastVLine(XPos + 41, YPos, 6, BLACK); screen.drawFastVLine(XPos + 41, YPos + 6, 93, colour); screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      screen.drawFastVLine(XPos + 42, YPos, 7, BLACK); screen.drawFastVLine(XPos + 42, YPos + 7, 91, colour); screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      screen.drawFastVLine(XPos + 43, YPos, 9, BLACK); screen.drawFastVLine(XPos + 43, YPos + 9, 89, colour); screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      screen.drawFastVLine(XPos + 44, YPos, 11, BLACK); screen.drawFastVLine(XPos + 44, YPos + 11, 83, colour); screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      screen.drawFastVLine(XPos + 45, YPos, 13, BLACK); screen.drawFastVLine(XPos + 45, YPos + 13, 79, colour); screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      screen.drawFastVLine(XPos + 46, YPos, 17, BLACK); screen.drawFastVLine(XPos + 46, YPos + 17, 71, colour); screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

      // screen.drawPixel(XPos + 30, YPos, BLACK); screen.drawFastVLine(XPos + 30, YPos, 105, colour); screen.drawPixel(XPos + 30, YPos + 104, BLACK);
      // screen.drawPixel(XPos + 31, YPos, BLACK); screen.drawFastVLine(XPos + 31, YPos, 105, colour); screen.drawPixel(XPos + 31, YPos + 104, BLACK);
      // screen.drawPixel(XPos + 32, YPos, BLACK); screen.drawFastVLine(XPos + 32, YPos, 105, colour); screen.drawPixel(XPos + 32, YPos + 104, BLACK);
      // screen.drawPixel(XPos + 33, YPos, BLACK); screen.drawFastVLine(XPos + 33, YPos, 105, colour); screen.drawPixel(XPos + 33, YPos + 104, BLACK);
      // screen.drawPixel(XPos + 34, YPos, BLACK); screen.drawFastVLine(XPos + 34, YPos, 105, colour); screen.drawPixel(XPos + 34, YPos + 104, BLACK);
      // screen.drawFastVLine(XPos + 35, YPos, 2, BLACK); screen.drawFastVLine(XPos + 35, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
      // screen.drawFastVLine(XPos + 36, YPos, 2, BLACK); screen.drawFastVLine(XPos + 36, YPos + 2, 101, colour); screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
      // screen.drawFastVLine(XPos + 37, YPos, 3, BLACK); screen.drawFastVLine(XPos + 37, YPos + 3, 98, colour); screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
      // screen.drawFastVLine(XPos + 38, YPos, 3, BLACK); screen.drawFastVLine(XPos + 38, YPos + 3, 97, colour); screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
      // screen.drawFastVLine(XPos + 39, YPos, 4, BLACK); screen.drawFastVLine(XPos + 39, YPos + 4, 97, colour); screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
      // screen.drawFastVLine(XPos + 40, YPos, 5, BLACK); screen.drawFastVLine(XPos + 40, YPos + 5, 95, colour); screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
      // screen.drawFastVLine(XPos + 41, YPos, 6, BLACK); screen.drawFastVLine(XPos + 41, YPos + 6, 93, colour); screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
      // screen.drawFastVLine(XPos + 42, YPos, 7, BLACK); screen.drawFastVLine(XPos + 42, YPos + 7, 91, colour); screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
      // screen.drawFastVLine(XPos + 43, YPos, 9, BLACK); screen.drawFastVLine(XPos + 43, YPos + 9, 87, colour); screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
      // screen.drawFastVLine(XPos + 44, YPos, 11, BLACK); screen.drawFastVLine(XPos + 44, YPos + 11, 83, colour); screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
      // screen.drawFastVLine(XPos + 45, YPos, 13, BLACK); screen.drawFastVLine(XPos + 45, YPos + 13, 79, colour); screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
      // screen.drawFastVLine(XPos + 46, YPos, 17, BLACK); screen.drawFastVLine(XPos + 46, YPos + 17, 71, colour); screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

      screen.fillRect(XPos + 47, YPos, space, 105, BLACK);
      XPos = XPos + 47 + space;
    }
  }
  // "°C"
  screen.drawFastVLine(XPos, YPos, 20, BLACK);
  screen.drawFastVLine(XPos, YPos + 20, 8, colour);
  screen.drawFastVLine(XPos, YPos + 28, 77, BLACK);  // "°"
  screen.drawFastVLine(XPos + 1, YPos, 14, BLACK);
  screen.drawFastVLine(XPos + 1, YPos + 14, 19, colour);
  screen.drawFastVLine(XPos + 1, YPos + 33, 72, BLACK);
  screen.drawFastVLine(XPos + 2, YPos, 13, BLACK);
  screen.drawFastVLine(XPos + 2, YPos + 13, 22, colour);
  screen.drawFastVLine(XPos + 2, YPos + 35, 70, BLACK);
  screen.drawFastVLine(XPos + 3, YPos, 10, BLACK);
  screen.drawFastVLine(XPos + 3, YPos + 10, 27, colour);
  screen.drawFastVLine(XPos + 3, YPos + 37, 68, BLACK);
  screen.drawFastVLine(XPos + 4, YPos, 9, BLACK);
  screen.drawFastVLine(XPos + 4, YPos + 9, 29, colour);
  screen.drawFastVLine(XPos + 4, YPos + 38, 67, BLACK);
  screen.drawFastVLine(XPos + 5, YPos, 7, BLACK);
  screen.drawFastVLine(XPos + 5, YPos + 7, 33, colour);
  screen.drawFastVLine(XPos + 5, YPos + 40, 65, BLACK);
  screen.drawFastVLine(XPos + 6, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 6, YPos + 7, 14, colour);
  screen.drawFastVLine(XPos + 6, YPos + 21, 5, BLACK);
  screen.drawFastVLine(XPos + 6, YPos + 26, 14, colour);
  screen.drawFastVLine(XPos + 6, YPos + 40, 65, BLACK);
  screen.drawFastVLine(XPos + 7, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 7, YPos + 6, 12, colour);
  screen.drawFastVLine(XPos + 7, YPos + 18, 11, BLACK);
  screen.drawFastVLine(XPos + 7, YPos + 29, 12, colour);
  screen.drawFastVLine(XPos + 7, YPos + 41, 64, BLACK);
  screen.drawFastVLine(XPos + 8, YPos, 5, BLACK);
  screen.drawFastVLine(XPos + 8, YPos + 5, 10, colour);
  screen.drawFastVLine(XPos + 8, YPos + 15, 17, BLACK);
  screen.drawFastVLine(XPos + 8, YPos + 32, 10, colour);
  screen.drawFastVLine(XPos + 8, YPos + 42, 63, BLACK);
  screen.drawFastVLine(XPos + 9, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 9, YPos + 4, 11, colour);
  screen.drawFastVLine(XPos + 9, YPos + 15, 17, BLACK);
  screen.drawFastVLine(XPos + 9, YPos + 32, 10, colour);
  screen.drawFastVLine(XPos + 9, YPos + 42, 63, BLACK);
  screen.drawFastVLine(XPos + 10, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 10, YPos + 4, 9, colour);
  screen.drawFastVLine(XPos + 10, YPos + 13, 21, BLACK);
  screen.drawFastVLine(XPos + 10, YPos + 34, 9, colour);
  screen.drawFastVLine(XPos + 10, YPos + 43, 62, BLACK);
  screen.drawFastVLine(XPos + 11, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 11, YPos + 4, 9, colour);
  screen.drawFastVLine(XPos + 11, YPos + 13, 21, BLACK);
  screen.drawFastVLine(XPos + 11, YPos + 34, 9, colour);
  screen.drawFastVLine(XPos + 11, YPos + 43, 62, BLACK);
  screen.drawFastVLine(XPos + 12, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 12, YPos + 3, 9, colour);
  screen.drawFastVLine(XPos + 12, YPos + 12, 23, BLACK);
  screen.drawFastVLine(XPos + 12, YPos + 35, 9, colour);
  screen.drawFastVLine(XPos + 12, YPos + 44, 61, BLACK);
  screen.drawFastVLine(XPos + 13, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 13, YPos + 3, 9, colour);
  screen.drawFastVLine(XPos + 13, YPos + 12, 23, BLACK);
  screen.drawFastVLine(XPos + 13, YPos + 35, 9, colour);
  screen.drawFastVLine(XPos + 13, YPos + 44, 61, BLACK);
  screen.drawFastVLine(XPos + 14, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 14, YPos + 3, 9, colour);
  screen.drawFastVLine(XPos + 14, YPos + 12, 23, BLACK);
  screen.drawFastVLine(XPos + 14, YPos + 35, 9, colour);
  screen.drawFastVLine(XPos + 14, YPos + 44, 61, BLACK);
  screen.drawFastVLine(XPos + 15, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 15, YPos + 3, 9, colour);
  screen.drawFastVLine(XPos + 15, YPos + 12, 23, BLACK);
  screen.drawFastVLine(XPos + 15, YPos + 35, 9, colour);
  screen.drawFastVLine(XPos + 15, YPos + 44, 61, BLACK);
  screen.drawFastVLine(XPos + 16, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 16, YPos + 3, 10, colour);
  screen.drawFastVLine(XPos + 16, YPos + 13, 21, BLACK);
  screen.drawFastVLine(XPos + 16, YPos + 34, 9, colour);
  screen.drawFastVLine(XPos + 16, YPos + 43, 62, BLACK);
  screen.drawFastVLine(XPos + 17, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 17, YPos + 4, 9, colour);
  screen.drawFastVLine(XPos + 17, YPos + 13, 21, BLACK);
  screen.drawFastVLine(XPos + 17, YPos + 34, 9, colour);
  screen.drawFastVLine(XPos + 17, YPos + 43, 62, BLACK);
  screen.drawFastVLine(XPos + 18, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 18, YPos + 4, 10, colour);
  screen.drawFastVLine(XPos + 18, YPos + 14, 18, BLACK);
  screen.drawFastVLine(XPos + 18, YPos + 32, 10, colour);
  screen.drawFastVLine(XPos + 18, YPos + 42, 63, BLACK);
  screen.drawFastVLine(XPos + 19, YPos, 5, BLACK);
  screen.drawFastVLine(XPos + 19, YPos + 5, 10, colour);
  screen.drawFastVLine(XPos + 19, YPos + 15, 17, BLACK);
  screen.drawFastVLine(XPos + 19, YPos + 32, 10, colour);
  screen.drawFastVLine(XPos + 19, YPos + 42, 63, BLACK);
  screen.drawFastVLine(XPos + 20, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 20, YPos + 6, 12, colour);
  screen.drawFastVLine(XPos + 20, YPos + 18, 11, BLACK);
  screen.drawFastVLine(XPos + 20, YPos + 29, 12, colour);
  screen.drawFastVLine(XPos + 20, YPos + 41, 64, BLACK);
  screen.drawFastVLine(XPos + 21, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 21, YPos + 6, 15, colour);
  screen.drawFastVLine(XPos + 21, YPos + 21, 5, BLACK);
  screen.drawFastVLine(XPos + 21, YPos + 26, 14, colour);
  screen.drawFastVLine(XPos + 21, YPos + 40, 65, BLACK);
  screen.drawFastVLine(XPos + 22, YPos, 7, BLACK);
  screen.drawFastVLine(XPos + 22, YPos + 7, 33, colour);
  screen.drawFastVLine(XPos + 22, YPos + 40, 65, BLACK);
  screen.drawFastVLine(XPos + 23, YPos, 9, BLACK);
  screen.drawFastVLine(XPos + 23, YPos + 9, 29, colour);
  screen.drawFastVLine(XPos + 23, YPos + 38, 67, BLACK);
  screen.drawFastVLine(XPos + 24, YPos, 10, BLACK);
  screen.drawFastVLine(XPos + 24, YPos + 10, 27, colour);
  screen.drawFastVLine(XPos + 24, YPos + 37, 68, BLACK);
  screen.drawFastVLine(XPos + 25, YPos, 13, BLACK);
  screen.drawFastVLine(XPos + 25, YPos + 13, 21, colour);
  screen.drawFastVLine(XPos + 25, YPos + 34, 71, BLACK);
  screen.drawFastVLine(XPos + 26, YPos, 14, BLACK);
  screen.drawFastVLine(XPos + 26, YPos + 14, 19, colour);
  screen.drawFastVLine(XPos + 26, YPos + 33, 72, BLACK);
  screen.drawFastVLine(XPos + 27, YPos, 20, BLACK);
  screen.drawFastVLine(XPos + 27, YPos + 20, 7, colour);
  screen.drawFastVLine(XPos + 27, YPos + 27, 78, BLACK);
  screen.fillRect(XPos + 28, YPos, space, 105, BLACK);
  XPos = XPos + 28 + space;
  screen.drawFastVLine(XPos, YPos, 17, BLACK);
  screen.drawFastVLine(XPos, YPos + 17, 71, colour);
  screen.drawFastVLine(XPos, YPos + 88, 17, BLACK);  // "C"
  screen.drawFastVLine(XPos + 1, YPos, 13, BLACK);
  screen.drawFastVLine(XPos + 1, YPos + 13, 79, colour);
  screen.drawFastVLine(XPos + 1, YPos + 92, 13, BLACK);
  screen.drawFastVLine(XPos + 2, YPos, 11, BLACK);
  screen.drawFastVLine(XPos + 2, YPos + 11, 83, colour);
  screen.drawFastVLine(XPos + 2, YPos + 94, 11, BLACK);
  screen.drawFastVLine(XPos + 3, YPos, 8, BLACK);
  screen.drawFastVLine(XPos + 3, YPos + 8, 87, colour);
  screen.drawFastVLine(XPos + 3, YPos + 96, 9, BLACK);
  screen.drawFastVLine(XPos + 4, YPos, 7, BLACK);
  screen.drawFastVLine(XPos + 4, YPos + 7, 91, colour);
  screen.drawFastVLine(XPos + 4, YPos + 98, 7, BLACK);
  screen.drawFastVLine(XPos + 5, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 5, YPos + 6, 93, colour);
  screen.drawFastVLine(XPos + 5, YPos + 99, 6, BLACK);
  screen.drawFastVLine(XPos + 6, YPos, 5, BLACK);
  screen.drawFastVLine(XPos + 6, YPos + 5, 95, colour);
  screen.drawFastVLine(XPos + 6, YPos + 100, 5, BLACK);
  screen.drawFastVLine(XPos + 7, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 7, YPos + 4, 97, colour);
  screen.drawFastVLine(XPos + 7, YPos + 101, 4, BLACK);
  screen.drawFastVLine(XPos + 8, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 8, YPos + 3, 99, colour);
  screen.drawFastVLine(XPos + 8, YPos + 102, 3, BLACK);
  screen.drawFastVLine(XPos + 9, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 9, YPos + 3, 99, colour);
  screen.drawFastVLine(XPos + 9, YPos + 102, 3, BLACK);
  screen.drawFastVLine(XPos + 10, YPos, 2, BLACK);
  screen.drawFastVLine(XPos + 10, YPos + 2, 101, colour);
  screen.drawFastVLine(XPos + 10, YPos + 103, 2, BLACK);
  screen.drawFastVLine(XPos + 11, YPos, 2, BLACK);
  screen.drawFastVLine(XPos + 11, YPos + 2, 101, colour);
  screen.drawFastVLine(XPos + 11, YPos + 103, 2, BLACK);
  screen.drawPixel(XPos + 12, YPos, BLACK);
  screen.drawFastVLine(XPos + 12, YPos + 1, 103, colour);
  screen.drawPixel(XPos + 12, YPos + 104, BLACK);
  screen.drawPixel(XPos + 13, YPos, BLACK);
  screen.drawFastVLine(XPos + 13, YPos + 1, 103, colour);
  screen.drawPixel(XPos + 13, YPos + 104, BLACK);
  screen.drawPixel(XPos + 14, YPos, BLACK);
  screen.drawFastVLine(XPos + 14, YPos + 1, 103, colour);
  screen.drawPixel(XPos + 14, YPos + 104, BLACK);
  screen.drawPixel(XPos + 15, YPos, BLACK);
  screen.drawFastVLine(XPos + 15, YPos + 1, 103, colour);
  screen.drawPixel(XPos + 15, YPos + 104, BLACK);
  screen.drawPixel(XPos + 16, YPos, BLACK);
  screen.drawFastVLine(XPos + 16, YPos + 1, 103, colour);
  screen.drawPixel(XPos + 16, YPos + 104, BLACK);
  screen.drawFastVLine(XPos + 17, YPos, 105, colour);
  screen.drawFastVLine(XPos + 18, YPos, 105, colour);
  screen.drawFastVLine(XPos + 19, YPos, 105, colour);
  screen.drawFastVLine(XPos + 20, YPos, 16, colour);
  screen.drawFastVLine(XPos + 20, YPos + 16, 73, BLACK);
  screen.drawFastVLine(XPos + 20, YPos + 89, 16, colour);
  screen.drawFastVLine(XPos + 21, YPos, 15, colour);
  screen.drawFastVLine(XPos + 21, YPos + 15, 75, BLACK);
  screen.drawFastVLine(XPos + 21, YPos + 90, 15, colour);
  screen.drawFastVLine(XPos + 22, YPos, 14, colour);
  screen.drawFastVLine(XPos + 22, YPos + 14, 77, BLACK);
  screen.drawFastVLine(XPos + 22, YPos + 91, 14, colour);
  screen.drawFastVLine(XPos + 23, YPos, 14, colour);
  screen.drawFastVLine(XPos + 23, YPos + 14, 77, BLACK);
  screen.drawFastVLine(XPos + 23, YPos + 91, 14, colour);
  screen.drawFastVLine(XPos + 24, YPos, 14, colour);
  screen.drawFastVLine(XPos + 24, YPos + 14, 77, BLACK);
  screen.drawFastVLine(XPos + 24, YPos + 91, 14, colour);
  screen.drawFastVLine(XPos + 25, YPos, 15, colour);
  screen.drawFastVLine(XPos + 25, YPos + 15, 75, BLACK);
  screen.drawFastVLine(XPos + 25, YPos + 90, 15, colour);
  screen.drawFastVLine(XPos + 26, YPos, 16, colour);
  screen.drawFastVLine(XPos + 26, YPos + 16, 73, BLACK);
  screen.drawFastVLine(XPos + 26, YPos + 89, 16, colour);
  screen.drawFastVLine(XPos + 27, YPos, 37, colour);
  screen.drawFastVLine(XPos + 27, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 27, YPos + 66, 39, colour);
  screen.drawFastVLine(XPos + 28, YPos, 37, colour);
  screen.drawFastVLine(XPos + 28, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 28, YPos + 66, 39, colour);
  screen.drawFastVLine(XPos + 29, YPos, 37, colour);
  screen.drawFastVLine(XPos + 29, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 29, YPos + 66, 39, colour);
  screen.drawPixel(XPos + 30, YPos, BLACK);
  screen.drawFastVLine(XPos + 30, YPos + 1, 36, colour);
  screen.drawFastVLine(XPos + 30, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 30, YPos + 66, 38, colour);
  screen.drawPixel(XPos + 30, YPos + 104, BLACK);
  screen.drawPixel(XPos + 31, YPos, BLACK);
  screen.drawFastVLine(XPos + 31, YPos + 1, 36, colour);
  screen.drawFastVLine(XPos + 31, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 31, YPos + 66, 38, colour);
  screen.drawPixel(XPos + 31, YPos + 104, BLACK);
  screen.drawPixel(XPos + 32, YPos, BLACK);
  screen.drawFastVLine(XPos + 32, YPos + 1, 36, colour);
  screen.drawFastVLine(XPos + 32, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 32, YPos + 66, 38, colour);
  screen.drawPixel(XPos + 32, YPos + 104, BLACK);
  screen.drawPixel(XPos + 33, YPos, BLACK);
  screen.drawFastVLine(XPos + 33, YPos + 1, 36, colour);
  screen.drawFastVLine(XPos + 33, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 33, YPos + 66, 38, colour);
  screen.drawPixel(XPos + 33, YPos + 104, BLACK);
  screen.drawPixel(XPos + 34, YPos, BLACK);
  screen.drawFastVLine(XPos + 34, YPos + 1, 36, colour);
  screen.drawFastVLine(XPos + 34, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 34, YPos + 66, 38, colour);
  screen.drawPixel(XPos + 34, YPos + 104, BLACK);
  screen.drawFastVLine(XPos + 35, YPos, 2, BLACK);
  screen.drawFastVLine(XPos + 35, YPos + 2, 35, colour);
  screen.drawFastVLine(XPos + 35, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 35, YPos + 66, 37, colour);
  screen.drawFastVLine(XPos + 35, YPos + 103, 2, BLACK);
  screen.drawFastVLine(XPos + 36, YPos, 2, BLACK);
  screen.drawFastVLine(XPos + 36, YPos + 2, 35, colour);
  screen.drawFastVLine(XPos + 36, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 36, YPos + 66, 37, colour);
  screen.drawFastVLine(XPos + 36, YPos + 103, 2, BLACK);
  screen.drawFastVLine(XPos + 37, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 37, YPos + 3, 34, colour);
  screen.drawFastVLine(XPos + 37, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 37, YPos + 66, 36, colour);
  screen.drawFastVLine(XPos + 37, YPos + 102, 3, BLACK);
  screen.drawFastVLine(XPos + 38, YPos, 3, BLACK);
  screen.drawFastVLine(XPos + 38, YPos + 3, 34, colour);
  screen.drawFastVLine(XPos + 38, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 38, YPos + 66, 36, colour);
  screen.drawFastVLine(XPos + 38, YPos + 102, 3, BLACK);
  screen.drawFastVLine(XPos + 39, YPos, 4, BLACK);
  screen.drawFastVLine(XPos + 39, YPos + 4, 33, colour);
  screen.drawFastVLine(XPos + 39, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 39, YPos + 66, 35, colour);
  screen.drawFastVLine(XPos + 39, YPos + 101, 4, BLACK);
  screen.drawFastVLine(XPos + 40, YPos, 5, BLACK);
  screen.drawFastVLine(XPos + 40, YPos + 5, 32, colour);
  screen.drawFastVLine(XPos + 40, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 40, YPos + 66, 34, colour);
  screen.drawFastVLine(XPos + 40, YPos + 100, 5, BLACK);
  screen.drawFastVLine(XPos + 41, YPos, 6, BLACK);
  screen.drawFastVLine(XPos + 41, YPos + 6, 31, colour);
  screen.drawFastVLine(XPos + 41, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 41, YPos + 66, 33, colour);
  screen.drawFastVLine(XPos + 41, YPos + 99, 6, BLACK);
  screen.drawFastVLine(XPos + 42, YPos, 7, BLACK);
  screen.drawFastVLine(XPos + 42, YPos + 7, 30, colour);
  screen.drawFastVLine(XPos + 42, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 42, YPos + 66, 32, colour);
  screen.drawFastVLine(XPos + 42, YPos + 98, 7, BLACK);
  screen.drawFastVLine(XPos + 43, YPos, 9, BLACK);
  screen.drawFastVLine(XPos + 43, YPos + 9, 28, colour);
  screen.drawFastVLine(XPos + 43, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 43, YPos + 66, 30, colour);
  screen.drawFastVLine(XPos + 43, YPos + 96, 9, BLACK);
  screen.drawFastVLine(XPos + 44, YPos, 11, BLACK);
  screen.drawFastVLine(XPos + 44, YPos + 11, 26, colour);
  screen.drawFastVLine(XPos + 44, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 44, YPos + 66, 28, colour);
  screen.drawFastVLine(XPos + 44, YPos + 94, 11, BLACK);
  screen.drawFastVLine(XPos + 45, YPos, 13, BLACK);
  screen.drawFastVLine(XPos + 45, YPos + 13, 24, colour);
  screen.drawFastVLine(XPos + 45, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 45, YPos + 66, 26, colour);
  screen.drawFastVLine(XPos + 45, YPos + 92, 13, BLACK);
  screen.drawFastVLine(XPos + 46, YPos, 17, BLACK);
  screen.drawFastVLine(XPos + 46, YPos + 17, 20, colour);
  screen.drawFastVLine(XPos + 46, YPos + 37, 29, BLACK);
  screen.drawFastVLine(XPos + 46, YPos + 66, 22, colour);
  screen.drawFastVLine(XPos + 46, YPos + 88, 17, BLACK);

  screen.fillRect(XPos + 47, YPos, MODE_XPOS - XPos - 50, 105, BLACK);
}

void drawSmNum(float number, int XPos, int YPos, uint16_t colour) {
  char num[6];
  char digit[2];
  int space = 1;

  dtostrf(number, 6, 0, num);
  for (int count = 0; count < 6; count++) {
    // Serial.print("Character: "); Serial.print(num[count]); Serial.print(", Position: "); Serial.print(XPos); Serial.print(","); Serial.println(YPos);
    // strcpy(digit, num[count]);
    if (num[count] == '-') {
      screen.drawFastVLine(XPos, YPos, 10, BLACK); screen.drawFastVLine(XPos, YPos + 10, 3, colour); screen.drawFastVLine(XPos, YPos + 13, 6, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 10, BLACK); screen.drawFastVLine(XPos + 1, YPos + 10, 3, colour); screen.drawFastVLine(XPos + 1, YPos + 13, 6, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 10, BLACK); screen.drawFastVLine(XPos + 2, YPos + 10, 3, colour); screen.drawFastVLine(XPos + 2, YPos + 13, 6, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 10, BLACK); screen.drawFastVLine(XPos + 3, YPos + 10, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 13, 6, BLACK);

      screen.fillRect(XPos + 4, YPos, space, 19, BLACK);
      XPos = XPos + 4 + space;
    } else if (num[count] == '.') {
      screen.drawFastVLine(XPos, YPos, 16, BLACK); screen.drawFastVLine(XPos, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 1, YPos, 16, BLACK); screen.drawFastVLine(XPos + 1, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 2, YPos, 16, BLACK); screen.drawFastVLine(XPos + 2, YPos + 16, 3, colour);

      screen.fillRect(XPos + 3, YPos, space, 19, BLACK);
      XPos = XPos + 3 + space;
    } else if (num[count] == '0') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 15, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 1, 17, colour); screen.drawPixel(XPos + 1, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 19, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 13, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 13, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 19, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 17, colour); screen.drawPixel(XPos + 6, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 3, 13, colour); screen.drawFastVLine(XPos + 7, YPos + 16, 3, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '1') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 2, colour); screen.drawFastVLine(XPos, YPos + 4, 15, BLACK);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 2, 3, colour); screen.drawFastVLine(XPos + 1, YPos + 4, 15, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 19, colour);
      screen.drawFastVLine(XPos + 3, YPos, 19, colour);
      screen.drawFastVLine(XPos + 4, YPos, 19, colour);
      screen.fillRect(XPos + 5, YPos, space, 19, BLACK);

      XPos = XPos + 5 + space;
    } else if (num[count] == '2') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 5, colour); screen.drawFastVLine(XPos, YPos + 7, 6, BLACK); screen.drawFastVLine(XPos, YPos + 13, 6, colour);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 1, 6, colour); screen.drawFastVLine(XPos + 1, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 1, YPos + 11, 8, colour);
      screen.drawFastVLine(XPos + 2, YPos, 7, colour); screen.drawFastVLine(XPos + 2, YPos + 7, 2, BLACK); screen.drawFastVLine(XPos + 2, YPos + 9, 10, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 5, BLACK); screen.drawFastVLine(XPos + 3, YPos + 8, 7, colour); screen.drawPixel(XPos + 3, YPos + 15, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 3, BLACK); screen.drawFastVLine(XPos + 4, YPos + 6, 7, colour); screen.drawFastVLine(XPos + 4, YPos + 13, 3, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 11, colour); screen.drawFastVLine(XPos + 5, YPos + 11, 5, BLACK); screen.drawFastVLine(XPos + 5, YPos + 16, 3, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 8, colour); screen.drawFastVLine(XPos + 6, YPos + 9, 7, BLACK); screen.drawFastVLine(XPos + 6, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 7, YPos, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 2, 5, colour); screen.drawFastVLine(XPos + 7, YPos + 7, 9, BLACK); screen.drawFastVLine(XPos + 7, YPos + 16, 3, colour);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '3') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 5, colour); screen.drawFastVLine(XPos, YPos + 7, 5, BLACK); screen.drawFastVLine(XPos, YPos + 12, 5, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 1, 6, colour); screen.drawFastVLine(XPos + 1, YPos + 7, 5, BLACK); screen.drawFastVLine(XPos + 1, YPos + 12, 6, colour); screen.drawPixel(XPos + 1, YPos, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 7, colour); screen.drawPixel(XPos + 2, YPos + 7, BLACK); screen.drawFastVLine(XPos + 2, YPos + 8, 3, colour); screen.drawPixel(XPos + 2, YPos + 11, BLACK); screen.drawFastVLine(XPos + 2, YPos + 12, 7, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 5, BLACK); screen.drawFastVLine(XPos + 3, YPos + 8, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 11, 5, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 5, BLACK); screen.drawFastVLine(XPos + 4, YPos + 8, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 11, 5, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 19, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 17, colour); screen.drawPixel(XPos + 6, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 2, 7, colour); screen.drawPixel(XPos + 7, YPos + 9, BLACK); screen.drawFastVLine(XPos + 7, YPos + 10, 7, colour); screen.drawFastVLine(XPos + 7, YPos + 17, 2, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '4') {
      screen.drawFastVLine(XPos, YPos, 9, BLACK); screen.drawFastVLine(XPos, YPos + 9, 6, colour); screen.drawFastVLine(XPos, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 6, BLACK); screen.drawFastVLine(XPos + 1, YPos + 6, 9, colour); screen.drawFastVLine(XPos + 1, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 2, BLACK); screen.drawFastVLine(XPos + 2, YPos + 2, 13, colour); screen.drawFastVLine(XPos + 2, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 3, YPos, 10, colour); screen.drawFastVLine(XPos + 3, YPos + 10, 2, BLACK); screen.drawFastVLine(XPos + 3, YPos + 12, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 6, colour); screen.drawFastVLine(XPos + 4, YPos + 6, 6, BLACK); screen.drawFastVLine(XPos + 4, YPos + 12, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 3, colour); screen.drawFastVLine(XPos + 5, YPos + 3, 9, BLACK); screen.drawFastVLine(XPos + 5, YPos + 12, 3, colour); screen.drawFastVLine(XPos + 5, YPos + 15, 4, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 19, colour);
      screen.drawFastVLine(XPos + 7, YPos, 19, colour);
      screen.drawFastVLine(XPos + 8, YPos, 19, colour);
      screen.drawFastVLine(XPos + 9, YPos, 12, BLACK); screen.drawFastVLine(XPos + 9, YPos + 12, 3, colour); screen.drawFastVLine(XPos + 9, YPos + 15, 4, BLACK);
      screen.fillRect(XPos + 10, YPos, space, 19, BLACK);

      XPos = XPos + 10 + space;
    } else if (num[count] == '5') {
      screen.drawFastVLine(XPos, YPos, 8, colour); screen.drawFastVLine(XPos, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos, YPos + 11, 6, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawFastVLine(XPos + 1, YPos, 8, colour); screen.drawFastVLine(XPos + 1, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos + 1, YPos + 11, 7, colour); screen.drawPixel(XPos + 1, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 8, colour); screen.drawFastVLine(XPos + 2, YPos + 8, 3, BLACK); screen.drawFastVLine(XPos + 2, YPos + 11, 8, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 2, BLACK); screen.drawFastVLine(XPos + 3, YPos + 5, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 8, 8, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 2, BLACK); screen.drawFastVLine(XPos + 4, YPos + 5, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 8, 8, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 3, colour); screen.drawFastVLine(XPos + 5, YPos + 3, 2, BLACK); screen.drawFastVLine(XPos + 5, YPos + 5, 14, colour);
      screen.drawFastVLine(XPos + 6, YPos, 3, colour); screen.drawFastVLine(XPos + 6, YPos + 3, 2, BLACK); screen.drawFastVLine(XPos + 6, YPos + 5, 13, colour); screen.drawPixel(XPos + 6, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 3, colour); screen.drawFastVLine(XPos + 7, YPos + 3, 3, BLACK); screen.drawFastVLine(XPos + 7, YPos + 6, 11, colour); screen.drawFastVLine(XPos + 7, YPos + 17, 2, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '6') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 15, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawPixel(XPos + 1, YPos, colour); screen.drawFastVLine(XPos + 1, YPos + 1, 17, colour); screen.drawPixel(XPos + 1, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 19, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 4, BLACK); screen.drawFastVLine(XPos + 3, YPos + 7, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 10, 6, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 4, BLACK); screen.drawFastVLine(XPos + 4, YPos + 7, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 10, 6, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 6, colour);
      screen.drawPixel(XPos + 5, YPos + 6, BLACK); screen.drawFastVLine(XPos + 5, YPos + 7, 12, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 5, colour); screen.drawPixel(XPos + 6, YPos + 6, BLACK); screen.drawFastVLine(XPos + 6, YPos + 7, 11, colour); screen.drawPixel(XPos + 6, YPos + 17, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 2, 4, colour); screen.drawFastVLine(XPos + 7, YPos + 6, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 8, 9, colour); screen.drawFastVLine(XPos + 7, YPos + 17, 2, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '7') {
      screen.drawFastVLine(XPos, YPos, 3, colour); screen.drawFastVLine(XPos, YPos + 3, 11, BLACK); screen.drawFastVLine(XPos, YPos + 14, 5, colour);
      screen.drawFastVLine(XPos + 1, YPos, 3, colour); screen.drawFastVLine(XPos + 1, YPos + 3, 7, BLACK); screen.drawFastVLine(XPos + 1, YPos + 10, 9, colour);
      screen.drawFastVLine(XPos + 2, YPos, 3, colour); screen.drawFastVLine(XPos + 2, YPos + 3, 3, BLACK); screen.drawFastVLine(XPos + 2, YPos + 6, 13, colour);
      screen.drawFastVLine(XPos + 3, YPos, 17, colour); screen.drawFastVLine(XPos + 3, YPos + 17, 2, BLACK);
      screen.drawFastVLine(XPos + 4, YPos, 13, colour); screen.drawFastVLine(XPos + 4, YPos + 13, 6, BLACK);
      screen.drawFastVLine(XPos + 5, YPos, 9, colour); screen.drawFastVLine(XPos + 5, YPos + 9, 10, BLACK);
      screen.drawFastVLine(XPos + 6, YPos, 5, colour); screen.drawFastVLine(XPos + 6, YPos + 5, 14, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 3, colour); screen.drawFastVLine(XPos + 7, YPos + 3, 16, BLACK);

      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);
      XPos = XPos + 8 + space;
    } else if (num[count] == '8') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 5, colour); screen.drawFastVLine(XPos, YPos + 7, 3, BLACK); screen.drawFastVLine(XPos, YPos + 10, 7, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 1, 7, colour); screen.drawPixel(XPos + 1, YPos + 8, BLACK); screen.drawFastVLine(XPos + 1, YPos + 9, 9, colour); screen.drawPixel(XPos + 1, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 19, colour); screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 3, BLACK); screen.drawFastVLine(XPos + 3, YPos + 6, 5, colour); screen.drawFastVLine(XPos + 3, YPos + 11, 5, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 3, BLACK); screen.drawFastVLine(XPos + 4, YPos + 6, 5, colour); screen.drawFastVLine(XPos + 4, YPos + 11, 5, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 19, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 7, colour); screen.drawPixel(XPos + 6, YPos + 8, BLACK); screen.drawFastVLine(XPos + 6, YPos + 9, 9, colour); screen.drawPixel(XPos + 6, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 3, BLACK); screen.drawFastVLine(XPos + 7, YPos + 2, 5, colour); screen.drawFastVLine(XPos + 7, YPos + 7, 3, BLACK); screen.drawFastVLine(XPos + 7, YPos + 10, 7, colour); screen.drawFastVLine(XPos + 7, YPos + 17, 2, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    } else if (num[count] == '9') {
      screen.drawFastVLine(XPos, YPos, 2, BLACK); screen.drawFastVLine(XPos, YPos + 2, 10, colour); screen.drawFastVLine(XPos, YPos + 12, 2, BLACK); screen.drawFastVLine(XPos, YPos + 14, 3, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);
      screen.drawPixel(XPos + 1, YPos, BLACK); screen.drawFastVLine(XPos + 1, YPos + 1, 12, colour); screen.drawPixel(XPos + 1, YPos + 13, BLACK); screen.drawFastVLine(XPos + 1, YPos + 14, 4, colour); screen.drawPixel(XPos + 1, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 2, YPos, 13, colour); screen.drawPixel(XPos + 2, YPos + 13, BLACK); screen.drawFastVLine(XPos + 2, YPos + 14, 5, colour);
      screen.drawFastVLine(XPos + 3, YPos, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 3, 7, BLACK); screen.drawFastVLine(XPos + 3, YPos + 10, 3, colour); screen.drawFastVLine(XPos + 3, YPos + 13, 3, BLACK); screen.drawFastVLine(XPos + 3, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 4, YPos, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 3, 7, BLACK); screen.drawFastVLine(XPos + 4, YPos + 10, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 13, 3, BLACK); screen.drawFastVLine(XPos + 4, YPos + 16, 3, colour);
      screen.drawFastVLine(XPos + 5, YPos, 19, colour);
      screen.drawPixel(XPos + 6, YPos, BLACK); screen.drawFastVLine(XPos + 6, YPos + 1, 17, colour); screen.drawPixel(XPos + 6, YPos + 18, BLACK);
      screen.drawFastVLine(XPos + 7, YPos, 2, BLACK); screen.drawFastVLine(XPos + 7, YPos + 2, 15, colour); screen.drawFastVLine(XPos + 7, YPos + 17, 2, BLACK);
      screen.fillRect(XPos + 8, YPos, space, 19, BLACK);

      XPos = XPos + 8 + space;
    }
  }
  // "°C"
  screen.drawFastVLine(XPos, YPos, 3, BLACK);        screen.drawFastVLine(XPos, YPos + 3, 4, colour);      screen.drawFastVLine(XPos, YPos + 7, 12, BLACK);     // "°"
  screen.drawPixel(XPos + 1, YPos, BLACK);           screen.drawFastVLine(XPos + 1, YPos + 1, 8, colour);  screen.drawFastVLine(XPos + 1, YPos + 9, 10, BLACK);
  screen.drawFastVLine(XPos + 2, YPos, 3, colour);   screen.drawFastVLine(XPos + 2, YPos + 3, 4, BLACK);   screen.drawFastVLine(XPos + 2, YPos + 7, 3, colour); screen.drawFastVLine(XPos + 2, YPos + 10, 9, BLACK);
  screen.drawFastVLine(XPos + 3, YPos, 2, colour);   screen.drawFastVLine(XPos + 3, YPos + 2, 6, BLACK);   screen.drawFastVLine(XPos + 3, YPos + 8, 2, colour); screen.drawFastVLine(XPos + 3, YPos + 10, 9, BLACK);
  screen.drawFastVLine(XPos + 4, YPos, 3, colour);   screen.drawFastVLine(XPos + 4, YPos + 3, 4, BLACK);   screen.drawFastVLine(XPos + 4, YPos + 7, 3, colour); screen.drawFastVLine(XPos + 4, YPos + 10, 9, BLACK);
  screen.drawPixel(XPos + 5, YPos, BLACK);           screen.drawFastVLine(XPos + 5, YPos + 1, 8, colour);  screen.drawFastVLine(XPos + 5, YPos + 9, 10, BLACK);
  screen.drawFastVLine(XPos + 6, YPos, 3, BLACK);    screen.drawFastVLine(XPos + 6, YPos + 3, 4, colour);  screen.drawFastVLine(XPos + 6, YPos + 7, 12, BLACK);
  screen.drawFastVLine(XPos + 7, YPos, 19, BLACK);
  screen.drawFastVLine(XPos + 8, YPos, 2, BLACK);    screen.drawFastVLine(XPos + 8, YPos + 2, 15, colour); screen.drawFastVLine(XPos, YPos + 17, 2, BLACK);     // "C"
  screen.drawPixel(XPos + 9, YPos, BLACK);           screen.drawFastVLine(XPos + 9, YPos + 1, 17, colour); screen.drawPixel(XPos + 9, YPos + 18, BLACK);
  screen.drawFastVLine(XPos + 10, YPos, 19, colour);
  screen.drawFastVLine(XPos + 11, YPos, 3, colour);  screen.drawFastVLine(XPos + 11, YPos + 3, 13, BLACK); screen.drawFastVLine(XPos + 11, YPos + 16, 3, colour);
  screen.drawFastVLine(XPos + 12, YPos, 3, colour);  screen.drawFastVLine(XPos + 12, YPos + 3, 13, BLACK); screen.drawFastVLine(XPos + 12, YPos + 16, 3, colour);
  screen.drawFastVLine(XPos + 13, YPos, 7, colour);  screen.drawFastVLine(XPos + 13, YPos + 7, 4, BLACK);  screen.drawFastVLine(XPos + 13, YPos + 11, 8, colour);
  screen.drawPixel(XPos + 14, YPos, BLACK);          screen.drawFastVLine(XPos + 14, YPos + 1, 6, colour); screen.drawFastVLine(XPos + 14, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 14, YPos + 11, 7, colour); screen.drawPixel(XPos + 14, YPos + 18, BLACK);
  screen.drawFastVLine(XPos + 15, YPos, 2, BLACK);   screen.drawFastVLine(XPos + 15, YPos + 2, 5, colour); screen.drawFastVLine(XPos + 15, YPos + 7, 4, BLACK); screen.drawFastVLine(XPos + 15, YPos + 11, 4, colour); screen.drawFastVLine(XPos + 15, YPos + 17, 2, BLACK);
  screen.fillRect(XPos + 16, YPos, MODE_XPOS - XPos - 20, 19, BLACK);
}

void modeIcon(char mode[5]) {
  if (strcmp(mode, "Heat") == 0) {  
    #ifdef DISPDEBUG
    Serial.println("Heat mode");
    #endif
    screen.drawFastVLine(MODE_XPOS, MODE_YPOS, 20, BLACK); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 20, 6, MARS); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS, 19, BLACK); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 19, 9, MARS); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS, 12, BLACK); screen.drawPixel(MODE_XPOS + 2, MODE_YPOS + 12, MARS); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 13, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 20, 9, MARS); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 12, 2, MARS); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 14, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 19, 11, MARS); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 13, 3, MARS); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 17, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 18, 13, MARS); screen.drawPixel(MODE_XPOS + 4, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 13, 18, MARS); screen.drawPixel(MODE_XPOS + 5, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS, 14, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 14, 10, MARS); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 24, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 30, 2, MARS);
    screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 3, 3, MARS); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 6, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 14, 10, MARS); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 24, 7, BLACK); screen.drawPixel(MODE_XPOS + 7, MODE_YPOS + 31, MARS);
    screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 2, 7, MARS); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 9, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 13, 7, MARS); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 20, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 28, 2, ORANGE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 30, 2, BLACK);
    screen.drawPixel(MODE_XPOS + 9, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 1, 19, MARS); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 20, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 26, 5, ORANGE); screen.drawPixel(MODE_XPOS + 9, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 5, 16, MARS); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 21, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 27, 5, ORANGE);
    screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 6, 9, MARS); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 15, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 24, 8, ORANGE);
    screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 7, 9, MARS); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 16, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 25, 4, ORANGE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 6, 11, MARS); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 17, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 24, 4, ORANGE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 5, 11, MARS); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 16, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 22, 5, ORANGE); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 4, 12, MARS); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 16, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 20, 6, ORANGE); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 3, 2, MARS); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 5, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 8, 10, MARS); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 18, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 22, 6, ORANGE); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 9, 10, MARS); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 19, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 25, 4, ORANGE); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 29, 2, BLACK); screen.drawPixel(MODE_XPOS + 17, MODE_YPOS + 31, ORANGE);
    screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 11, 9, MARS); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 20, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 24, 8, ORANGE);
    screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 12, 6, MARS); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 18, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 27, 4, ORANGE); screen.drawPixel(MODE_XPOS + 19, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 11, 8, MARS); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 19, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 27, 3, ORANGE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 8, 15, MARS); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 23, 8, BLACK); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 31, MARS);
    screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 9, 13, MARS); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 22, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 30, 2, MARS);
    screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 11, 11, MARS); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 22, 8, BLACK); screen.drawPixel(MODE_XPOS + 23, MODE_YPOS + 30, MARS); screen.drawPixel(MODE_XPOS + 23, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS, 18, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 18, 3, MARS); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 21, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 29, 2, MARS); screen.drawPixel(MODE_XPOS + 24, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS, 17, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 17, 7, MARS); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 24, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 28, 3, MARS); screen.drawPixel(MODE_XPOS + 25, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS, 17, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 17, 8, MARS); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 25, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 27, 3, MARS); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 16, 6, MARS); screen.drawPixel(MODE_XPOS + 27, MODE_YPOS + 22, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 23, 7, MARS); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 13, 7, MARS); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 20, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 23, 6, MARS); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS, 14, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 14, 4, MARS); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 19, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 22, 6, MARS); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS, 21, BLACK); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 21, 6, MARS); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS, 20, BLACK); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 20, 6, MARS); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 26, 6, BLACK);
  } else if (strcmp(mode, "Fan") == 0) {
    #ifdef DISPDEBUG
    Serial.println("Fan Mode");
    #endif
    screen.drawFastVLine(MODE_XPOS, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 20, 12, BLACK);
    screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 9, 14, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 8, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 12, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 20, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 6, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 10, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 14, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 19, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 22, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 5, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 8, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 13, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 20, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 24, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 4, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 7, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 20, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 25, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 3, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 6, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 20, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 26, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 3, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 5, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 12, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 19, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 27, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 2, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 4, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 12, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 19, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 28, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 30, 2, BLACK);
    screen.drawPixel(MODE_XPOS + 9, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 1, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 4, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 12, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 18, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 28, 3, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 9, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 10, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 1, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 3, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 13, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 18, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 29, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 10, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 11, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 1, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 3, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 13, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 17, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 29, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 11, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 2, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 4, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 7, 21, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 22, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 27, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 13, MODE_YPOS + 2, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 3, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 9, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 14, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 18, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 22, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 28, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 14, MODE_YPOS + 2, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 3, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 11, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 13, 6, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 14, MODE_YPOS + 19, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 20, 9, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 14, MODE_YPOS + 29, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 15, MODE_YPOS + 2, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 3, 9, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 15, MODE_YPOS + 12, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 13, 6, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 15, MODE_YPOS + 19, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 20, 9, LIGHT_BLUE);screen.drawPixel(MODE_XPOS + 15, MODE_YPOS + 29, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 16, MODE_YPOS + 2, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 3, 9, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 16, MODE_YPOS + 12, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 13, 6, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 16, MODE_YPOS + 19, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 20, 9, LIGHT_BLUE);screen.drawPixel(MODE_XPOS + 16, MODE_YPOS + 29, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 17, MODE_YPOS + 2, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 3, 9, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 17, MODE_YPOS + 12, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 13, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 19, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 21, 8, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 17, MODE_YPOS + 29, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 2, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 4, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 10, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 14, 4, LIGHT_BLUE);  screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 18, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 23, 6, LIGHT_BLUE);screen.drawPixel(MODE_XPOS + 18, MODE_YPOS + 29, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 2, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 5, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 10, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 25, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 28, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 30, 2, LIGHT_BLUE);
    screen.drawPixel(MODE_XPOS + 20, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 1, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 3, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 15, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 19, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 29, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 20, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 21, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 1, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 3, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 14, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 19, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 29, 2, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 22, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 1, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 4, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 14, 6, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 20, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 28, 3, LIGHT_BLUE); screen.drawPixel(MODE_XPOS + 22, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 2, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 4, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 13, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 20, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 28, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 3, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 5, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 13, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 20, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 27, 2, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 3, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 6, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 20, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 26, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 4, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 7, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 20, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 25, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 5, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 8, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 12, 7, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 19, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 24, 3, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 6, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 10, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 13, 5, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 18, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 22, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 8, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 12, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 20, 4, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 9, 14, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 12, 8, LIGHT_BLUE); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 20, 12, BLACK);
  } else if (strcmp(mode, "Cool") == 0) {
    #ifdef DISPDEBUG
    Serial.println("Cool mode");
    #endif
    screen.drawFastVLine(MODE_XPOS, MODE_YPOS, 12, BLACK);     screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 12, 2, ICE_BLUE);     screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 14, 2, BLACK);     screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 16, 2, ICE_BLUE);     screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 18, 14, BLACK);
    screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 12, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 15, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 17, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 20, 12, BLACK);
    screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS, 8, BLACK);  screen.drawPixel(MODE_XPOS + 2, MODE_YPOS + 8, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 9, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 20, 3, BLACK); screen.drawPixel(MODE_XPOS + 2, MODE_YPOS + 23, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 7, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 9, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 20, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 23, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 25, 7, BLACK);
    screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 8, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 10, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 20, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 22, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS, 9, BLACK); screen.drawPixel(MODE_XPOS + 5, MODE_YPOS + 9, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 10, 2, BLACK); screen.drawPixel(MODE_XPOS + 5, MODE_YPOS + 12, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 20, 2, BLACK); screen.drawPixel(MODE_XPOS + 5, MODE_YPOS + 22, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 3, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 6, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 9, 4, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 19, 4, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 23, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 26, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 3, 10, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 19, 10, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 7, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 19, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 25, 7, BLACK);
    screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 11, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 19, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 21, 11, BLACK);
    screen.drawPixel(MODE_XPOS + 10, MODE_YPOS, BLACK); screen.drawPixel(MODE_XPOS + 10, MODE_YPOS + 1, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 2, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 11, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 18, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 21, 9, BLACK); screen.drawPixel(MODE_XPOS + 10, MODE_YPOS + 30, ICE_BLUE); screen.drawPixel(MODE_XPOS + 10, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 11, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 1, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 3, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 20, 9, BLACK);  screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 29, 2, ICE_BLUE);screen.drawPixel(MODE_XPOS + 11, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 2, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 4, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 13, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 15, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 17, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 19, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 28, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 3, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 5, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 13, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 15, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 17, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 19, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 27, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 4, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 6, 7, BLACK);  screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 13, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 19, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 26, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS, 32, ICE_BLUE);
    screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS, 32, ICE_BLUE);
    screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 4, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 6, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 13, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 19, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 26, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 28, 4, BLACK); 
    screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 3, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 5, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 13, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 15, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 17, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 19, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 27, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 2, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 4, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 13, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 15, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 17, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 19, 8, BLACK);  screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 28, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 30, 2, BLACK);
    screen.drawPixel(MODE_XPOS + 20, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 1, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 3, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 12, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 18, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 20, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 29, 2, ICE_BLUE); screen.drawPixel(MODE_XPOS + 20, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 21, MODE_YPOS, BLACK); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 1, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 2, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 11, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 18, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 21, 9, BLACK); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 30, ICE_BLUE); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 11, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 19, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 21, 11, BLACK);
    screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 7, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 19, 6, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 25, 7, BLACK);
    screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 3, 10, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 19, 10, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 3, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 6, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 9, 4, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 13, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 19, 4, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 23, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 26, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS, 9, BLACK); screen.drawPixel(MODE_XPOS + 26, MODE_YPOS + 9, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 10, 2, BLACK); screen.drawPixel(MODE_XPOS + 26, MODE_YPOS + 12, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 13, 6, BLACK); screen.drawPixel(MODE_XPOS + 26, MODE_YPOS + 19, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 20, 2, BLACK); screen.drawPixel(MODE_XPOS + 26, MODE_YPOS + 22, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 8, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 10, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 18,2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 20, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 22, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 7, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 9, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 18,2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 20, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 23, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 25, 7, BLACK);
    screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS, 8, BLACK); screen.drawPixel(MODE_XPOS + 29, MODE_YPOS + 8, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 9, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 12, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 14, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 18,2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 20, 3, BLACK); screen.drawPixel(MODE_XPOS + 29, MODE_YPOS + 23, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 12, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 15, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 17, 3, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 20, 12, BLACK);
    screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 13, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 15, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 17, 2, ICE_BLUE); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 19, 13, BLACK);
  } else if (strcmp(mode, "Off") == 0) {
    #ifdef DISPDEBUG
    Serial.println("All off");
    #endif
    screen.drawFastVLine(MODE_XPOS, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 12, 8, RED); screen.drawFastVLine(MODE_XPOS, MODE_YPOS + 20, 12, BLACK);
    screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 9, 14, RED); screen.drawFastVLine(MODE_XPOS + 1, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 8, 16, RED); screen.drawFastVLine(MODE_XPOS + 2, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 6, 7, RED); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 13, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 20, 6, RED); screen.drawFastVLine(MODE_XPOS + 3, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 5, 5, RED); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 10, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 22, 5, RED); screen.drawFastVLine(MODE_XPOS + 4, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 4, 4, RED); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 8, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 24, 4, RED); screen.drawFastVLine(MODE_XPOS + 5, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 3, 6, RED); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 9, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 25, 4, RED); screen.drawFastVLine(MODE_XPOS + 6, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 3, 7, RED); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 10, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 26, 3, RED); screen.drawFastVLine(MODE_XPOS + 7, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 2, 3, RED); screen.drawPixel(MODE_XPOS + 8, MODE_YPOS + 5, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 6, 5, RED); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 11, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 27, 3, RED); screen.drawFastVLine(MODE_XPOS + 8, MODE_YPOS + 30, 2, BLACK);
    screen.drawPixel(MODE_XPOS + 9, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 1, 4, RED); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 5, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 7, 5, RED); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 12, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 27, 3, RED); screen.drawFastVLine(MODE_XPOS + 9, MODE_YPOS + 30, 2, BLACK);
    screen.drawPixel(MODE_XPOS + 10, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 1, 3, RED); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 4, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 8, 5, RED); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 13, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 10, MODE_YPOS + 28, 3, RED); screen.drawPixel(MODE_XPOS + 10, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 11, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 1, 3, RED); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 4, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 9, 5, RED); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 14, 14, BLACK); screen.drawFastVLine(MODE_XPOS + 11, MODE_YPOS + 28, 3, RED); screen.drawPixel(MODE_XPOS + 11, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 3, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 10, 5, RED); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 15, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 12, MODE_YPOS + 28, 4, RED);
    screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 3, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 11, 5, RED); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 16, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 13, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 3, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 12, 5, RED); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 17, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 14, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 3, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 13, 5, RED); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 18, 11, BLACK); screen.drawFastVLine(MODE_XPOS + 15, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 3, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 14, 5, RED); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 19, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 16, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 3, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 15, 5, RED); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 20, 9, BLACK); screen.drawFastVLine(MODE_XPOS + 17, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 3, 14, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 16, 5, RED); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 21, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 18, MODE_YPOS + 29, 3, RED);
    screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS, 3, RED); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 3, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 17, 5, RED); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 22, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 19, MODE_YPOS + 28, 4, RED);
    screen.drawPixel(MODE_XPOS + 20, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 1, 3, RED); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 4, 14, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 18, 5, RED); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 23, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 20, MODE_YPOS + 28, 3, RED); screen.drawPixel(MODE_XPOS + 20, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 21, MODE_YPOS, BLACK);  screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 1, 3, RED); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 4, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 19, 5, RED); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 24, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 21, MODE_YPOS + 28, 3, RED); screen.drawPixel(MODE_XPOS + 21, MODE_YPOS + 31, BLACK);
    screen.drawPixel(MODE_XPOS + 22, MODE_YPOS, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 1, 4, RED); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 5, 15, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 20, 5, RED); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 25, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 22, MODE_YPOS + 27, 4, RED); screen.drawPixel(MODE_XPOS + 22, MODE_YPOS + 31, BLACK);
    screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS, 2, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 2, 3, RED); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 5, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 21, 6, RED); screen.drawPixel(MODE_XPOS + 23, MODE_YPOS + 26, BLACK); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 27, 3, RED); screen.drawFastVLine(MODE_XPOS + 23, MODE_YPOS + 30, 2, BLACK);
    screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 3, 3, RED); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 6, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 22, 7, RED); screen.drawFastVLine(MODE_XPOS + 24, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS, 3, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 3, 4, RED); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 7, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 23, 6, RED); screen.drawFastVLine(MODE_XPOS + 25, MODE_YPOS + 29, 3, BLACK);
    screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS, 4, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 4, 4, RED); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 8, 16, BLACK); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 24, 4, RED); screen.drawFastVLine(MODE_XPOS + 26, MODE_YPOS + 28, 4, BLACK);
    screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS, 5, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 5, 5, RED); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 10, 13, BLACK); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 22, 5, RED); screen.drawFastVLine(MODE_XPOS + 27, MODE_YPOS + 27, 5, BLACK);
    screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS, 6, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 6, 7, RED); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 13, 7, BLACK); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 19, 7, RED); screen.drawFastVLine(MODE_XPOS + 28, MODE_YPOS + 26, 6, BLACK);
    screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS, 8, BLACK); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 8, 16, RED); screen.drawFastVLine(MODE_XPOS + 29, MODE_YPOS + 24, 8, BLACK);
    screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS, 10, BLACK); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 10, 13, RED); screen.drawFastVLine(MODE_XPOS + 30, MODE_YPOS + 23, 9, BLACK);
    screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS, 12, BLACK); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 12, 8, RED); screen.drawFastVLine(MODE_XPOS + 31, MODE_YPOS + 20, 12, BLACK);
  }
}
void drawWifi()  {
  bool wifiConn = false;
  if (WiFi.status() == WL_CONNECTED)  {wifiConn = true;}
  bool mqttConn = true;
  uint16_t wifiColour;
  uint16_t mqttColour;


  if (wifiConn==true)  {
    wifiColour = BLUE;
    if (mqttConn==true)  {
      mqttColour = VIOLET;
    }
    else  {
      mqttColour = MARS;
    }
  }
  else  {
    wifiColour = MARS;  
    mqttColour = MARS;
  }

  screen.drawFastVLine(WIFI_XPOS, WIFI_YPOS, 24, BLACK); screen.drawFastVLine(WIFI_XPOS, WIFI_YPOS+24, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS, WIFI_YPOS+29, 3, BLACK);
  screen.drawFastVLine(WIFI_XPOS+1, WIFI_YPOS, 23, BLACK); screen.drawFastVLine(WIFI_XPOS+1, WIFI_YPOS+23, 7, wifiColour); screen.drawFastVLine(WIFI_XPOS+1, WIFI_YPOS+30, 2, BLACK);
  screen.drawFastVLine(WIFI_XPOS+2, WIFI_YPOS, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+2, WIFI_YPOS+9, 3, wifiColour); screen.drawFastVLine(WIFI_XPOS+2, WIFI_YPOS+12, 10, BLACK); screen.drawFastVLine(WIFI_XPOS+2, WIFI_YPOS+22, 9, wifiColour); screen.drawPixel(WIFI_XPOS+2, WIFI_YPOS+31, BLACK);
  screen.drawFastVLine(WIFI_XPOS+3, WIFI_YPOS, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+3, WIFI_YPOS+8, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+3, WIFI_YPOS+12, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+3, WIFI_YPOS+21, 11, wifiColour);
  screen.drawPixel(WIFI_XPOS+4, WIFI_YPOS, BLACK); screen.drawFastVLine(WIFI_XPOS+4, WIFI_YPOS+1, 3, wifiColour); screen.drawFastVLine(WIFI_XPOS+4, WIFI_YPOS+4, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+4, WIFI_YPOS+8, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+4, WIFI_YPOS+12, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+4, WIFI_YPOS+21, 11, wifiColour);
  screen.drawPixel(WIFI_XPOS+5, WIFI_YPOS, BLACK); screen.drawFastVLine(WIFI_XPOS+5, WIFI_YPOS+1, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+5, WIFI_YPOS+5, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+5, WIFI_YPOS+9, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+5, WIFI_YPOS+13, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+5, WIFI_YPOS+21, 11, wifiColour);
  screen.drawFastVLine(WIFI_XPOS+6, WIFI_YPOS, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+6, WIFI_YPOS+5, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+6, WIFI_YPOS+9, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+6, WIFI_YPOS+13, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+6, WIFI_YPOS+21, 11, wifiColour);
  screen.drawFastVLine(WIFI_XPOS+7, WIFI_YPOS, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+7, WIFI_YPOS+5, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+7, WIFI_YPOS+9, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+7, WIFI_YPOS+13, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+7, WIFI_YPOS+21, 11, wifiColour);
  screen.drawFastVLine(WIFI_XPOS+8, WIFI_YPOS, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+8, WIFI_YPOS+5, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+8, WIFI_YPOS+10, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+8, WIFI_YPOS+14, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+8, WIFI_YPOS+22, 9, wifiColour); screen.drawPixel(WIFI_XPOS+8, WIFI_YPOS+31, BLACK);
  screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS, 6, wifiColour); screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS+6, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS+10, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS+14, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS+22, 7, wifiColour); screen.drawFastVLine(WIFI_XPOS+9, WIFI_YPOS+30, 2, BLACK);
  screen.drawPixel(WIFI_XPOS+10, WIFI_YPOS, BLACK); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+1, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+6, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+11, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+15, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+24, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+10, WIFI_YPOS+29, 3, BLACK);
  screen.drawPixel(WIFI_XPOS+11, WIFI_YPOS, BLACK); screen.drawFastVLine(WIFI_XPOS+11, WIFI_YPOS+1, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+11, WIFI_YPOS+6, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+11, WIFI_YPOS+11, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+11, WIFI_YPOS+15, 17, BLACK);
  screen.drawPixel(WIFI_XPOS+12, WIFI_YPOS, BLACK); screen.drawFastVLine(WIFI_XPOS+12, WIFI_YPOS+1, 6, wifiColour); screen.drawFastVLine(WIFI_XPOS+12, WIFI_YPOS+7, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+12, WIFI_YPOS+12, 4, wifiColour); screen.drawFastVLine(WIFI_XPOS+12, WIFI_YPOS+16, 16, BLACK);
  screen.drawFastVLine(WIFI_XPOS+13, WIFI_YPOS, 2, BLACK); screen.drawFastVLine(WIFI_XPOS+13, WIFI_YPOS+2, 6, wifiColour); screen.drawFastVLine(WIFI_XPOS+13, WIFI_YPOS+8, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+13, WIFI_YPOS+12, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+13, WIFI_YPOS+17, 15, BLACK);
  screen.drawFastVLine(WIFI_XPOS+14, WIFI_YPOS, 2, BLACK); screen.drawFastVLine(WIFI_XPOS+14, WIFI_YPOS+2, 6, wifiColour); screen.drawFastVLine(WIFI_XPOS+14, WIFI_YPOS+8, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+14, WIFI_YPOS+13, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+14, WIFI_YPOS+18, 14, BLACK);
  screen.drawFastVLine(WIFI_XPOS+15, WIFI_YPOS, 2, BLACK); screen.drawFastVLine(WIFI_XPOS+15, WIFI_YPOS+3, 6, wifiColour); screen.drawFastVLine(WIFI_XPOS+15, WIFI_YPOS+9, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+15, WIFI_YPOS+14, 5, wifiColour); screen.drawFastVLine(WIFI_XPOS+15, WIFI_YPOS+19, 13, BLACK);
  
  screen.drawFastVLine(WIFI_XPOS+16, WIFI_YPOS, 3, BLACK); screen.drawFastVLine(WIFI_XPOS+16, WIFI_YPOS+3, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+16, WIFI_YPOS+9, 10, BLACK); screen.drawFastVLine(WIFI_XPOS+16, WIFI_YPOS+15, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+16, WIFI_YPOS+21, 11, BLACK);
  screen.drawFastVLine(WIFI_XPOS+17, WIFI_YPOS, 4, BLACK); screen.drawFastVLine(WIFI_XPOS+17, WIFI_YPOS+4, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+17, WIFI_YPOS+10, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+17, WIFI_YPOS+16, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+17, WIFI_YPOS+22, 10, BLACK);
  screen.drawFastVLine(WIFI_XPOS+18, WIFI_YPOS, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+18, WIFI_YPOS+5, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+18, WIFI_YPOS+11, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+18, WIFI_YPOS+17, 8, mqttColour); screen.drawFastVLine(WIFI_XPOS+18, WIFI_YPOS+25, 7, BLACK);
  screen.drawFastVLine(WIFI_XPOS+19, WIFI_YPOS, 5, BLACK); screen.drawFastVLine(WIFI_XPOS+19, WIFI_YPOS+5, 7, mqttColour); screen.drawFastVLine(WIFI_XPOS+19, WIFI_YPOS+12, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+19, WIFI_YPOS+18, 10, mqttColour); screen.drawFastVLine(WIFI_XPOS+19, WIFI_YPOS+28, 4, BLACK);
  screen.drawFastVLine(WIFI_XPOS+20, WIFI_YPOS, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+20, WIFI_YPOS+6, 7, mqttColour); screen.drawFastVLine(WIFI_XPOS+20, WIFI_YPOS+13, 7, BLACK); screen.drawFastVLine(WIFI_XPOS+20, WIFI_YPOS+20, 10, mqttColour); screen.drawFastVLine(WIFI_XPOS+20, WIFI_YPOS+30, 2, BLACK);
  screen.drawPixel(WIFI_XPOS+21, WIFI_YPOS, mqttColour); screen.drawFastVLine(WIFI_XPOS+21, WIFI_YPOS+1, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+21, WIFI_YPOS+7, 7, mqttColour); screen.drawFastVLine(WIFI_XPOS+21, WIFI_YPOS+14, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+21, WIFI_YPOS+22, 8, mqttColour); screen.drawFastVLine(WIFI_XPOS+21, WIFI_YPOS+30, 2, BLACK);
  screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS, 2, mqttColour); screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS+2, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS+8, 7, mqttColour); screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS+15, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS+24, 5, mqttColour); screen.drawFastVLine(WIFI_XPOS+22, WIFI_YPOS+29, 3, BLACK);
  screen.drawFastVLine(WIFI_XPOS+23, WIFI_YPOS, 3, mqttColour); screen.drawFastVLine(WIFI_XPOS+23, WIFI_YPOS+3, 6, BLACK); screen.drawFastVLine(WIFI_XPOS+23, WIFI_YPOS+9, 8, mqttColour); screen.drawFastVLine(WIFI_XPOS+23, WIFI_YPOS+17, 15, BLACK);
  screen.drawFastVLine(WIFI_XPOS+24, WIFI_YPOS, 3, mqttColour); screen.drawFastVLine(WIFI_XPOS+24, WIFI_YPOS+3, 7, BLACK); screen.drawFastVLine(WIFI_XPOS+24, WIFI_YPOS+10, 9, mqttColour); screen.drawFastVLine(WIFI_XPOS+24, WIFI_YPOS+19, 13, BLACK);
  screen.drawFastVLine(WIFI_XPOS+25, WIFI_YPOS, 4, mqttColour); screen.drawFastVLine(WIFI_XPOS+25, WIFI_YPOS+4, 7, BLACK); screen.drawFastVLine(WIFI_XPOS+25, WIFI_YPOS+11, 10, mqttColour); screen.drawFastVLine(WIFI_XPOS+25, WIFI_YPOS+21, 11, BLACK);
  screen.drawFastVLine(WIFI_XPOS+26, WIFI_YPOS, 5, mqttColour); screen.drawFastVLine(WIFI_XPOS+26, WIFI_YPOS+5, 7, BLACK); screen.drawFastVLine(WIFI_XPOS+26, WIFI_YPOS+12, 11, mqttColour); screen.drawFastVLine(WIFI_XPOS+26, WIFI_YPOS+23, 9, BLACK);
  screen.drawFastVLine(WIFI_XPOS+27, WIFI_YPOS, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+27, WIFI_YPOS+6, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+27, WIFI_YPOS+14, 13, mqttColour); screen.drawFastVLine(WIFI_XPOS+27, WIFI_YPOS+27, 5, BLACK);
  screen.drawFastVLine(WIFI_XPOS+28, WIFI_YPOS, 7, mqttColour); screen.drawFastVLine(WIFI_XPOS+28, WIFI_YPOS+7, 8, BLACK); screen.drawFastVLine(WIFI_XPOS+28, WIFI_YPOS+15, 14, mqttColour); screen.drawFastVLine(WIFI_XPOS+28, WIFI_YPOS+29, 3, BLACK);
  screen.drawFastVLine(WIFI_XPOS+29, WIFI_YPOS, 8, mqttColour); screen.drawFastVLine(WIFI_XPOS+29, WIFI_YPOS+8, 9, BLACK); screen.drawFastVLine(WIFI_XPOS+29, WIFI_YPOS+17, 12, mqttColour); screen.drawFastVLine(WIFI_XPOS+29, WIFI_YPOS+29, 3, BLACK);
  screen.drawFastVLine(WIFI_XPOS+30, WIFI_YPOS, 9, mqttColour); screen.drawFastVLine(WIFI_XPOS+30, WIFI_YPOS+9, 10, BLACK); screen.drawFastVLine(WIFI_XPOS+30, WIFI_YPOS+19, 10, mqttColour); screen.drawFastVLine(WIFI_XPOS+30, WIFI_YPOS+29, 3, BLACK);
  screen.drawFastVLine(WIFI_XPOS+31, WIFI_YPOS, 11, mqttColour); screen.drawFastVLine(WIFI_XPOS+31, WIFI_YPOS+11, 11, BLACK); screen.drawFastVLine(WIFI_XPOS+31, WIFI_YPOS+22, 6, mqttColour); screen.drawFastVLine(WIFI_XPOS+31, WIFI_YPOS+28, 4, BLACK);
}

void settingsIcon(char icon[5]) {
  if (strcmp(icon, "Reg") == 0)  {
    #ifdef DISPDEBUG
    Serial.println("Drawing settings icon");
    #endif
    screen.drawFastVLine(SET_XPOS, SET_YPOS, 14, BLACK); screen.drawFastVLine(SET_XPOS, SET_YPOS+14, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS, SET_YPOS+18, 14, BLACK);
    screen.drawFastVLine(SET_XPOS+1, SET_YPOS, 13, BLACK); screen.drawFastVLine(SET_XPOS+1, SET_YPOS+13, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+1, SET_YPOS+19, 13, BLACK);
    screen.drawFastVLine(SET_XPOS+2, SET_YPOS, 12, BLACK); screen.drawFastVLine(SET_XPOS+2, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+2, SET_YPOS+20, 12, BLACK);
    screen.drawFastVLine(SET_XPOS+3, SET_YPOS, 6, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+6, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+8, 4, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+20, 4, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+24, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+26, 6, BLACK);
    screen.drawFastVLine(SET_XPOS+4, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+5, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+9, 2, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+11, 10, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+21, 2, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+23, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+5, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+5, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+5, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+6, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+6, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+6, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+7, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+7, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+7, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+8, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+8, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+8, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+9, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+5, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+13, 6, BLACK); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+19, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+10, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+5, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+12, 8, BLACK); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+20, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+11, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+5, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+11, 10, BLACK); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+21, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+12, SET_YPOS, 2, BLACK); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+2, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+10, 12, BLACK); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+22, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+30, 2, BLACK);
    screen.drawPixel(SET_XPOS+13, SET_YPOS, BLACK); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+1, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+23, 8, GREY_BLUE); screen.drawPixel(SET_XPOS+13, SET_YPOS+31, BLACK);
    screen.drawFastVLine(SET_XPOS+14, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+14, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+14, SET_YPOS+23, 9, GREY_BLUE);
    screen.drawFastVLine(SET_XPOS+15, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+23, 9, GREY_BLUE);
    screen.drawFastVLine(SET_XPOS+16, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+16, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+16, SET_YPOS+23, 9, GREY_BLUE);
    screen.drawFastVLine(SET_XPOS+17, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+23, 9, GREY_BLUE);
    screen.drawPixel(SET_XPOS+18, SET_YPOS, BLACK); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+1, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+9, 14, BLACK); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+23, 8, GREY_BLUE); screen.drawPixel(SET_XPOS+18, SET_YPOS+31, BLACK);
    screen.drawFastVLine(SET_XPOS+19, SET_YPOS, 2, BLACK); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+2, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+10, 12, BLACK); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+22, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+30, 2, BLACK);
    screen.drawFastVLine(SET_XPOS+20, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+5, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+11, 10, BLACK); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+21, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+21, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+5, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+12, 8, BLACK); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+20, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+22, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+5, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+13, 6, BLACK); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+19, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+23, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+24, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+25, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+26, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+27, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+5, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+9, 2, BLACK); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+11, 10, GREY_BLUE); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+21, 2, BLACK); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+23, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+28, SET_YPOS, 6, BLACK); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+6, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+28, 4, BLACK); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+20, 4, BLACK); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+24, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+26, 6, BLACK);
    screen.drawFastVLine(SET_XPOS+29, SET_YPOS, 12, BLACK); screen.drawFastVLine(SET_XPOS+29, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+29, SET_YPOS+20, 12, BLACK);
    screen.drawFastVLine(SET_XPOS+30, SET_YPOS, 13, BLACK); screen.drawFastVLine(SET_XPOS+30, SET_YPOS+13, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+30, SET_YPOS+19, 13, BLACK);
    screen.drawFastVLine(SET_XPOS+31, SET_YPOS, 14, BLACK); screen.drawFastVLine(SET_XPOS+31, SET_YPOS+14, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+31, SET_YPOS+18, 14, BLACK);
  }
  if (strcmp(icon, "Save") == 0)  {
    screen.drawFastVLine(SET_XPOS, SET_YPOS, 14, BLACK); screen.drawFastVLine(SET_XPOS, SET_YPOS+14, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS, SET_YPOS+18, 14, BLACK);
    screen.drawFastVLine(SET_XPOS+1, SET_YPOS, 13, BLACK); screen.drawFastVLine(SET_XPOS+1, SET_YPOS+13, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+1, SET_YPOS+19, 13, BLACK);
    screen.drawFastVLine(SET_XPOS+2, SET_YPOS, 12, BLACK); screen.drawFastVLine(SET_XPOS+2, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+2, SET_YPOS+20, 12, BLACK);
    screen.drawFastVLine(SET_XPOS+3, SET_YPOS, 6, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+6, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+8, 4, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+12, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+20, 4, BLACK); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+24, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+3, SET_YPOS+26, 6, BLACK);
    screen.drawFastVLine(SET_XPOS+4, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+5, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+9, 2, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+11, 10, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+21, 2, BLACK); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+23, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+4, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+5, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+5, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+5, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+6, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+6, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+6, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+7, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+7, SET_YPOS+3, 26, GREY_BLUE); screen.drawFastVLine(SET_XPOS+7, SET_YPOS+29, 3, BLACK);
    screen.drawFastVLine(SET_XPOS+8, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+8, SET_YPOS+4, 24, GREY_BLUE); screen.drawFastVLine(SET_XPOS+8, SET_YPOS+28, 4, BLACK);
    screen.drawFastVLine(SET_XPOS+9, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+5, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+13, 6, BLACK); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+19, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+9, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+10, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+5, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+12, 8, BLACK); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+20, 7, GREY_BLUE); screen.drawFastVLine(SET_XPOS+10, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+11, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+5, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+11, 10, BLACK); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+21, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+11, SET_YPOS+27, 5, BLACK);
    screen.drawFastVLine(SET_XPOS+12, SET_YPOS, 2, BLACK); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+2, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+10, 12, BLACK); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+22, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+12, SET_YPOS+30, 2, BLACK);
    screen.drawPixel(SET_XPOS+13, SET_YPOS, GREEN); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+1, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+9, 5, BLACK); screen.drawFastVLine(SET_XPOS+13, SET_YPOS+14, 17, PEACH); screen.drawPixel(SET_XPOS+13, SET_YPOS+31, BLACK);
    screen.drawFastVLine(SET_XPOS+14, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+14, SET_YPOS+9, 4, BLACK); screen.drawFastVLine(SET_XPOS+14, SET_YPOS+13, 19, PEACH);
    screen.drawFastVLine(SET_XPOS+15, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+9, 4, BLACK); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+13, 10, PEACH); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+22, 7, BLACK); screen.drawFastVLine(SET_XPOS+15, SET_YPOS+30, 2, PEACH);
    screen.drawFastVLine(SET_XPOS+16, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+16, SET_YPOS+9, 4, BLACK); screen.drawFastVLine(SET_XPOS+16, SET_YPOS+13, 9, PEACH); screen.drawFastVLine(SET_XPOS+16, SET_YPOS+22, 9, BLACK); screen.drawPixel(SET_XPOS+16, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+17, SET_YPOS, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+9, 4, BLACK); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+13, 9, PEACH); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+17, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+17, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+17, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+17, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+17, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+17, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+17, SET_YPOS+31, PEACH);
    screen.drawPixel(SET_XPOS+18, SET_YPOS, BLACK); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+1, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+9, 4, BLACK); screen.drawPixel(SET_XPOS+18, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+18, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+18, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+18, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+18, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+18, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+18, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+18, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+19, SET_YPOS, 2, BLACK); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+2, 8, GREY_BLUE); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+10, 3, BLACK); screen.drawPixel(SET_XPOS+19, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+19, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+19, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+19, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+19, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+19, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+19, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+19, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+20, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+5, 6, GREY_BLUE); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+11, 2, BLACK); screen.drawPixel(SET_XPOS+20, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+20, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+20, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+20, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+20, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+20, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+20, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+20, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+21, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+5, 7, GREY_BLUE); screen.drawPixel(SET_XPOS+21, SET_YPOS+12, BLACK); screen.drawPixel(SET_XPOS+21, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+21, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+21, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+21, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+21, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+21, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+21, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+21, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+22, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+5, 8, GREY_BLUE);screen.drawPixel(SET_XPOS+22, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+22, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+22, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+22, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+22, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+22, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+22, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+22, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+23, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+4, 9, GREY_BLUE); screen.drawPixel(SET_XPOS+23, SET_YPOS+13, PEACH); screen.drawPixel(SET_XPOS+23, SET_YPOS+14, BLACK); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+15, 4, PEACH); screen.drawPixel(SET_XPOS+23, SET_YPOS+19, BLACK); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+23, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+23, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+23, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+23, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+23, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+23, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+23, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+24, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+3, 10, GREY_BLUE); screen.drawPixel(SET_XPOS+24, SET_YPOS+13, PEACH); screen.drawPixel(SET_XPOS+24, SET_YPOS+14, BLACK); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+15, 4, PEACH); screen.drawPixel(SET_XPOS+24, SET_YPOS+19, BLACK); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+24, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+24, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+24, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+24, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+24, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+24, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+24, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+25, SET_YPOS, 3, BLACK); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+3, 10, GREY_BLUE); screen.drawPixel(SET_XPOS+25, SET_YPOS+13, PEACH); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+14, 6, BLACK); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+20, 2, PEACH); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+25, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+25, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+25, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+25, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+25, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+25, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+25, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+26, SET_YPOS, 4, BLACK); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+4, 9, GREY_BLUE); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+13, 9, PEACH); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+26, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+26, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+26, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+26, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+26, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+26, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+26, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+27, SET_YPOS, 5, BLACK); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+5, 4, GREY_BLUE); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+9, 2, BLACK); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+11, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+13, 9, PEACH); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+22, 2, BLACK); screen.drawPixel(SET_XPOS+27, SET_YPOS+24, PEACH); screen.drawPixel(SET_XPOS+27, SET_YPOS+25, BLACK); screen.drawPixel(SET_XPOS+27, SET_YPOS+26, PEACH); screen.drawPixel(SET_XPOS+27, SET_YPOS+27, BLACK); screen.drawPixel(SET_XPOS+27, SET_YPOS+28, PEACH); screen.drawFastVLine(SET_XPOS+27, SET_YPOS+29, 2, BLACK); screen.drawPixel(SET_XPOS+27, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+28, SET_YPOS, 6, BLACK); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+6, 2, GREY_BLUE); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+8, 4, BLACK); screen.drawPixel(SET_XPOS+28, SET_YPOS+12, GREY_BLUE); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+13, 9, PEACH); screen.drawFastVLine(SET_XPOS+28, SET_YPOS+22, 9, BLACK); screen.drawPixel(SET_XPOS+28, SET_YPOS+31, PEACH);
    screen.drawFastVLine(SET_XPOS+29, SET_YPOS, 12, BLACK); screen.drawPixel(SET_XPOS+29, SET_YPOS+12, GREY_BLUE); screen.drawFastVLine(SET_XPOS+29, SET_YPOS+13, 10, PEACH); screen.drawFastVLine(SET_XPOS+29, SET_YPOS+23, 7, BLACK); screen.drawFastVLine(SET_XPOS+29, SET_YPOS+30, 2, PEACH);
    screen.drawFastVLine(SET_XPOS+30, SET_YPOS, 13, BLACK); screen.drawFastVLine(SET_XPOS+30, SET_YPOS+13, 19, PEACH);
    screen.drawFastVLine(SET_XPOS+31, SET_YPOS, 14, BLACK); screen.drawFastVLine(SET_XPOS+31, SET_YPOS+14, 17, PEACH); screen.drawPixel(SET_XPOS+13, SET_YPOS+31, BLACK);
    
  }
}

void displayCurrTemp() {
  #ifdef PROGTEXT
  Serial.print("Displaying current temperature - ");
  Serial.print(tempCurr, 1);
  Serial.println("°C");
  #endif
  // Serial.print("displayCurrTemp() running on core "); Serial.println(xPortGetCoreID());
  drawBigNum(tempCurr, TEMP_XPOS, TEMP_YPOS, ICE_BLUE);
}

void displaySetTemp() {
  #ifdef PROGTEXT
  Serial.print("Displaying set temperature - ");
  Serial.print(settings.tempSet, 0);
  Serial.println("°C");
  #endif
  // Serial.print("displaySetTemp() running on core "); Serial.println(xPortGetCoreID());
  drawSmNum(settings.tempSet, TEMPSET_XPOS, TEMPSET_YPOS, ICE_BLUE);
}

void ScreenInit() {
  Serial.print("Initializing ILI3941 display at ");
  Serial.print(SCREEN_WIDTH);
  Serial.print("x");
  Serial.println(SCREEN_HEIGHT);
  screen.begin();
  screen.setRotation(1);
  screen.cp437(true);
  screen.fillScreen(BLACK);

  drawTopBar("Booting");
  drawBottomBar();
  for (char count = 1; count <= settings.brightness; count++) {
    setScreenBrightness(count);
    delay(100);
  }
  screen.setCursor(0,20);
}

void RunScreen() {
  drawTopBar("Main");
  modeIcon(opMode);
  drawWifi();
  settingsIcon("Reg");
  displayCurrTemp();
  displaySetTemp();
  drawHistoryGraph();
}

void SettingsScreen() {

  drawTopBar("Set");
  settingsIcon("Save");
}

void drawTouchPoint(int pointX, int pointY, int size = 5) {
  static int oldX;
  static int oldY;

  screen.fillCircle(oldX, oldY, size + 1, BLACK);
  screen.fillCircle(pointX, pointY, size, VIOLET_CREME);

  oldX = pointX;
  oldY = pointY;
}

void checkTouch() {
  TSPoint p = ts.getPoint();
  int debounceTime = 100;

  if (p.z > 0) {
    int mapX = map(p.x, calibrations.ts_minX, calibrations.ts_maxX, 0, SCREEN_WIDTH);
    int mapY = map(p.y, calibrations.ts_minY, calibrations.ts_maxY, 0, SCREEN_HEIGHT);

    #ifdef PROGTEXT
    Serial.print("Mapped point: (");
    Serial.print(mapX);
    Serial.print(",");
    Serial.print(mapY);
    Serial.println(")");
    drawTouchPoint(mapX, mapY);
    #endif

    if ((mapY > 225) && (mapY < 250)) {  //100-130, 35-50
      if ((mapX > 250) && (mapX < 300)) {
        Serial.print("Change to next operation mode: ");  // Fan, Cool, Off, Heat,
        if (strcmp(opMode, "Heat") == 0) {
          strcpy(opMode, "Fan");
        }
        else if (strcmp(opMode, "Fan") == 0) {
          strcpy(opMode, "Cool");
        }
        else if (strcmp(opMode, "Cool") == 0) {
          strcpy(opMode, "Off");
        }
        else if (strcmp(opMode, "Off") == 0) {
          strcpy(opMode, "Heat");
        }
        Serial.println(opMode);
        modeIcon(opMode);
      }
      if ((mapX > 30) && (mapX < 90)) {  //260-300, 35-50
        Serial.println("Change to settings mode");
      }
      Serial.println("\n");
    }
    do {
      delay(debounceTime);
      p = ts.getPoint();
      Serial.print("Waiting for touch to release - Pressure read: "); Serial.println(p.z);
    } while (p.z > 0);
  }
  // else  {Serial.println("No touch");}
}

void TouchCal(int calTime) {
  unsigned long calStart = millis();
  unsigned long calEnd = millis() + (calTime * 1000);
  int minX = 1024;
  int maxX = 0;
  int minY = 1024;
  int maxY = 0;
  int mapX;
  int mapY;
  TSPoint p = ts.getPoint();

  screen.fillScreen(BLACK);

  while (millis() < calEnd) {
    // we have some minimum pressure we consider 'valid' pressure of 0 means no pressing!
    if (p.z != 0) {
      if (p.x < minX) { minX = p.x; }
      if (p.x > maxX) { maxX = p.x; }
      if (p.y < minY) { minY = p.y; }
      if (p.y > maxY) { maxY = p.y; }
      mapX = map(p.x, minX, maxX, 0, SCREEN_WIDTH);
      mapY = map(p.y, minY, maxY, 0, SCREEN_HEIGHT);
      Serial.print("Pressure = ");
      Serial.print(p.z);
      Serial.print("     X = ");
      Serial.print(p.x);
      Serial.print("     Y = ");
      Serial.println(p.y);
      Serial.print("Ranges - X: ");
      Serial.print(minX);
      Serial.print("-");
      Serial.print(maxX);
      Serial.print("     Y: ");
      Serial.print(minY);
      Serial.print("-");
      Serial.print(maxY);
      Serial.print("Mapped point: (");
      Serial.print(mapX);
      Serial.print(",");
      Serial.print(mapY);
      Serial.println(")\n");
      digitalWrite(pinLED, 1);
      drawTouchPoint(mapX, mapY, 5);
      delay(100);
    }
    calibrations.ts_minX = minX;
    calibrations.ts_maxX = maxX;
    calibrations.ts_minY = minY;
    calibrations.ts_maxY = maxY;
    digitalWrite(pinLED, 0);
  }
  RunScreen();
}