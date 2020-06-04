# PPCF-PaperPuppetControlFramework
Universal control framework about paper puppets. In addition, you can set the speed of a move. The frame can drive up to eight servos for movement. Servos can be used to drive joints, as well as eye and ear movements. In the future, a 16-servo version will be developed to achieve richer actions

### Hardware
|mcu|servo|power|connect|
|----|----|----|----|
|ESP8266(NodeMcu)/Atmega328P|MG90S/Motor 19500KV|MP1584|2.4Gwifi/BLE4.0|

### Code on mcu
Working on it  :)

### Structure
Up to 8 servos moving asynchronously (because it uses interrupts)，we can only turn up to 8 joints. The test version fixes the position of the servo to test the feasibility

<div align="center"><img width="100%" src="imgs/joint.png"> </div>

### App

Working on it  :)

### Library

[VarSpeedServo](https://github.com/netlabtoolkit/VarSpeedServo)











