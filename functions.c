#include <kipr/wombat.h>
#include <comp_lib.h>
#include <L_Mechanism.h>
#include <arm_hand_position.h>
#include <functions.h>
#include <consts.h>
int Rspd;
int Lspd;

float itt(int tpr, float inches){
    float tpi;
	tpi = tpr/wheel;
    printf("%f\n",tpi*inches);
    return tpi*inches;
}
void ratio(int spd){
    //45/500
    //0.09
    float math = spd*54.3;
    float final = math/500;
    float diff;
    printf("final %f\n",final);
	if(tprL > tprR){diff = tprL-tprR; printf("diff1 %f\n",diff); Lspd = diff * final; Rspd = 0;}
    else if(tprR > tprL){diff = tprR-tprL; Rspd = diff * final; Lspd = 0;}
    else{return;}
}

void in_drive(int spd, float des)
{
    cmpc(ML);
    cmpc(MR);
    ratio(spd);
	int rspd = spd - Rspd;
    printf("r %d\n",rspd);
	int lspd = spd - Lspd;
    printf("l %d\n",lspd);
    float r = itt(tprR,des);
    float l = itt(tprL,des);
    while(1){
		if(gmpc(ML) < l){
    		mav(ML, lspd);
   		}else{mav(ML,0);}
        if(gmpc(MR) < r){
    		mav(MR, rspd);
   		}else{mav(MR,0);}
        if(gmpc(ML) > l || gmpc(MR) > r){break;}
    }
    mav(ML,0);
    mav(MR, 0);
}
void Drive_backwards(int desired,int speed){
	motor(MR,speed);
    motor(ML,speed);
    msleep(desired);
    
    motor(MR,0);
    motor(ML,0);
    msleep(300);
}
void drive_forwards(int speed, int desired){
	motor(ML,speed);
    motor(MR,speed);
    msleep(desired);
    
    motor(ML,0);
    motor(MR,0);
    msleep(300);
}
void left_turn(int speed, int desired){
	motor(MR,speed);
    msleep(desired);
}
void right_turn(int speed, int desired){
	motor(ML,speed);
    msleep(desired);
}
void green_pom_right_turn(int speed, int desired){
	motor(MR,(-1)*speed);
    msleep(desired);
}
void stop_please(int speed, int desired){
	motor(ML,speed);
    motor(MR,speed);
    msleep(desired);
}
void in_turn(int deg,int spd){
    cmpc(ML);
    cmpc(MR);
    float in_length = (wheel/3.14) * (deg/360);
    int ticks = itt(tprL, in_length);
	if(deg > 0){
        Rspd = -1*spd; 
        Lspd = spd;
        while(gmpc(ML) < ticks){move(Lspd,Rspd);}     
     }
    else if(deg < 0){Lspd = -1*spd; Rspd = spd;}
    else{return;}
    
}
/*
void line_follow(int side, int speed){
  //line to left, right sensor: 1
  //line to right, left sensor: 2
  switch(side){
      case 1: {
          while(1){
            if(buffer(rIR) < midpoint){move(speed-(speed*0.046), speed);}
            if(buffer(rIR) > midpoint){move(0,0); break;}
            if(buffer(lIR) > midpoint){move(speed, -1*(speed/4));}
            if(buffer(lIR) < midpoint){move(-1*(speed/4), speed);} 
          }
      } 
      case 2: {
           while(1){
            if(buffer(lIR) < midpoint){move(speed, speed-(speed*0.046));}
            if(buffer(lIR) > midpoint){move(0,0); break;}
            if(buffer(rIR) < midpoint){move(speed, -1*(speed/4));}
            if(buffer(rIR) > midpoint){move(-1*(speed/4), speed);} 
          }
      }
  }
}
int buffer(int sensor){
  int value = 0;
  int total = 0;
  int i = 0;
  while (i<5){
    i++;
    value = analog(sensor);
    msleep(3);
    total+=value;
  }
  total=total/5;
  return total;
}

void slow_servo(int part, int des, int speed) {
  int cur = get_servo_position(part);
  if(des < 50){des=50;};if(des > 2000){des=2000;};
  if (cur < des) {
    enable_servo(part);
    while (cur != des) {
    	cur+=speed;
        set_servo_position(part, cur);
        msleep(1);
    }
    disable_servo(part);
  }
  if (cur > des){
    enable_servo(part);
    while (cur != des) {
    	cur-=speed;
        set_servo_position(part, cur);
        msleep(1);
    }
    disable_servo(part);
  }
}
*/
void move(int l_speed,int r_speed){//basic moving function thats based off mav
    mav(MR,r_speed);
    mav(ML,l_speed);
}

