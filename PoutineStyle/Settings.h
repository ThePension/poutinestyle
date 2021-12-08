#pragma once

class Settings
{
	public:
		Settings();
		~Settings();

		int getLevel();
		bool getShowMetaData();
		int getSensibility();
		int getDifficulty();
		int getVolume();

		void setLevel(int level);
		void setShowMetaData(bool showMetaData);
		void setSensibility(int sensibility);
		void setDifficulty(int difficulty);
		void setVolume(int volume);

	private:
		int level;
		bool showMetaData;
		int sensibility;
		int difficulty;
		int volume;
};