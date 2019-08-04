#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>


using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    	// TODO: Request a service and pass the velocities to it to drive the robot
	ROS_INFO_STREAM("Driving the robot to the target.");
	
	ball_chaser::DriveToTarget srv;
    	srv.request.linear_x = lin_x;
    	srv.request.angular_z = ang_z;
    	
	if (!client.call(srv)) {
	    	ROS_ERROR("Failed to call service DriveToTarget.");
	}
}



// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    	int white_pixel = 255;

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
	
	bool found_ball = false;
	
	int row = 0;
	int step = 0;
	int i = 0;

	//int height = img.height;
    	//int step = img.step;

    	float x = 0.0;
    	float z = 0.0;
  	
	for (row = 0; row < img.height && found_ball == false; row++)
    	{
        	for (step = 0; step < img.step && found_ball == false; ++step)
        	{   
            		i = (row*img.step)+step;
            		//ROS_INFO("row: %d, step: %d, i: %d", row, step, i);
            		if (img.data[i] == white_pixel && img.data[i + 1] == white_pixel && img.data[i + 2] == white_pixel)
			{   
				found_ball = true;
				//ROS_INFO("row: %d, step: %d, i: %d", row, step, i);
				
			 }
		}
    	}	

    	 if (found_ball)
    	{
        // Then, identify if this pixel falls in the left, mid, or right side of the image
        	int imgThird = img.width/3;
        	int col = step/3;
        //ROS_INFO("col: %d", col);
        	if (col < imgThird) 
        	{
        	    drive_robot(0.0, -0.5);
            //ROS_INFO("LEFT");
        	} 
        	else if (col >= imgThird && col < 2*imgThird)
        	{
        	    drive_robot(0.5, 0.0);
            //ROS_INFO("MID");
        	}
        	else if (col >= 2*imgThird)
        	{
            	drive_robot(0.1, 0.5);
            //ROS_INFO("RIGHT");
        	}
        // Depending on the white ball position, call the drive_bot function and pass velocities to it
    	}
	else
	{
		drive_robot(x, z);
	}
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}
