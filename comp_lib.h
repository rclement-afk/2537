#define right_motor 1
#define left_motor 2
#define target_theta_45 225000 //numbers for wallaby-4188
#define target_theta_90 507500
#define target_theta_180 1061500
#define target_theta_360 2175000
#define target_theta_m45 225000
#define target_theta_m90 507500
#define target_theta_m180 1061500
#define target_theta_m360 2175000
#define target_theta_building 260000
#define target_theta_building_2 260000
//#define shifter_min 500

//#define analog_white 2500
//int analog_white;
int analog_black;
//#define analog_black 3800
#define digital_right 0
#define digital_left 1
#define left_IR 1
#define right_IR 0
#define stop 0
#define multiplier 1.5
#define ET 5
#define front_IR 2
int min_accel_x;
    int max_accel_y;
void bookItAcrossValve();
/*#define arm 0
#define claw 1
#define arm_start 600
#define claw_start 1055
#define claw_close 600
#define arm_up 0*/
void pvc_backwards_follow();

void move(int l_speed,int r_speed);/*{
    mav(right_motor,r_speed);
    mav(left_motor,l_speed);
}*/
void in_drive(int spd, float des);
int white;
int black;
int physical;
int black_speed;

void square_up(int ending,int speed);/*
    if(speed > 0 && speed < 600){
        black_speed = 1.2*speed;
    }
    else{black_speed = 0.25*speed;}
    if(ending == 1 || ending == 2){
        while(1){
            if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                move(speed,speed);
            }
            if(analog(right_IR)>analog_white){
                move(speed,stop);
            }
            if(analog(left_IR)>analog_white){
                move(stop,speed);
            }
            if(analog(left_IR)>analog_white && analog(right_IR)>analog_white) {
                move(stop,stop);
                break;
            }
        }
    }
    if(ending == 3){
        ao();
    }
    switch(ending){
        case 3:
            {
                while(1){
                    if(digital(digital_right)==0 && digital(digital_left)==0){
                        move(speed,speed);
                    }
                    if(digital(digital_right)==1){
                        move(speed,stop);
                    }
                    if(digital(digital_left)==1){
                        move(stop,speed);
                    }
                    if(digital(digital_right)==1 && digital(digital_left)==1){
                        move(stop,stop);
                        break;
                    }
                }
            }
        case 1:
            {
                while(1){
                    if(analog(left_IR)>analog_white && analog(right_IR)>analog_white){
                        move(black_speed,black_speed);
                    }
                    if(analog(left_IR)<analog_white){
                        move(stop,black_speed);
                    }
                    if(analog(right_IR)<analog_white){
                        move(black_speed,stop);
                    }
                    if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                        move(stop,stop);
                        break;
                    }
                }
            }
        case 2:
            {
                while(1){
                    if(analog(left_IR)>analog_white && analog(right_IR)>analog_white){
                        move(-1*black_speed,-1*black_speed);
                    }
                    if(analog(left_IR)<analog_white){
                        move(stop,-1*black_speed);
                    }
                    if(analog(right_IR)<analog_white){
                        move(-1*black_speed,stop);
                    }
                    if(analog(left_IR)<analog_white && analog(right_IR)<analog_white){
                        move(stop,stop);
                        break;
                    }
                }
            }
    }
}*/

double bias;

double calibrate_gyro();//{
    int i;
    double avg ;
    /*while( i < 50){
        avg += gyro_z();
        msleep(1);
        i++;
        printf("Gyro Z: %d\n",gyro_z());
    }
    bias = avg / 50.0;
    printf("New Bias: %f\n", bias);
    return bias;
}*/

void drive_with_gyro(int speed, double time);//{
    //calibrate_gyro();
    double startTime;
    double theta;
    /*while(seconds() - startTime < time){
        if (theta < 1000 && theta > -1000){
            mav(right_motor, speed);
            mav(left_motor, speed);
        }
        else if (theta < 1000){
            mav(right_motor, speed + 100);
            mav(left_motor, speed - 100);
        }
        else{
            mav(right_motor, speed - 100);
            mav(left_motor, speed + 100);
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
        printf("%f",theta);
    }
    ao();
}*/

