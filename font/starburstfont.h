/*
 * starburstfont.h - used to talk to the htk1633 chip to do things like turn on LEDs or scan keys
 * Copyright:  Slash/Byte
 * License: GPLv3
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License version 3 as
    published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * 	.▄▄ · ▄▄▌   ▄▄▄· .▄▄ ·  ▄ .▄▄▄▄▄·  ▄· ▄▌▄▄▄▄▄▄▄▄ .
 *  ▐█ ▀. ██•  ▐█ ▀█ ▐█ ▀. ██▪▐█▐█ ▀█▪▐█▪██▌•██  ▀▄.▀·
 *  ▄▀▀▀█▄██▪  ▄█▀▀█ ▄▀▀▀█▄██▀▐█▐█▀▀█▄▐█▌▐█▪ ▐█.▪▐▀▀▪▄
 *  ▐█▄▪▐█▐█▌▐▌▐█ ▪▐▌▐█▄▪▐███▌▐▀██▄▪▐█ ▐█▀·. ▐█▌·▐█▄▄▌
 *   ▀▀▀▀ .▀▀▀  ▀  ▀  ▀▀▀▀ ▀▀▀ ··▀▀▀▀   ▀ •  ▀▀▀  ▀▀▀
 *                                         12-07-2018
 * Special function extension for use with
 * Chess Computer
 *
 * font found at https://github.com/adafruit/Adafruit_LED_Backpack/blob/master/Adafruit_LEDBackpack.cpp
 * lines 53-184, thanks adafruit!
 *
 */

//adafruit remap key
//bit  0 = 0
//bit  1 = 1
//bit  2 = 2
//bit  3 = 3
//bit  4 = 4
//bit  5 = 5
//bit  6 = 9
//bit  7 = 10
//bit  8 = 7
//bit  9 = 13
//bit 10 = 12
//bit 11 = 11
//bit 12 = 6
//bit 13 = 8
//bit 14 = 14
//bit 15 = 15
 
#ifndef starburstfont_h
#define starburstfont_h

