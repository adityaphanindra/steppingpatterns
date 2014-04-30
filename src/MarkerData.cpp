#include "MarkerData.h"
#include <string>

Marker::MarkerData::MarkerData()
{
}

Marker::MarkerData::MarkerData(const MarkerData & copy) : 
	_position(copy._position),
	_timestamp(copy._timestamp)
{
}

Marker::Position Marker::MarkerData::getPosition()
{
	this->_mutexLock.lock();
	Marker::Position position = this->_position;
	this->_mutexLock.unlock();
	return position;
}
void Marker::MarkerData::setPosition(Position position)
{
	this->_mutexLock.lock();
	this->_position = position;
	this->_mutexLock.unlock();
}
void Marker::MarkerData::setPositionX(float x)
{
	this->_mutexLock.lock();
	this->_position.x = x;
	this->_mutexLock.unlock();
}
void Marker::MarkerData::setPositionY(float y)
{
	this->_mutexLock.lock();
	this->_position.y = y;
	this->_mutexLock.unlock();
}
void Marker::MarkerData::setPositionZ(float z)
{
	this->_mutexLock.lock();
	this->_position.z = z;
	this->_mutexLock.unlock();
}

void Marker::MarkerData::setTimestamp(std::string timestamp)
{
	this->_timestamp = timestamp;
}

std::string Marker::MarkerData::getTimestamp()
{
	return this->_timestamp;
}

std::string Marker::MarkerData::getString()
{
	return std::to_string(this->getPosition().x) + "\t" + std::to_string(this->getPosition().y) + "\t" + std::to_string(this->getPosition().z);
}

bool Marker::MarkerData::isValid()
{
	if((this->_position.x != this->_position.x) || (this->_position.y != this->_position.y) || (this->_position.z != this->_position.z))
		return false;
	else return true;
}


