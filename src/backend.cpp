/*****************************************************
File: backend.cpp
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
#include <thread>
#include <mutex>
#include "container.h"
#include "ht16k33.h"
#include "starburst.h"
#include "pstream.h"
#include "backend.h"
/************************************
This class contains functions that
will be threaded.

Theses functions.....
- manage polyglot's IO stream
- manage hardware button polling (emulated at the moment)
- manage hardware display updates
*************************************/

/*
 Constructor, takes a "STARBURST" display object
 Starts the polyglot stream
 assumes polylgot is installed in its default directory
*/
BackEnd::BackEnd(STARBURST *a)
{
    //start the stream
    proc = new redi::pstream("polyglot", redi::pstream::pstdout |
                             redi::pstream::pstdin | redi::pstream::pstderr);
    hardwareDisplay = a;
}

/* Sends a string to the output stream, ends with a new line */
void BackEnd::putStream(std::string a)
{
    *proc << a << std::endl;
}

/*
 Returns a string from the input stream.
 Terminates if there is a stream error.
*/
std::string BackEnd::getStream(void)
{
    std::string buffer;
    if(!std::getline(*proc, buffer))
    {
        printf("Check your Polyglot install and .ini file\n");
        printf("also check your engine installation path.\n");
        printf("Stream Error, see ya!\n");
        exit(EXIT_FAILURE); //don't try this at home kids
    }
    return buffer;
}

/* clears the io stream */
void BackEnd::clearStream(void)
{
    proc->clear();
}

/*
 Constantly checks and fills a container
 with a string read from the input stream.
 only fills the container with a "valid" string
 */
void BackEnd::readEngine(void)
{
    while(1)
    {
        if(engineOutput.is() == 0) //if container is empty
        {
            std::string readBuffer = getStream(); //read the stream
            if(!readBuffer.empty()) //if the stream is full
            {
                int a = checkState(readBuffer); //check the state, no trim
                if(a) //if the state is valid
                    engineOutput.set_str_easy(readBuffer); //store the string
            }
        }
        cpuBreak();
    }
}

/*
 Constantly checks a container for display data
 if there is display data, send it to the hardware display
 */
void BackEnd::writeDisplay(void)
{
    while(1)
    {
        if(displayInput.is() == 1) //if the container is full
        {
            //_displayBusy = 1; //display lock
			m.lock();
            std::string disp = displayInput.get_str(); //get the display data
            /*<<<<<<<<<<<<<<<<<<<< REMOVE A >>>>>>>>>>>>>>>>>>>>>>>>>
             check and mate DP bug fix
             a temp solution for testing the
             check and mate LEDs
             This will change when its running on real hardware
            */
            //preserve DP state
            bool _check = (hardwareDisplay->memory[0] & 0x4000); //Q&D fix
            bool _mate = (hardwareDisplay->memory[3] & 0x4000);  //Q&D fix
            /*<<<<<<<<<<<<<<<<<<<< REMOVE A >>>>>>>>>>>>>>>>>>>>>>>>>*/

            if(!disp.empty())
                hardwareDisplay->print(disp); //writes string to hardware display

            /*<<<<<<<<<<<<<<<<<<<< REMOVE B >>>>>>>>>>>>>>>>>>>>>>>>>*/
            //re-enable DP state after write
            if(_check)
                hardwareDisplay->setLed(14); //Q&D fix
            if(_mate)
                hardwareDisplay->setLed(62); //Q&D fix
            /*<<<<<<<<<<<<<<<<<<<< REMOVE B >>>>>>>>>>>>>>>>>>>>>>>>>*/
            //_displayBusy = 0; //display unlock
			m.unlock();
        }
        cpuBreak();
    }
}

/*
 Constantly checks a container for stream data
 if there is data, place it on the output stream
 IE send commands to polyglot
 */
void BackEnd::writeEngine(void)
{
    while(1)
    {
        if(engineInput.is() == 1) //if the container is full
        {
            std::string input = engineInput.get_str(); //get the input data
            if(!input.empty())
                putStream(input); //write the input data to the stream
        }
        cpuBreak();
    }
}

/*
 this is a CIN button emulation,
 this will change when I have real hardware

 Constantly checks cin for a button read,
 then adds it to a container
 */
void BackEnd::readButton(void)
{
    while(1)
    {
        if(buttonOutput.is() == 0) //if no button is available
        {
			//m.lock();
            /* <<<<<<<<<<<<<<<<< REMOVE >>>>>>>>>>> */
            //quick and dirty emulation for keypad
            char a = getchar(); //get char from cin
            if(a) //check input
            {
                /* keypad mapping */
                int k = -1;
                if(a == '1') k=0; //RE
                if(a == '2') k=1; //CB
                if(a == '3') k=2; //CL
                if(a == '4') k=3; //EN

                if(a == 'q') k=4; //LV
                if(a == 'w') k=5; //DM
                if(a == 'e') k=6; //PB
                if(a == 'r') k=7; //PV

                if(a == 'a') k=8; //A1
                if(a == 's') k=9; //B2
                if(a == 'd') k=10; //C3
                if(a == 'f') k=11; //D4

                if(a == 'z') k=12; //E5
                if(a == 'x') k=13; //F6
                if(a == 'c') k=14; //G7
                if(a == 'v') k=15; //H8

                if(k!= -1) //if input is ok
                    buttonOutput.set_int_easy(k); //place in container
            }
            /* <<<<<<<<<<<<<<<<< REMOVE >>>>>>>>>>> */
			//m.unlock();
        }
        cpuBreak();
    }
}

/*
 This function takes string and compares it to an array of strings
 it then returns the index number +1.
 this function also trims unused information from the string
 set by 'b', if b is true, the string is trimmed
*/
int BackEnd::checkState(std::string &a, bool b)
{
    if(a.empty()) //return 0 if the string is empty
        return 0;

    size_t found;
    int return_val = 0;

    do
    {
        found = a.find(response[return_val]); //iterate through valid engine response
        return_val++;
        if(found!=std::string::npos) //break if found
            break;
    }
    while(return_val < 16); //array limit

    if(b) //trim string
    {
        if((return_val >= 12) && (return_val <=14))
        {
            if(return_val == 12)
                found+=5;
            else if(return_val == 13)
                found+=6;
            else
                found+=14;

            std::string b;
            for(std::string::size_type i = found; i < a.length(); i++)
                b+=a.at(i);
            a=b;
        }
    }
    return return_val%16; //returns the index value +1
}