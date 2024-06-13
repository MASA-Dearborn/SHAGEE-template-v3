#include "common/SHAGEE_config.h"
#include "BasicStepperDriver.h"

#define MOTOR_STEPS 200
#define MICROSTEPS 1
#define FLUSH_DEGREES 5
#define DEPLOY_DEGREES 80
#define RPM 280

// Probably pretty important to note that all of these functions are blocking lol

//create object stepper
BasicStepperDriver stepper(MOTOR_STEPS, MD_DIR, MD_STEP, MD_EN);

//set pins
void motor_setup()
{
    pinMode(MD_M0, OUTPUT);
    pinMode(MD_M1, OUTPUT);
    pinMode(MD_nSLP, OUTPUT);
    pinMode(MD_TRQ_ST, INPUT);
    pinMode(MD_STL_REP, INPUT);
    pinMode(MD_nFAULT, INPUT);

    digitalWrite(MD_M0,LOW);
    digitalWrite(MD_M1,LOW);
    digitalWrite(MD_nSLP,HIGH);
    digitalWrite(MD_EN,HIGH);

    stepper.begin(RPM, MICROSTEPS);
}

void motor_sleep()
{
    stepper.disable();
}

void motor_awake()
{
    stepper.enable();
}

//deploy airbrakes rotate(degrees), make sure this is positive
void motor_deploy()
{
    stepper.rotate(DEPLOY_DEGREES);
}

//retract airbrakes rotate(degrees), make sure this is negative
void motor_retract()
{
    stepper.rotate(-DEPLOY_DEGREES);
}

void motor_flush()
{
    stepper.rotate(FLUSH_DEGREES);
}

/*
other potentially useful methods of the stepper motor class:
setSpeedProfile
calcStepsForRotation
getTimeForMove
startMove
startRotate
getStepsCompleted
getStepsRemaining
stop
*/