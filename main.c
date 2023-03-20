#include <kipr/wombat.h>
#include <comp_lib.h>
#include <L_Mechanism.h>
#include <arm_hand_position.h>
#include <functions.h>
#include <consts.h>
int main()
{
   printf("Kara");
    
    slow_arm(1568,1);
    slow_hand(claw_closed,1);
    msleep(5000);
    //wait_for_light(3);
    //start value 1573
    //main run under
    slow_hand(claw_open,1);
    square_up(2,1000);
    stop_please(0,300);
    slow_hand(claw_closed,1);
    slow_arm(691,1);
    stop_please(0,300);
    Drive_backwards(500,-100);
    left_turn(100,1500);//the 1200 point turn
    slow_hand(claw_open,1);
    square_up(1,-1000);
    Drive_backwards(200,-100);
    square_up(2,-1000);
    //square_up(1,1000);
    drive_forwards(100,1000);
    square_up(2,-1000);
    green_pom_right_turn(100,1700);
    Drive_backwards(1400,-100);
    stop_please(0,300);
    //left_turn(100,50);
    //reset place #1
    left_turn(100,400); 
    stop_please(0,300);   
    slow_arm(1491,1);
    drive_forwards(100,500);
    slow_hand(claw_closed,1);
    slow_arm(591,1);
    right_turn(100,1600);
    slow_hand(claw_open,1);
    square_up(2,-1000);
    
    //stacked pom code
    //drive_forwards(100,500);
    //slow_hand(claw_open,1);
    //slow_arm(688,1);
    
    return 0;
    
}
