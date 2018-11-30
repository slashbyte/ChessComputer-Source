/*****************************************************
File: frontend.h
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
#ifndef frontend_h
#define frontend_h
/************************************
This class contains functions that
manage all of the game "functions".
ie. new game, undo, move

In addition to managing the "backend"
thread functions.

This is an extension of
the "backend" class
*************************************/

class FrontEnd : public BackEnd
{
    using BackEnd::BackEnd;
public:
    void begin(void);                 /* Starts the backend threads */
	/* access functions */
    bool is_button(void);             /* checks for valid button press */
    int get_button(void);             /* returns the button value */
    bool is_engine(void);             /* checks for valid stream state */
    std::string get_engine(void);     /* returns a response string */
	/***************************/
    void send_display(std::string a);         /* send the hardware display a string to display */
    void send_display(std::string a, bool b); /* send an upper or lower case string */
    void send_engine(std::string a);          /* send the "engine" a string (command) */
	/******************************/
	/* Game play functions */
    void undoMove(void);                /* undo the computers last move and your last move */
    void go(void);                      /* invokes the chess engine */
    void newGame(int sd, bool p);       /* begins a new game, takes searchDepth and ponder flag */
    bool getMove(int b);                /* grab a move from the user */
    void showMove(std::string b);       /* show the computers move */
    void clear(void);                   /* clears the screen */
    void posVer(void);                  /* FEN position request */
    void hint(void);                    /* request a hint */
    void error(void);                   /* display the error screen */
    void check(bool b);                 /* set or clear the "check" LED */
    void mate(bool b);                  /* set or clear the "mate" LED */
    void mateBlink(void);               /* blinks the display if in mate */
    void thinkANI(void);                /* display animated think screen */
    void think(void);                   /* display simple think screen */
    void killScreen(int b, int _delay); /* displays the kill screen (draw by 50, resign) */
    void fen(std::string b);            /* displays the FEN pos string */
    void saveDisplayState(void);        /* saves the current display state */
    void restoreDisplayState(void);     /* restores the saved display state */
    void level(int &sd);                /* sets the search depth level */
	void ponder(bool &p);               /* turn ponder on or off */
	void getBoard(void);                /* request board */
	void printBoard(std::string a);     /* display the chessboard on the console (for debugging) */
	void showHint(std::string b);       /* display the computers hint */
	
private:
	/* thread objects */
    std::thread t1,t2,t3,t4;
	/* vars */
    const char alfa[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    const char num[8] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    const std::string spinner = "/-\\|";
    const std::string KS[7] = {"White Mates", "Black Mates", "Stalemate", "Draw", "Draw by 50 rule", "Draw", "Resign"};
    uint16_t mState[8];
	/* helper function */
	void strToUpper(std::string &a); /* string to uppercase */
    void strToLower(std::string &a); /* string to lower case */
    char buttonToChar(int a, int b); /* converts a button code to a char */
};


#endif