void a_cel(){
    float L_speed;
    float curr_time = seconds(); 
    float init_time = seconds();
    while( (curr_time - init_time) < .2 ){
        curr_time = seconds();   
        L_speed = 6.75 * ((curr_time - init_time) * 1000);
        move(L_speed,L_speed); 
    }
}

void de_cel(){
    cmpc(ML);
    cmpc(MR);
    while(gmpc(ML) < 500){

        int R_speed = 2.4 * (500 - gmpc(MR) + 150);
        int L_speed = 2.4 * (500 - gmpc(ML) + 150);
        move(L_speed,R_speed);

    }
    move(0,0);
}

//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
int black_speed;
void square_up(int ending,int speed){
    if(speed > 0 && speed < 400){//failcheck for speed
        black_speed = speed;
    }
    else{black_speed = 1*speed;}
    if(ending == 1 || ending == 2){
        while(1){
            if(buffer(lIR)<midpoint && buffer(rIR)<midpoint){ //move to black
                move(speed,speed);
            }
            if(buffer(rIR)>midpoint){ //right wheel back if black
                move(speed,(speed*(-.25)));
            }
            if(buffer(lIR)>midpoint){//left wheel back if black
                move((speed*(-.25)),speed);
            }
            if(buffer(lIR)>midpoint && buffer(rIR)>midpoint) { //if both sensors on black, stop
                move(0,0);
                break;
            }
        }
    }
   
    switch(ending){
        case 1: //if ending on white:
            {
                while(1){
                    if(buffer(lIR)>midpoint && buffer(rIR)>midpoint){ //move forward if black
                        move(black_speed,black_speed);
                    }
                    if(buffer(lIR)<midpoint){ //right wheel forward if left sensor is white
                        move(0,black_speed);
                    }
                    if(buffer(rIR)<midpoint){ //left wheel forward if right sensor is white 
                        move(black_speed,0);
                    }
                    if(buffer(lIR)<midpoint && buffer(rIR)<midpoint){ //if white, stop
                        move(0,0);
                        break;
                    }
                }
            }
        case 2: //if ending on black:
            {
                while(1){
                    if(buffer(lIR)>midpoint && buffer(rIR)>midpoint){ //move backward if black
                        move(-1*black_speed,-1*black_speed);
                    }
                    if(buffer(lIR)<midpoint){ //right wheel backward if white
                        move(0,-1*black_speed);
                    }
                    if(buffer(rIR)<midpoint){ //left wheel backward if white
                        move(-1*black_speed,0);
                    }
                    if(buffer(lIR)<midpoint && buffer(rIR)<midpoint){ //if white, stop
                        move(0,0);
                        break;
                    }
                }
            }
    }
}