void PID_gyro_drive(int speed, double time);//{
    //calibrate_gyro();
    double startTime;
    double theta ;
    /*while((seconds() - startTime) < time){
        if(speed > 0){
            mav(right_motor, (speed - (speed * (theta/100000))));            
            mav(left_motor, (speed + (speed * theta/100000)));
        }


        else{
            mav(left_motor, (speed - (speed * theta/100000)));            
            mav(right_motor, (speed + (speed * (theta/100000))));
        }
        msleep(10);
        theta += (gyro_z() - bias) * 10;
    }
    move(0,0);
}*/
void turn_with_gyro_create(int speed, int deg);//{
    double theta;
    int targetTheta; 
    /*switch(deg){
        case 45:
            targetTheta = target_theta_45;
            create_drive_direct(speed,speed*-1);
            break;
        case 90:
            targetTheta = target_theta_90; //507500
            create_drive_direct(speed,speed*-1);
            break;
        case 180:
            targetTheta = target_theta_180;
            create_drive_direct(speed,speed*-1);
            break;
        case 360:
            targetTheta = target_theta_360;
            create_drive_direct(speed,speed*-1);
            break;
        case -45:
            targetTheta = target_theta_m45;
            create_drive_direct(speed*-1,speed);
            break;
        case -90:
            targetTheta = target_theta_m90;
            create_drive_direct(speed*-1,speed);
            break;
        case -180:
            targetTheta = target_theta_m180;
            create_drive_direct(speed*-1,speed);
            break;
        case -360:
            targetTheta = target_theta_m360;
            create_drive_direct(speed*-1,speed);
            break;
        default:
            targetTheta=0;
            break;
    }  
    while(theta < targetTheta){
        msleep(10);
        theta += abs(gyro_z() - bias) * 10;
        printf("Turn Gyro Z: %d\n",gyro_z());
    }
    create_drive_direct(0,0);
}*/


void turn_with_gyro(int speed, int deg);//{
    //calibrate_gyro();
    double theta ;
    int targetTheta; 
    /*switch(deg){
        case 45:
            targetTheta = target_theta_45;
            move(speed,speed*-1);
            break;
        case 90:
            targetTheta = target_theta_90;
            move(speed,speed*-1);
            break;
        case 180:
            targetTheta = target_theta_180;
            move(speed,speed*-1);
            break;
        case 360:
            targetTheta = target_theta_360;
            move(speed,speed*-1);
            break;
        case -45:
            targetTheta = target_theta_m45;
            move(speed*-1,speed);
            break;
        case -90:
            targetTheta = target_theta_m90;
            move(speed*-1,speed);
            break;
        case -180:
            targetTheta = target_theta_m180;
            move(speed*-1,speed);
            break;
        case -360:
            targetTheta = target_theta_m360;
            move(speed*-1,speed);
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
    mav(right_motor, 0);
    mav(right_motor, 0);
    ao();
}*/

void backward_linefollow(int distance);
/*{
    cmpc(0);
    cmpc(2);
    while(gmpc(0)>-distance)
    {
        mav(left_motor,-.55*(analog(back_IR)));
        mav(right_motor,-.55*(3400-analog(back_IR)));
    }
}*/
void cube_verify();
/*{
    if(buffer(4)>1600)
    {
        move(-400,-400);
        while(buffer(4)>1400){}
        move(0,0);
    }
    if(buffer(4)<1600)
    {
        move(400,400);
        while(buffer(4)<1400){}
        move(0,0);
    }
}*/

void PID_gyro_drive_distance(int speed, int distance);

void pre_test();
//void calibration_square();


void valve_verify();
int n;


void PID_get_cube();