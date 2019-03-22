/**
    @file ballistics.c
    @author Vincent H Lai (vhlai)
    This program calculates time of travel and distance traveled at various angles of launch of an object based on it's initial velocity given by the user. 
  */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//acceleration of gravity (in m/s^2) (wihtout the "downwards" modifier)
#define GRAVITY 9.81
//PI
#define PI 3.14159

/**
    calculates the flight time given angle and initial velocity using the quadratic equation. 
    @param 
angle the angle at which a the object is shot
    @param 
v0 the objects initial velocity as read from input
  */
double flightTime( int angle, double v0 )
{
    double time = 0;
    //convert angle to radians
    double rads = angle*M_PI/180;
    //quadratic formula "a"
    double A = -1*GRAVITY/2;
    //quadratic formula "b"
    double B = v0*sin(rads);
    //calculates time
    time = ((-1*B)-sqrt(B*B))/2/A;
    //checks for positive time, if answer invalid, calculates alternate answer
    return time;
}



/**
    Creates a row of the table
    @param
angle: the angle at which the object was shot
    @param
v0: the initial velocity of the object
    @param
t: the time traveled
  */
void tableRow( int angle, double v0, double t )
{
    double rads = angle*M_PI/180;
    //distance traveled
    double distance = v0*t*cos(rads);
    printf("%10d | %10.3f | %10.3f | %10.3f\n", angle, v0, t, distance);
}

/**
    The main program. Reads input, writes each row using tableRow, and creates the headers. 
  */
int main(){
    printf("V0: ");
    double v0 = 0;
    scanf("%lf", &v0);
    putchar('\n');
    printf("     angle |         v0 |       time |   distance\n");
    printf("-----------+------------+------------+-----------\n");
    //Prints row in angle increments of 5 degrees up to 90
    for(int a = 0; a <= 90; a+=5){
        double time = flightTime(a, v0);
        tableRow(a, v0, time);
    }
    return 0;
}
