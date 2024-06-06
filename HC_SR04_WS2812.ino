#include <hcsr04.h>
#include <FastLED.h>
#include "SSD1306Wire.h"  

//hc-sr04端口初始化
#define TRIG_PIN 12
#define ECHO_PIN 13
HCSR04 hcsr04(TRIG_PIN, ECHO_PIN, 20, 4000);

//led端口初始化
#define NUM_LEDS 12//LED数量
#define LED_PIN 3//定义io口
CRGB leds[NUM_LEDS];//定义led数组

//ssd1306端口初始化
SSD1306Wire display(0x3c, 4, 5);//SDA-->4;SCL-->5

void setup() 
{
  display.init();//OLED初始化
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);//设置字体大小
  FastLED.addLeds<WS2812, LED_PIN, RGB>(leds, NUM_LEDS);//ssd1306初始化
}

void led(int a)//led颜色
{
    for(int i=0;i<12;i++)
    {
      if(a==1){leds[i] = CRGB::Green;}
      else if(a==2){leds[i] = CRGB::Yellow;}
      else if(a==3){leds[i] = CRGB::Red;}
      FastLED.show();
      delay(100);
    }
}

void ssd_1306()//随距离变色
{
  if(hcsr04.distanceInMillimeters()<70) //2-7CM
  {
    led(1);//红
  }
  else if(hcsr04.distanceInMillimeters()>=120) //12-17CM
  {
    led(3);//绿
  }
  else //7-12CM
  {
    led(2);//黄
  }
}

void loop() 
{
  ssd_1306();
  display.clear();
  display.drawString(0, 20, "distance:");//从开头0开始，在第20行显示
  display.drawString(0, 40,String(hcsr04.distanceInMillimeters()));
  display.display();
  delay(250);  
}
