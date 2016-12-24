/*
 * VehicleWrapper.h
 *
 *  Created on: 23/12/2016
 *      Author: MDA
 */

#ifndef _VEHICLEWRAPPER_H_
#define _VEHICLEWRAPPER_H_

class VehicleWrapper
{
public:
	Vehicle* vhc;

	VehicleWrapper (Vehicle* v):vhc(v){};
	~VehicleWrapper ();
	bool operator<(const VehicleWrapper &vw) const;
	Vehicle* operator->() {return vhc;}
};

#endif /*_VEHICLEWRAPPER_H_*/
