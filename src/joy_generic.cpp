/*
TAKES JOY INPUT AND CONVERT TO REQUIRED MESSAGE INFORMATION IN CUSTOM MESSAGE FORMAT
-------------------------------------------------------------------
CUSTOM MESSAGE TYPE: joy_cmd

[CONTROL]
[NORMALISED VALUES between -1 t0 +1]
DOUBLE:	throttle
		yaw
		pitch
		roll

[SAFETY]
BOOL: 	arm			[Arming/Diarming Request]

[MODE]
INT:	mode [1- OFFBOARD with RC_overide, 2- GUIDED/OFFBOARD, 3- MANUAL]

[ACTION]
BOOL: 	takeoff_request
		land_request

[MOVEMENT]
BOOL:	move_to_next_forward
		move_to_next_right
		move_to_next_back
		move_to_next_left
--------------------------------------------------------------------
ASSIGNED JOY CONTROL:
AXES:
[LEFT VERTICAL]		0- THROTTLE
[LEFT HORIZONTAL]	1- YAW
[RIGHT VERTICAL]	3- PITCH
[RIGHT HORIZONTAL]	4- ROLL

BUTTONS:
L1 -	SAFETY_SELECT
L2 -	MODE_SELECT
R1 -	ACTION_SELECT
R2 -	MOVEMENT_SELECT
1-		BUTTON_1
2-		BUTTON_2
3-		BUTTON_3
4-		BUTTON_4

L1+ (...): 1- ARM REQUEST 	2- DISARM REQUEST
L2+ (...): 1- OFFBOARD_RC	2- OFFBOARD 	3- MANUAL
R1+ (...): 1- TAKEOFF REQUEST 	2- LAND REQUEST
R2+ (...): 1- FORWARD 2- RIGHT 3- BACK 4-LEFT

--------------------------------------------------------------------

CONFIGURE YOUR GENERIC JOY:
	SETS TO SETUP JOY AND GET THE MAX MIN VALES GIVEN IN THE README

CODE DEVELOPED AND MAINTAINED BY RISHABH SINGH [www.rishabh-singh.in]
*/

#include <ros/ros.h>
#include <sensor_msgs/Joy.h>
#include <realsim_joy/joy_msg.h>

realsim_joy::joy_msg arm;
realsim_joy::joy_msg arm;
realsim_joy::joy_msg arm;

/*---------------- CONFIGURE JOY ---------------------*/
// ------------ DEFINE AXES AND BUTTONS ------------- //
#define axes_throttle 
#define axes_yaw 
#define axes_pitch 
#define axes_roll
#define button_safety_select
#define button_mode_select
#define button_action_select
#define button_movement_select

#define button_1
#define button_2
#define button_3
#define button_4

// --- DEFINE THEIR MAX VALUE WITH SIGN TO NORMALISE ---//
#define throttle_max 3627 
#define yaw_max 3627 
#define pitch_max 3627 
#define roll_max 3627
#define button_safety_select_max 1
#define button_mode_select_max 1
#define button_action_select_max 1
#define button_movement_select_max 1

#define button_1_max 1
#define button_2_max 1
#define button_3_max 1
#define button_4_max 1
/*-----------------------------------------------------*/

/*---------------- JOY MESSAGE ------------------------*/

realsim_joy::joy_msg joy_msg_norm;

//type - double
joy_msg_norm.throttle_norm = 0.0;
joy_msg_norm.yaw_norm = 0.0;
joy_msg_norm.pitch_norm = 0.0;
joy_msg_norm.roll_norm = 0.0;

//type - int
joy_msg_norm.mode = 0;

//type - bool
joy_msg_norm.arm_request = 0;
joy_msg_norm.normal_control = 1;

joy_msg_norm.takeoff_request = 0;
joy_msg_norm.land_request = 0;

joy_msg_norm.move_to_next_forward = 0;
joy_msg_norm.move_to_next_right = 0;
joy_msg_norm.move_to_next_left = 0;
joy_msg_norm.move_to_next_back = 0;
/* ---------------------------------------------------- */


int joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{	
	throttle_norm = (double)joy->axes[axes_throttle]/throttle_max;
	yaw_norm = (float)joy->axes[axes_yaw]/yaw_max;
	pitch_norm = (double)joy->axes[axes_pitch]/pitch_max;
	roll_norm = (double)joy->axes[axes_roll]/roll_max;

	safety_select = (bool)(joy->button[button_safety_select]/button_safety_select_max);
	mode_select = (bool)(joy->button[button_mode_select]/button_mode_select_max);
	action_select = (bool)(joy->button[button_action_select]/button_action_select_max);
	movement_select = (bool)(joy->button[button_movement_select]/button_movement_select_max);

	bool button_1_rc = (bool)(joy->button[button_1]/button_1_max);
	bool button_2_rc = (bool)(joy->button[button_2]/button_2_max);
	bool button_3_rc = (bool)(joy->button[button_3]/button_3_max);
	bool button_4_rc = (bool)(joy->button[button_4]/button_4_max);

	if(safety_select == 1){
		joy_msg_norm.normal_control = 0;               											
		if(button_1_rc == 1){
			joy_msg_norm.arm_request = 1;
		}
		if(button_2_rc == 1){
			joy_msg_norm.arm_request = 0;
		}
	}

	else if(mode_select == 1){
		joy_msg_norm.normal_control = 0;               											
		if(button_1_rc == 1){
			joy_msg_norm.mode = 1;
		}
		else if(button_2_rc == 1){
			joy_msg_norm.mode = 2;
		}
		else if(button_3_rc == 1){
			joy_msg_norm.mode = 3;
		}
	}

	else if(action_select == 1){
		joy_msg_norm.normal_control = 0;               											
		if(button_1_rc == 1){
			joy_msg_norm.takeoff_request = 1;
			joy_msg_norm.land_request = 0;
		}
		else if(button_2_rc == 1){
			joy_msg_norm.takeoff_request = 0;
			joy_msg_norm.land_request = 1;
		}
	}

	else if(movement_select == 1){
		joy_msg_norm.normal_control = 0;               											
		if(button_1_rc == 1){
			joy_msg_norm.move_to_next_forward = 1;
		}
		else{
			joy_msg_norm.move_to_next_forward = 0;
		}

		if(button_2_rc == 1){
			joy_msg_norm.move_to_next_right = 1;
		}
		else{
			joy_msg_norm.move_to_next_right = 0;
		}

		if(button_3_rc == 1){
			joy_msg_norm.move_to_next_back = 1;
		}
		else{
			joy_msg_norm.move_to_next_back = 0;
		}

		if(button_4_rc == 1){
			joy_msg_norm.move_to_next_left = 1;
		}
		else{
			joy_msg_norm.move_to_next_left = 0;
		}
	}

	else{
		joy_msg_norm.normal_control = 1;
	}

	// ROS_INFO("%f",&joy_vz);
	// ROS_INFO("%d",&axes_mode1);
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "joy_input_conversion");
  	ros::NodeHandle n;

	ros::Rate rate(20.0);
	
	ros::Subscriber joy_sub_manual = n.subscribe<sensor_msgs::Joy>("/joy", 100, &joyCallback);
	ros::Publisher joy_convt_pub = nh.advertise<realsim_joy::joy_msg>("/realsim_joy/joy_norm", 10);

	ROS_INFO("INITIALISING...REALSIM JOY NODE");
	for(int i=0; i<100; i++){
		ros::spinOnce();
		ros::Duration(0.01).sleep();
	}

	while(ros::ok()){
		joy_convt_pub.publish(joy_msg_norm);
		ros::spinOnce();
	}
	
	return 0;  
}