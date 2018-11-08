
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
	//Who collides with this asteroid
	int collides;
	//Default constructor
	SpaceObject(double, double, double, double, double);
};
SpaceObject::SpaceObject(double x1, double y1, double vx1, double vy1, double m1){
	x = x1;
	y = y1;
	vx = vx1;
	vy = vy1;
	m = m1;
	collides = -1;
}
#endif
