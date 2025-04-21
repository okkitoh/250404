
#include "Phone.h"
#include <iostream>
#include <stdio.h>



Phone::Phone(std::string Name, int SerialNumber)
	: BatteryLife(15), InternalTemperature(30.0),
	timerActive(false), timer(0.0),
	ringActive(false), ringState(FLAG_NONE), ringTimer(0.0)
{
	// this is a pointer to Object's "scope"
	// -> is a dereferencing operation
	// . is a access operation
	// this.Name would be invalid as 'this' holds an address
	// and -> is like saying (*this).Name where * in this context means dereference (get the value held at this address)
	this->Name = Name;
	this->SerialNumber = SerialNumber;
}
void Phone::Update(double elapsedTime)
{
	decrementTimer(elapsedTime);
	ringAlarm(elapsedTime);
}
std::vector<std::string> Phone::PrintInformation()
{
	char BUFF[256];
	std::vector<std::string> drawLines;
	drawLines.push_back("");
	drawLines.push_back("");
	drawLines.push_back("");
	drawLines.push_back("");
	drawLines.push_back("");
	sprintf_s(BUFF, sizeof(BUFF), "  %.2f         %c ", timer, ringState & FLAG_HI ? ')' : 32);
	drawLines.push_back(BUFF);
	sprintf_s(BUFF, sizeof(BUFF), " %c       %c        ", 179, ringState & (FLAG_MID | FLAG_HI) ? 191 : 32);
	drawLines.push_back(BUFF);
	sprintf_s(BUFF, sizeof(BUFF), " %c%c%c%c %c           ", 179, (ringState == FLAG_NONE ?  176 : 178), ringState == FLAG_NONE ? 177 : 178, 179, ringState != FLAG_NONE ? 248 : 32);
	drawLines.push_back(BUFF);
	drawLines.push_back(" |::|             ");
	sprintf_s(BUFF, sizeof(BUFF), " %c%c%c%c             ", 192, 196, 196, 217);
	drawLines.push_back(BUFF);
/*	std::cout << "This is a: " << Name << std::endl;
	std::cout << "Serial Number is: " << SerialNumber << std::endl;
	std::cout << "Temperature is: " << InternalTemperature << std::endl;*/
	return drawLines;
}
void Phone::PrintBatteryLife()
{
	std::cout << BatteryLife << std::endl;
}
void Phone::TakePicture()
{
	std::cout << "Click" << std::endl;
}
void Phone::SetFactoryDefaults(float DefaultBatteryLife, float DefaultTemperature)
{
	BatteryLife = DefaultTemperature;
	InternalTemperature = DefaultTemperature;
}
void Phone::ChargeBattery(int charge)
{
	BatteryLife = std::min(BatteryLife + charge, 100.f);
}
void Phone::MakeCall()
{
	if (BatteryLife < 5.f)
	{
		std::cout << "Low battery, please charge!" << std::endl;
		return;
	}
	std::cout << "Making a call" << std::endl;
	BatteryLife = std::max(BatteryLife - 5.f, 0.f);
}
int Phone::GetSerialNumber()
{
	return SerialNumber;
}
void Phone::SetSerialNumber(int SerialNumber)
{
	this->SerialNumber = SerialNumber;
}
std::string Phone::GetName()
{
	return Name;
}
void Phone::SetName(std::string Name)
{
	this->Name = Name;
}
void Phone::SetTimer(double timer)
{
	this->timer = timer;
	this->timerActive = true;
	this->ringState = FLAG_NONE;
	this->ringTimer = 0.0;
	this->ringActive = false;
}
void Phone::decrementTimer(double elapsedTime)
{
	if (!this->timerActive) return;

	this->timer -= elapsedTime;
	if (this->timer <= 0.0)
	{
		// yeah.. not a good way to do sequential animation but works in a pinch
		this->timer = 0.0;
		this->timerActive = false;
		this->ringActive = true;
		this->ringState = FLAG_LOW;
		this->ringTimer = 0.00;
	}
}
void Phone::ringAlarm(double elapsedTime)
{
	if (!this->ringActive) return;
	
	this->ringTimer += elapsedTime;
	int trunc = (int)this->ringTimer % 3;
	this->ringState = trunc == 0 ? 1 : pow(2, short(trunc));
	if (this->ringTimer >= 9.0)
	{
		this->ringActive = false;
		this->ringState = FLAG_NONE;
		this->ringTimer = 0.0;
	}
}