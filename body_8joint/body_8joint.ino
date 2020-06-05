/***********************************************************
  项目名：8自由度纸片人通用控制框架
  作者：BlackBox114
  当前版本描述：
  开发板：NodeMcu(ESP-12E)
  修改密码为自己的wifiSSID和PSWD，打开手机连接826热点，访问相应IP即可访问控制页面
  控制页面可以同时控制八个舵机的运作，可以记录和储存动作，调整舵机运动速度
  修改人：BlackBox114
  修改时间：2020.06.05
  修改内容：增加直接使用网页控制舵机的功能
  接线：待更新
  /***********************************************************/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//----------------------------------------Include the Servo Library
#include <Servo.h>

#include "PageIndex.h"; //--> 网页储存在这里

#define ServoPort D4   //--> 定义舵机接口

//----------------------------------------AP点的ssid和pswd
const char* ssid = "PaperPuppetJoint8";
const char* password = "11111111";
//----------------------------------------

Servo myservo;  //--> 创建舵机对象

ESP8266WebServer server(80);  //--> 端口为80

//----------------------------------------这部分函数在你访问8266
/*
  出现报错：Exception (3):
  epc1=0x4000bf64 epc2=0x00000000 epc3=0x4000473f excvaddr=0x4023d571 depc=0x00000000

  >>>stack>>>

  void handleRoot() {
  String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", s); //Send web page
  }
  已修复
*/
void handleRoot() {
  //String s = MAIN_page; //Read HTML contents
  server.send(200, "text/html", MAIN_page); //Send web page
}

//----------------------------------------

//----------------------------------------舵机控制程序
void handleServo() {
  String POS = server.arg("servoPOS");
  int pos = POS.toInt();
  myservo.write(pos);   //--> Move the servo motor according to the POS value
  delay(15);
  Serial.print("Servo Angle:");
  Serial.println(pos);
  server.send(200, "text/plane", "");
}
//----------------------------------------
//----------------------------------------初始化----------------------------------------
void setup() {
  Serial.begin(115200);
  delay(500);

  myservo.attach(ServoPort); //--> attaches the servo on D1 to the servo object


  WiFi.softAP(ssid, password);  //--> Start Making ESP8266 NodeMCU as an access point

  IPAddress apip = WiFi.softAPIP(); //--> Get the IP server
  Serial.print("Connect your wifi laptop/mobile phone to this NodeMCU Access Point : ");
  Serial.println(ssid);
  Serial.print("Visit this IP : ");
  Serial.print(apip); //--> Prints the IP address of the server to be visited
  Serial.println(" in your browser.");
  //----------------------------------------

  //----------------------------------------初始化网络服务器
  server.on("/", handleRoot); //--> Routine to handle at root location. This is to display web page.
  server.on("/setPOS", handleServo); //--> Sets servo position from Web request
  server.begin();
  Serial.println("HTTP server started");
}
//------------------------------------------------------------------------------------
//----------------------------------------主循环----------------------------------------
void loop() {
  server.handleClient();
}
//------------------------------------------------------------------------------------
