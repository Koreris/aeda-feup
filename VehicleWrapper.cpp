/*
 * VehicleWrapper.cpp
 *
 *  Created on: 23/12/2016
 *      Author: MDA
 */

#include "VehicleWrapper.h"

bool VehicleWrapper::operator<(const VehicleWrapper &vw) const
{
	return (*vhc) < *(vw.vhc);
}
