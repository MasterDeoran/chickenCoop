#ifndef __TIMENTP_H__
#define __TIMENTP_H__

#include <WiFiUdp.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include "../manager/WLANManager.hpp"

extern void timeSynchroLoop();

#endif;