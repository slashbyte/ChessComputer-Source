/*****************************************************
File: backend.h
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
#ifndef backend_h
#define backend_h
/************************************
This class contains functions that
will be threaded.

Theses functions.....
- manage polyglot's io stream
- manage hardware button polling
- manage hardware display updates
*************************************/

class BackEnd
{
public:
    BackEnd(STARBURST *a);
    STARBURST* hardwareDisplay;
	/* lock guard */
	std::mutex m;
    /* container objects for holding data */
    Container engineOutput;  /* container for the engine output */
    Container engineInput;   /* container for the engine input */
    Container displayInput;  /* container for the display */
    Container buttonOutput;  /* container for the buttons */
    /* thread functions */
    void readEngine(void);   /* updates the input stream */
    void writeDisplay(void); /* writes to the hardware display */
    void writeEngine(void);  /* updates the output stream */
    void readButton(void);   /* polls the buttons */
    /* helper functions */
    int checkState(std::string &a, bool b = 0); /* checks the input stream for responses */
    /* delay function to give the CPU a break in infinite loops */
    void cpuBreak(void)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(HANDBREAK));
    };

private:
	/* stream object */
    redi::pstream* proc;
	/* vars */
    const int HANDBREAK = 5; /* CPU break time, 5 milliseconds */
    const std::string response[15] = /* responses to check the input stream against */
    {
        "Error (unknown command):",
        "Illegal move:",
        "Black in check", //hacked polyglot only
        "White in check", //hacked polyglot only
        "1-0 {White mates}",
        "0-1 {Black mates}",
        "1/2-1/2 {Stalemate}",
        "1/2-1/2 {Draw by insufficient material}",
        "1/2-1/2 {Draw by fifty-move rule}",
        "1/2-1/2 {Draw by repetition}",
        "resign",
        "move",
        "Hint",
        "POLYGLOT FEN:", //hacked polyglot only
        "POLYGLOT"       //hacked polyglot only
    };
    /* helper functions */
    void putStream(std::string a); /* actually sends the data to the stream */
    std::string getStream(void);   /* actually receives the stream data */
    void clearStream(void);        /* clears the stream buffer */
};
#endif