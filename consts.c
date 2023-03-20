#include <kipr/wombat.h>
#include <comp_lib.h>
#include <L_Mechanism.h>
#include <arm_hand_position.h>
#include <functions.h>
#include <consts.h>
int ML = 2; // black closest to screen
int MR = 1; //red closest to red
int arm = 3;
int shifter = 2;
int claw = 0;
int rIR = 2;
int lIR = 0;
int fET = 4;
int light = 3;
int BR = 1;
int BL = 2;

int shifter_max = shifter_min - 1232;
int claw_open = 495;
int claw_closed = 15;
int arm_up = 16;
//
int shifter_ver = 980;
int shifter_hor = 40;
int claw_max = 1578;
int claw_min = 590;
int arm_max = 250;
int arm_min = 2000; 
//
int analog_white = 160;
int analog_black = 2960;
int midpoint = 2000;

int tprL = 1850;
int tprR = 1848;

float wheel = 8.6394;