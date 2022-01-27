//this code is modified for more performance. and as of feburary 2022 it will begin to have code that will speed it up.

1st is a cos/sin rewrite of lut which takes about 200 bytes of code memory and is slow to read
const unsigned int lut[] PROGMEM = {         // 0 to 90 degrees fixed point COSINE look up table
  16384, 16381, 16374, 16361, 16344, 16321, 16294, 16261, 16224, 16182, 16135, 16082, 16025, 15964, 15897, 15825, 15749, 15668, 15582, 15491, 15395, 15295, 15190, 15081, 14967, 14848, 14725, 14598, 14466, 14329, 14188, 14043, 13894, 13740, 13582, 13420, 13254, 13084, 12910, 12732, 12550, 12365, 12175, 11982, 11785, 11585, 11381, 11173, 10963, 10748, 10531, 10310, 10086, 9860, 9630, 9397, 9161, 8923, 8682, 8438, 8191, 7943, 7691, 7438, 7182, 6924, 6663, 6401, 6137, 5871, 5603, 5334, 5062, 4790, 4516, 4240, 3963, 3685, 3406, 3126, 2845, 2563, 2280, 1996, 1712, 1427, 1142, 857, 571, 285, 0
};
and replace wit this which is as fast, but takes a lot less of eeprom and only 8 bytes max of ram for processes.ir it is as fast as method above maybe 2x faster
uint32_t LUT(uint8_t a){ uint16_t tempa=a ;// 1,2,4,8,16,32,64,//this methid saves memory and is as fast or faster than progmem read and custom multiply
//sudo multiply by adding more efficien that arduino multiplier maybe? because 2 bytes wide, no sign and only needs to do numbers up to 90!
//quick multiply because does not need to deal with signs, or numbers above 90!
if (a & 0b01000000){tempa=tempa<<6;};uint16_t accumulator=tempa;tempa=a;
if (a & 0b00100000){tempa=tempa<<5;};accumulator+=tempa;tempa=a;
if (a & 0b00010000){tempa=tempa<<4;};accumulator+=tempa;tempa=a;
if (a & 0b00001000){tempa=tempa<<3;};accumulator+=tempa;tempa=a;
if (a & 0b00000100){tempa=tempa<<2;};accumulator+=tempa;tempa=a;
if (a & 0b00000010){tempa=tempa<<1;};accumulator+=tempa;tempa=a;
if (a & 0b00000001){tempa+=a;}else{tempa=0;}
accumulator+=tempa;
return (16384-(accumulator<<1)+1024-(accumulator>>5));}//originla below

# ATmega328 Tiny 3D Engine (Arduino UNO)
 
#### 3D model viewer made for the ATmega328 and Sainsmart 1.8" TFT screen (ST7735)

This is a tiny 3D engine made for the ATMEGA328 and a Sainsmart 1.8" TFT screen (ST7735).
It uses the amazingly fast Adafruit GFX library fork by XarkLabs: [github.com/XarkLabs](https://github.com/XarkLabs)

You can use the python script stl2h.py to convert STL models into header files and automatically import your meshes, just include the file and comment other mesh headers.

See stl2h.py help (./stl2h -h) for usage description.

```
Usage: ./stl2h.py -i <inputfile> -o <outputfile>
Convert a 3D mesh saved as STL format (ASCII) to header for Tiny 3D Engine.

  -i, --inputfile       3D mesh in STL file format
  -o, --outputfile      output filename of converted data
  -s, --scale           scale ratio (default 1.0)
  -n, --normals         save face normals
  -y, --yes             answer yes to all requests
  -v, --verbose         verbose output
```

Developed and tested with an Arduino UNO and a Sainsmart 1.8" TFT screen.

## Features:
* matrices for mesh transformations
* fixed point to avoid using floats
* 90 degrees fixed point look up table for sin/cos
* backface culling using shoelace algorithm
* flat colors (-unfinished/experimental/not fast enough-)
* rotate the mesh with a 3 axis accelerometer (ADXL335)
* rotate the mesh with a joystick thumb
* push button on digital PIN 2 to change the render type.

This is a project for the ATmega328 and ST7735, source will certainly need some tweaking to run on other components.

## Not implemented:
* clipping
* view/projection matrices (projection is done on world matrix directly)
* hidden surface removal

## Dependencies:
* [XarkLabs PDQ_GFX_Libs](https://github.com/XarkLabs/PDQ_GFX_Libs)

## Video:
[![Preview of Tiny 3D Engine on YouTube](http://img.youtube.com/vi/8nZam2jpIqw/0.jpg)](https://youtu.be/8nZam2jpIqw)

## Screenshot:
![Screenshot](https://raw.githubusercontent.com/mrt-prodz/ATmega328-Tiny-3D-Engine/master/screenshot.jpg)

## References:
[Wiring](http://www.tweaking4all.com/hardware/arduino/sainsmart-arduino-color-display)

[Game Loop](http://www.koonsolo.com/news/dewitters-gameloop)

[Peter Collingridge 3D graphics tutorial](http://petercollingridge.appspot.com/3D-tutorial)

[J-Snake Fixed Point Arithmetic](http://forums.tigsource.com/index.php?topic=35880.0)

[Math Open References](http://www.mathopenref.com/coordpolygonarea.html)

[World, View and Projection Transformation Matrices](http://www.codinglabs.net/article_world_view_projection_matrix.aspx)