extern const uint16_t alphafonttable[] =
{
0b0000000000000001,   //0              
0b0000000000000010,   //1
0b0000000000000100,   //2
0b0000000000001000,   //3              
0b0000000000010000,   //4              
0b0000000000100000,   //5              
0b0001000000000000,   //6              
0b0000000100000000,   //7              
0b0010000000000000,   //8              
0b0000000001000000,   //9              
0b0000000010000000,   //10             
0b0000100000000000,   //11             
0b0000010000000000,   //12             
0b0000001000000000,   //13             
0b0100000000000000,   //14             
0b1000000000000000,   //15             
0b0000000000000000,   //16             
0b0000000000000000,   //17             
0b0000000000000000,   //18             
0b0000000000000000,   //19             
0b0000000000000000,   //20             
0b0000000000000000,   //21             
0b0000000000000000,   //22             
0b0000000000000000,   //23             
0b0001010101001001,   //24             
0b0011010110000000,   //25             
0b0001010101111001,   //26             
0b0001000100100011,   //27             
0b0010000010110000,   //28             
0b0001010101001000,   //29             
0b0000111001000000,   //30             
0b0010010011000000,   //31             
0b0000000000000000,   //  (ascii)      
0b0000000000000110,   //! (ascii)      
0b0000000001100000,   //" (ascii)      
0b0001010101001110,   //# (ascii)      
0b0001010101101101,   //$ (ascii)      
0b0000100010100100,   //% (ascii)      
0b0011001001011101,   //& (ascii)      
0b0000000010000000,   //' (ascii)      
0b0000001010000000,   //( (ascii)      
0b0010100000000000,   //) (ascii)      
0b0011111111000000,   //* (ascii)      
0b0001010101000000,   //+ (ascii)      
0b0000100000000000,   //, (ascii)      
0b0001000100000000,   //- (ascii)      
0b0000000000000000,   //. (ascii)      
0b0000100010000000,   /// (ascii)      
0b0000100010111111,   //0 (ascii)      
0b0000000000000110,   //1 (ascii)      
0b0001000100011011,   //2 (ascii)      
0b0000000100001111,   //3 (ascii)      
0b0001000100100110,   //4 (ascii)      
0b0001001000101001,   //5 (ascii)      
0b0001000100111101,   //6 (ascii)      
0b0000000000000111,   //7 (ascii)      
0b0001000100111111,   //8 (ascii)      
0b0001000100101111,   //9 (ascii)      
0b0000010001000000,   //: (ascii)      
0b0000100001000000,   //; (ascii)      
0b0000001010000000,   //< (ascii)      
0b0001000100001000,   //= (ascii)      
0b0010100000000000,   //> (ascii)      
0b0000010100000011,   //? (ascii)      
0b0000000101111011,   //@ (ascii)      
0b0001000100110111,   //A (ascii)      
0b0000010101001111,   //B (ascii)      
0b0000000000111001,   //C (ascii)      
0b0000010001001111,   //D (ascii)      
0b0001000100111001,   //E (ascii)      
0b0001000000110001,   //F (ascii)      
0b0000000100111101,   //G (ascii)      
0b0001000100110110,   //H (ascii)      
0b0000010001000000,   //I (ascii)      
0b0000000000011110,   //J (ascii)      
0b0001001010110000,   //K (ascii)      
0b0000000000111000,   //L (ascii)      
0b0010000010110110,   //M (ascii)      
0b0010001000110110,   //N (ascii)      
0b0000000000111111,   //O (ascii)      
0b0001000100110011,   //P (ascii)      
0b0000001000111111,   //Q (ascii)      
0b0001001100110011,   //R (ascii)      
0b0001000100101101,   //S (ascii)      
0b0000010001000001,   //T (ascii)      
0b0000000000111110,   //U (ascii)      
0b0000100010110000,   //V (ascii)      
0b0000101000110110,   //W (ascii)      
0b0010101010000000,   //X (ascii)      
0b0010010010000000,   //Y (ascii)      
0b0000100010001001,   //Z (ascii)      
0b0000000000111001,   //[ (ascii)      
0b0010001000000000,   //\ (ascii)      
0b0000000000001111,   //] (ascii)      
0b0000100010000011,   //^ (ascii)      
0b0000000000001000,   //_ (ascii)      
0b0010000000000000,   //` (ascii)      
0b0001010000011000,   //a (ascii)      
0b0001001000111000,   //b (ascii)      
0b0001000100011000,   //c (ascii)      
0b0000100100001110,   //d (ascii)      
0b0001100000011000,   //e (ascii)      
0b0001000000110001,   //f (ascii)      
0b0000000110001110,   //g (ascii)      
0b0001010000110000,   //h (ascii)      
0b0000010000000000,   //i (ascii)      
0b0000000000001110,   //j (ascii)      
0b0000011011000000,   //k (ascii)      
0b0000000000110000,   //l (ascii)      
0b0001010100010100,   //m (ascii)      
0b0001010000010000,   //n (ascii)      
0b0001000100011100,   //o (ascii)      
0b0011000000110000,   //p (ascii)      
0b0000000110000110,   //q (ascii)      
0b0001000000010000,   //r (ascii)      
0b0000001100001000,   //s (ascii)      
0b0001000000111000,   //t (ascii)      
0b0000000000011100,   //u (ascii)      
0b0000001000000100,   //v (ascii)      
0b0000101000010100,   //w (ascii)      
0b0001101100000000,   //x (ascii)      
0b0000001000001100,   //y (ascii)      
0b0001100000001000,   //z (ascii)      
0b0011100000001001,   //{ (ascii)      
0b0000010001000000,   //| (ascii)      
0b0000001110001001,   //} (ascii)      
0b0010000010100000,   //~ (ascii)      
0b0011111111111111    //127            
};
#endif