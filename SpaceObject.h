
#ifndef SpaceObject_h
#define SpaceObject_h

class SpaceObject{
public:
	bool isAsteroid;
	//X axis position
	double x;
	//Y axis position
	double y;
	//X axis speed
	double vx;
	//Y axis speed
	double vy;
	//Object mass
	double m;
	//Default constructor
	SpaceObject(double, double, double, double, double);
};

#endif