/* gyro lib

double bias = 0.0;

double calibrate_gyro(){//gyro calibration through finding gyro setting it to zero then setting theta as that value
    int i = 0;
    double avg = 0;
    while( i < 50){
        avg += gyro_z();
        msleep(1);
        i++;
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);
    return bias;
}
void Drive(int desired,int speed){
    float add_fact = 1.920137e-16;
    float mult_fact = 0.00004470956;
    double theta = 0;
    float max_speed = 0;
    cmpc(ML);
    cmpc(MR);
    if(desired > 0 ){
        a_cel(); 
        if(desired < speed){
            speed = desired;   
        }
        while( gmpc ( ML ) < ( desired - 500 )){
            if( speed > 0 ){
                motor( MR,  (( speed - speed * (add_fact + mult_fact * theta))));
                motor( ML, (( speed + speed * (add_fact + mult_fact * theta))));
            }
            else{
                motor( MR,  (( speed + speed * (add_fact + mult_fact * theta))));
                motor( ML,  (( speed - speed * (add_fact + mult_fact * theta))));
            }
            msleep(10);
            theta += ( gyro_z() - bias) * 10;
            (speed + speed * (add_fact + mult_fact * theta)) > max_speed ? max_speed=(speed + speed * (add_fact + mult_fact * theta)) : msleep(1);
        }
        if ( desired > 500 ){
            de_cel();
            printf("%f",max_speed);
            move(0,0);
        }
        else{
            move(0,0);
        }
    }
    else if (desired < 0){
        while( gmpc ( ML ) > desired ){
            if( speed > 0 ){
                motor( MR,  (( speed - speed * (add_fact + mult_fact * theta))));
                motor( ML, (( speed + speed * (add_fact + mult_fact * theta))));
            }
            else{
                motor( MR,  (( speed + speed * (add_fact + mult_fact * theta))));
                motor( ML,  (( speed - speed * (add_fact + mult_fact * theta))));
            }
            msleep(10);
            theta += ( gyro_z() - bias) * 10;
            (speed + speed * (add_fact + mult_fact * theta)) > max_speed ? max_speed=(speed + speed * (add_fact + mult_fact * theta)) : msleep(1);
        }   
    }
}


//////////////////////////////////////////////////////////////////
void drive_with_gyro(int speed, double time){//gyro using clock time not distance(much more inaccurate)
    double startTime = seconds();
    double theta = 0;
    while(seconds() - startTime < time){
        //calibrate_gyro();
        if (theta < 1000 && theta > -1000){
            mav(MR, speed);
            mav(ML, speed);
        }
        else if (theta < 1000){
            mav(MR, speed + 100);
            mav(ML, speed - 100);
        }
        else{
            mav(MR, speed - 100);
            mav(ML, speed + 100);
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
        //printf("%f",theta);
    };
    move(0,0);
};
//////////////////////////////////////////////////////////////////
void turn_with_gyro(int speed, int deg, int frz){//turning using the gyro we use calibrate still to find zero then set theta to a know value instead of 0
    //frz is if wheel freezes when turning. 1 is yes
    double theta = 0;
    int targetTheta; 
    int turn;
    if(frz == 1){turn = 0;}else{turn = -1*speed;}
    switch(deg){
        case -40:
            targetTheta = target_theta_m40;
            move(turn,speed);
            break;
        case -30:
            targetTheta = target_theta_m30;
            move(turn,speed);
            break;
        case -22:
            targetTheta = target_theta_m22;
            move(turn,speed);
            break;
        case 0:
            targetTheta = target_theta_mrings;
            move(turn,speed);
            break;
        case 1:
            targetTheta = target_theta_rings;
            move(speed,turn);
            break;
        case 45:
            targetTheta = target_theta_45;
            move(speed,turn);
            break;
        case 90:
            targetTheta = target_theta_90;
            move(speed,turn);
            break;
        case 180:
            targetTheta = target_theta_180;
            move(speed,turn);
            break;
        case -45:
            targetTheta = target_theta_m45;
            move(turn,speed);
            break;
        case -90:
            targetTheta = target_theta_m90;
            move(turn,speed);
            break;
        case -180:
            targetTheta = target_theta_m180;
            move(turn,speed);
            break;
        default:
            targetTheta = 0;
            break;
    }  
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
        printf("Turn Gyro Z: %d\n",gyro_z());
    }
    move(0,0);
    msleep(50);
    
}

//////////////////////////////////////////////////////////////////
void PID_gyro_drive(int speed, double time){
    double startTime = seconds();
    double theta = 0;
    while((seconds() - startTime) < time){
        if(speed > 0){
            mav(MR, (speed - (speed * (theta/100000))));            
            mav(ML, (speed + (speed * theta/100000)));
        }


        else{
            mav(ML, (speed - (speed * theta/100000)));            
            mav(MR, (speed + (speed * (theta/100000))));
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
    }
    move(0,0);
};
////////////////////////////////////////////////////////
*/