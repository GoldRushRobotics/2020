#ifndef __LIGHT_SENSOR_H__
#define __LIGHT_SENSOR_H__

class LightSensor {
private:
	int _pin = -1;
public:
	void attach(int);
	int read();
};

#endif