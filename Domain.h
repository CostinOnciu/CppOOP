#pragma once
#include <string>
#include <string.h>
#include <stdlib.h>
#include <cstring>
#include <time.h>
#include <iostream>
#include <fstream>
#include <ostream>
#include <istream> 

class Footage {
	private:
		std::string title;
		std::string location;
		struct tm timeOfCreation;
		int timesAccesed;
		std::string footagePreview;
	public:
		Footage(){}
		Footage(const std::string& title, const std::string& location, const std::string& timeOfCreation, const int& timesAccesed, const std::string& footagePreview);
		std::string getTitle() const {
			return title;
		}
		std::string getLocation() const {
			return location;
		}
		struct tm getTimeOfCreation() const {
			return timeOfCreation;
		}
		int getTimesAccesed() const {
			return timesAccesed;
		}
		std::string getFootagePreview() const {
			return footagePreview;
		}

		std::string beginOfHtml();
		std::string endOfHtml();
		std::string writeToHtml();

		friend std::ostream& operator<<(std::ostream& outputStream, const Footage& footage);
		friend std::istream& operator>>(std::istream& inputStream,  Footage& footage);

		bool operator==(const Footage& footage);
		Footage& operator=(const Footage& footage);
};