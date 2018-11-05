#include <iostream>
using namespace std;

const double gravity = 6.674e - 5;
const double time_interval = 0.1;
const double minimal_distance = 2.0;
const double width = 200.0;
const double height = 200.0;
const double average_mass = 1000;
const double mass_standard_deviation = 50;

auto distance_between_elements(SpaceObject n1, SpaceObject n2) {
	auto first_component;
	auto second_component;

	first_component = pow(n1.x - n2.x, 2);
	second_component = pow(n1.y - n2.y, 2);

	return sqrt(first_component + second_component);
}

//Only used if distance is greater than 2 units
vector<double> normal_movement(SpaceObject n1, SpaceObject n2) {
	auto slope;
	auto angle;
	auto distance_between_n1_n2 = distance_between_elements(n1, n2);
	auto n1_x_axis_force;
	auto n1_y_axis_force;
	auto n2_x_axis_force;
	auto n2_y_axis_force;
	<vector>(double) results;

	//First, we have to calculate the slope
	slope = (n1.y - n2.y) / (n1.x - n1.y);

	//Check for slope correctness
	if ((slope > 1) || (slope < -1)) {
		slope = slope - ( ((int) slope) / 1);
	}

	//Slope angle calculation
	angle = atan(slope);

	//Second, we have to calculate forces
	n1_x_axis_force = ((gravity * n1.m * n2.m) / (distance_between_n1_n2)) * cos(angle);
	n1_y_axis_force = ((gravity * n1.m * n2.m) / (distance_between_n1_n2)) * sin(angle);

	if (n1_x_axis_force > 200) n1_x_axis_force = 200;
	if (n1_y_axis_force > 200) n1_y_axis_force = 200;

	n2_x_axis_force = -n1_x_axis_force;
	n2_y_axis_force = -n1_y_axis_force;

	results[0] = n1_x_axis_force;
	results[1] = n1_y_axis_force;
	results[2] = n2_x_axis_force;
	results[3] = n2_y_axis_force;

	return results;
}

auto change_element_position(SpaceObject *n1, vector<double>& x_axis_forces, vector<double>& y_axis_forces) {
	auto accel_x_axis;
	auto accel_y_axis;
	auto x_axis_speed;
	auto y_axis_speed;
	auto x_axis_new_pos;
	auto y_axis_new_pos;

	for(auto &force : x_axis_forces) {
		accel_x_axis += force / n1.m;
	}

	for(auto &force : y_axis_forces) {
		accel_y_axis += force / n1.m;
	}

	x_axis_speed = n1.vx + (accel_x_axis * time_interval);
	y_axis_speed = n1.vy + (accel_y_axis * time_interval);

	x_axis_new_pos = n1.x + (x_axis_speed * time_interval);
	y_axis_new_pos = n1.y + (y_axis_speed * time_interval);

	if (x_axis_new_pos <= 0) {
		x_axis_new_pos = 2;
		n1.vx *= -1;
	}
	if (y_axis_new_pos <= 0) {
		y_axis_new_pos = 2;
		n1.vy *= -1;
	}
	if (x_axis_new_pos >= width) {
		x_axis_new_pos = width - 2;
		n1.vx *= -1;
	}
	if (y_axis_new_pos >= width) {
		y_axis_new_pos = width - 2;
		n1.vy *= -1;
	}

	n1.vx = x_axis_speed;
	n1.vy = y_axis_speed;
	n1.x = x_axis_new_pos;
	n1.y = y_axis_new_pos;
}

//Take care of planet colliding...
auto collision_handling(SpaceObject n1, SpaceObject n2) {
	if (n1.isAsteroid) {
		n1.vx = n2.vx;
		n1.vy = n2.vy;
	}
	if (n2.isAsteroid) {
		n2.vx = n1.vx;
		n2.vy = n1.vy;
	}
}