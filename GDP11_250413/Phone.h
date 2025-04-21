#pragma once

#include <iostream>
#include <string>
#include <vector>



const short FLAG_NONE = 0;
const short FLAG_LOW = 1 << 0;
const short FLAG_MID = 1 << 1;
const short FLAG_HI = 1 << 2;



class Phone
{
public:
	Phone(std::string Name, int SerialNumber);
	void Update(double elapsedTime);
	std::vector<std::string> PrintInformation();

	void PrintBatteryLife();
	void TakePicture();
	void SetFactoryDefaults(float DefaultBatteryLife, float DefaultTemperature);
	void ChargeBattery(int charge);
	void MakeCall();
	int GetSerialNumber();
	void SetSerialNumber(int SerialNumber);
	std::string GetName();
	void SetName(std::string Name);	
	void SetTimer(double timer);
private:
	void decrementTimer(double elapsedTime);
	void ringAlarm(double elapsedTime);
	//void decrementRinger(double elaspedTime);

	std::string Name;
	int SerialNumber;
	float BatteryLife;
	float InternalTemperature;

	bool timerActive;
	double timer;

	bool ringActive;
	double ringTimer;
	short ringState;
};

