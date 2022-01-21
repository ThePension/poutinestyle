#include "Settings.h"

Settings::Settings()
{
	this->level = 0;
	this->showMetaData = false;
	this->sensibility = 5;
	this->difficulty = 1;
	this->volume = 75;
}

Settings::~Settings(){}

int Settings::getLevel()
{
	return this->level;
}

bool Settings::getShowMetaData()
{
	return this->showMetaData;
}

int Settings::getSensibility()
{
	return this->sensibility;
}

int Settings::getDifficulty()
{
	return this->difficulty;
}

int Settings::getVolume()
{
	return this->volume;
}

void Settings::setLevel(int level)
{
	this->level = level;
}

void Settings::setShowMetaData(bool showMetaData)
{
	this->showMetaData = showMetaData;
}

void Settings::setSensibility(int sensibility)
{
	this->sensibility = sensibility;
}

void Settings::setDifficulty(int difficulty)
{
	this->difficulty = difficulty;
}

void Settings::setVolume(int volume)
{
	this->volume = volume;
}