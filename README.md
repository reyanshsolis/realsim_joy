# RealSim Joy Interface

## TAKES JOY INPUT AND CONVERT TO REQUIRED MESSAGE INFORMATION IN CUSTOM MESSAGE FORMAT
## CUSTOM MESSAGE TYPE: joy_cmd

**\[CONTROL\] [NORMALISED VALUES between -1 t0 +1]**

    DOUBLE:
        throttle
        yaw
        pitch
        roll

**[SAFETY]**

    BOOL: 
        arm [Arming/Diarming Request]

**[MODE]**

    INT: 
        mode [1- OFFBOARD with RC_overide, 2- GUIDED/OFFBOARD, 3- MANUAL]

**[ACTION]**

    BOOL: 
        takeoff_request
        land_request

**[MOVEMENT]**

    BOOL: 
        move_to_next_forward
        move_to_next_right
        move_to_next_back
        move_to_next_left
## ASSIGNED JOY CONTROL FOR GENERIC JOYSTICK:

AXES:

    [LEFT VERTICAL] 0- THROTTLE
    [LEFT HORIZONTAL] 1- YAW
    [RIGHT VERTICAL] 3- PITCH
    [RIGHT HORIZONTAL] 4- ROLL

BUTTONS:

    L1 - SAFETY_SELECT
    L2 - MODE_SELECT
    R1 - ACTION_SELECT
    R2 - MOVEMENT_SELECT
    1- BUTTON_1
    2- BUTTON_2
    3- BUTTON_3
    4- BUTTON_4

L1+ (...): 1- ARM REQUEST 2- DISARM REQUEST\
L2+ (...): 1- OFFBOARD_RC 2- OFFBOARD 3- MANUAL\
R1+ (...): 1- TAKEOFF REQUEST 2- LAND REQUEST\
R2+ (...): 1- FORWARD 2- RIGHT 3- BACK 4-LEFT

----------



