/*****************************************************
File: main.cpp
Description: container class for data
Author: Slash/Byte
Date: 11-30-2018
Notes: Work in progress

MIT License (https://opensource.org/licenses/MIT)
.▄▄ · ▄▄▌   ▄▄▄· .▄▄ ·  ▄ .▄▄▄▄▄·  ▄· ▄▌▄▄▄▄▄▄▄▄ .
▐█ ▀. ██•  ▐█ ▀█ ▐█ ▀. ██▪▐█▐█ ▀█▪▐█▪██▌•██  ▀▄.▀·
▄▀▀▀█▄██▪  ▄█▀▀█ ▄▀▀▀█▄██▀▐█▐█▀▀█▄▐█▌▐█▪ ▐█.▪▐▀▀▪▄
▐█▄▪▐█▐█▌▐▌▐█ ▪▐▌▐█▄▪▐███▌▐▀██▄▪▐█ ▐█▀·. ▐█▌·▐█▄▄▌
 ▀▀▀▀ .▀▀▀  ▀  ▀  ▀▀▀▀ ▀▀▀ ··▀▀▀▀   ▀ •  ▀▀▀  ▀▀▀
*****************************************************/
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include "pstream.h"

#include "ht16k33.h"
#include "starburst.h"
#include "container.h"
#include "backend.h"
#include "frontend.h"

#define ADDR 0x70 //hardware i2c address

using namespace std;

int main(void)
{
    printf("Chess Challenger\n");
    printf("Slash/Byte\n");
	/* mapped the buttons to the keyboard for testing on the PC */
    printf("----------------------\n"); 
    printf("Keyboard Emulation Map\n"); 
    printf("----------------------\n");
	printf("1:RE, 2:CB, 3:CL, 4:EN\n");
    printf("Q:LV, W:DM, E:PB, R:PV\n");
    printf("A:A1, S:B2, D:C3, F:D4\n");
    printf("Z:E5, X:F6, C:G7, V:H8\n");
    printf("----------------------\n");

	/* hardware display obj */
    STARBURST HT;
    FrontEnd CC(&HT);

    HT.begin(ADDR, 4); //address of the display and the number of digits
    HT.clrAll();
    HT.print("--Chess Challenger--", 100);
	/* start up the threads after splash message */
    CC.begin();

    /* helper variables for game play logic */
    bool _b;              //button & stream flag
    bool SIDE = 0;        //players side
    bool NEWGAME = 1;     //newgame flag
	bool PONDER = 0;      //ponder flag
	int searchTime = 0; //search time
    const bool WHITE = 0;
    const bool BLACK = 1;

	CC.newGame(searchTime, PONDER); //start new game

    while(1) //main loop
    {
        _b = CC.is_button();                     //check button state
        if(_b)                                   //if there was a button press
        {
            int _c = CC.get_button();            //get button
			/* RE, reset */
            if(_c == 0)
            {
                NEWGAME = 1;                     //reset game flag
                SIDE = 0;                        //reset side to default
                CC.mate(0);                      //clear mate
                CC.newGame(searchTime, PONDER); //new game
            }
			/* CB, ponder control */
            if(_c == 1)
				CC.ponder(PONDER);
			/* CL, clear */
            if(_c == 2)
                CC.clear();   //clear the HW display
			/* EN, Enter */
            if(_c == 3)
            {
                if(NEWGAME)  //if the game is new, flop sides
                {
                    SIDE=!SIDE;
                    NEWGAME=0;
                }
                CC.go();       //engine go
                //CC.think();  //think screen
                CC.thinkANI(); //think with animation
            }
			/* LV, set level */
            if(_c == 4)
                CC.level(searchTime); //select your level of play
			/* DM, undo */
            if(_c == 5)                //DM, undo a move
			{
                CC.undoMove();
				CC.getBoard(); //debug stuff
			}
			/* PB, problem mode */
            if(_c == 6)
                CC.hint();
			/* PV, position verification */
            if(_c == 7) 
                CC.posVer();     //position verification request
			/* A1-H8 */	
            if((_c >= 8)&&(_c <= 15))
            {
                if(NEWGAME)
                    NEWGAME=0;
                if(!CC.getMove(_c)) //if move was "entered"
                {
                    CC.check(0);    //clear check led
                    //CC.think();   //show think screen
                    CC.thinkANI();  //think with animation
                }
            }
        }
        _b = CC.is_engine(); //check engine
        if(_b)               //if theres a response from the engine
        {
            string _d = CC.get_engine();   //get engine response
            int _a = CC.checkState(_d, 1); //check and trim
			/* error or illegal move */
            if((_a == 1) || (_a == 2))
                CC.error();                //error screen, flash @ 2hz
			/* black in check */
            if(_a == 3)
				if(SIDE == BLACK) //if my side
					CC.check(1);  //set check led
			/* white in check */
            if(_a == 4)
				if(SIDE == WHITE) //if my side
					CC.check(1);  //set check led
			/* White mates */	
            if(_a == 5)
				if(SIDE == WHITE) //if not my side (computer)
					CC.mate(1);   //set mate led
			/* black mates */
            if(_a == 6)
				if(SIDE == BLACK) //if not my side (computer)
					CC.mate(1);   //set mate led
			/* Mate */	
            if((_a == 5) || (_a == 6))
                CC.mateBlink();         //flash display @ 1hz, if mate (end of game)
			/* draw message */
            if((_a >= 7) && (_a <= 11)) //scroll kill-screen (draw message)
                CC.killScreen(_a, 150); //@150ms/char speed
			/* Display computer move */
            if(_a == 12)
			{
				printf("COMPUTER: %s\n", _d.c_str()); //comment me out!
                CC.showMove(_d);                      //display the computers move
				CC.getBoard();                        //debug stuff, comment me out
			}
			/* Display Hint */
            if(_a == 13)
			{
				printf("HINT: %s\n", _d.c_str()); //comment me out!
                CC.showHint(_d);                  //Algebraic notation.
				//hint sometimes gets clipped
				//might add scroll
			}
			/* FEN string display */
            if(_a == 14)
			{
				printf("FEN: %s\n", _d.c_str()); //comment me out!
                CC.fen(_d);                      //display fen string
			}
			/* polyglot board output */
			if(_a == 15)
				CC.printBoard(_d);				
        }
        CC.cpuBreak();
    }
    return 0;
}