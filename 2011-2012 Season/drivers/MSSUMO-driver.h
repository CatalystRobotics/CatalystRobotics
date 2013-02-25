/*!@addtogroup Mindsensors
 * @{
 * @defgroup MSSUMO Sumo Eyes Sensor
 * Mindsensors Sumo Eyes Sensor
 * @{
 */

/*
 * $Id: MSSUMO-driver.h 77 2011-11-30 19:03:16Z xander $
 */

#ifndef __MSSUMO_H__
#define __MSSUMO_H__
/** \file MSSUMO-driver.h
 * \brief Mindsensors Sumo Eyes Sensor driver
 *
 * MSSUMO-driver.h provides an API for the Mindsensors Sumo Eyes sensor.
 *
 * Changelog:
 * - 0.1: Initial release
 *
 * Credits:
 * - Big thanks to Mindsensors for providing me with the hardware necessary to write and test this.
 *
 * License: You may use this code as you wish, provided you give credit where its due.
 *
 * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 2.00 AND HIGHER.
 * \author Xander Soldaat (mightor_at_gmail.com)
 * \date 30 October 2011
 * \version 0.1
 * \example MSSUMO-test1.c
 */

#pragma systemFile

#ifndef __COMMON_H__
#include "common.h"
#endif

// This ensures the correct sensor types are used.
TSensorTypes LRType = sensorLightInactive;
TSensorTypes SRType = sensorLightActive;

typedef enum {
  MSSUMO_NONE = 0,
  MSSUMO_FRONT = 1,
  MSSUMO_LEFT = 2,
  MSSUMO_RIGHT = 3
} tObstacleZone;

tObstacleZone MSSUMOreadZone(tSensors link);
void MSSUMOsetShortRange(tSensors link);
void MSSUMOsetLongRange(tSensors link);

/**
 * Get the raw value from the sensor
 * @param link the MSSUMO port number
 * @return raw value of the sensor
 */
tObstacleZone MSSUMOreadZone(tSensors link) {
  int sensordata = 0;

  sensordata = SensorValue[link];

 	if ( sensordata > 30 && sensordata < 36 )
 	{
	  // obstacle is on left
    return (MSSUMO_LEFT);
	}
	else if ( sensordata > 63 && sensordata < 69 )
	{
	  // obstacle is on right
    return (MSSUMO_RIGHT);
	}
	else if ( sensordata >= 74 && sensordata <= 80 )
	{
	  // obstacle is in front.
    return (MSSUMO_FRONT);
	}
	else
	{
	  return (MSSUMO_NONE);
	}
}


/**
 * Set the range of the sensor to short range, this is done
 * by configuring the sensor as sensorLightActive.
 * @param link the MSSUMO port number
 */
void MSSUMOsetShortRange(tSensors link) {
  if (SensorType[link] != SRType)
    SetSensorType(link, SRType);
}


/**
 * Set the range of the sensor to long range, this is done
 * by configuring the sensor as sensorLightInactive
 * @param link the MSSUMO port number
 */
void MSSUMOsetLongRange(tSensors link) {
  if (SensorType[link] != LRType)
    SetSensorType(link, LRType);
}


#endif // __MSSUMO_H__

/*
 * $Id: MSSUMO-driver.h 77 2011-11-30 19:03:16Z xander $
 */
/* @} */
/* @} */
