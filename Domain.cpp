#include "Domain.h"
//#include "strptime.h"
#include <string>
#include <cstring>
#include <sstream>
#include <stdlib.h>

using namespace std;

Footage::Footage(const std::string& title, const std::string& location, const std::string& timeOfCreation, const int& timesAccesed, const std::string& footagePreview) {
	this->title = title;
	this->location = location;

	struct tm TimeOfCreation;
	char* timeOfCreationPointerChar = new char[timeOfCreation.size() + 1];
	strcpy(timeOfCreationPointerChar, timeOfCreation.c_str());
	strptime(timeOfCreationPointerChar, "%m-%d-%Y", &TimeOfCreation);
	TimeOfCreation.tm_mon += 1;
	TimeOfCreation.tm_year += 1900;
	this->timeOfCreation = TimeOfCreation;

	this->timesAccesed = timesAccesed;
	this->footagePreview = footagePreview;
}

std::string Footage::beginOfHtml()
{
	std::string html = "";
	html += "<!DOCTYPE html>\n<html>\n<head>\n<title>Recordings</title>\n</head>\n<body>\n<table border=\"1\">\n<tr>\n<td>Title</td>\n";
	html += "<td>Location</td>\n<td>Date of creation</td>\n<td>Times accesed</td>\n<td>Footage preview</td>\n</tr>";
	return html;
}

std::string Footage::endOfHtml()
{
	std::string html = "";
	html += "</table>\n</body>\n</html>";
	return html;
}

std::string Footage::writeToHtml()
{
	std::string html = "<tr>\n";
	html += "<td>";
	html += this->title;
	html += "</td>\n";

	html += "<td>";
	html += this->location;
	html += "</td>\n";
	
	html += "<td>";
	struct tm time = this->timeOfCreation;
	char timeOfCreation[12];
	char partOfTime[5];
	sprintf(partOfTime,"%d",time.tm_mon);
	//string partOfTime;

	if (time.tm_mon < 10) {
		strcpy(timeOfCreation, "0");
		strcat(timeOfCreation, partOfTime);
	}
	else
		strcpy(timeOfCreation, partOfTime);

	strcat(timeOfCreation, "-");

	sprintf(partOfTime,"%d",time.tm_mday);
	//itoa(time.tm_mday, partOfTime, 10);
	if (time.tm_mday < 10)
		strcat(timeOfCreation, "0");
	strcat(timeOfCreation, partOfTime);

	strcat(timeOfCreation, "-");

	sprintf(partOfTime,"%d",time.tm_year);	
	//itoa(time.tm_year, partOfTime, 10);
	strcat(timeOfCreation, partOfTime);

	html += timeOfCreation;
	html += "</td>\n";
	
	html += "<td>";
	char timesAccesed[10];
	sprintf(timesAccesed,"%d",this->timesAccesed);
	//itoa(this->timesAccesed, timesAccesed,10);
	html += timesAccesed;
	html += "</td>\n";
	
	html += "<td><a href=\"https://www.youtube.com/watch?v=iLBBRuVDOo4 \">";
	html += this->footagePreview;
	html += "</a></td>\n";

	html += "</tr>";
	return html;
}

bool Footage::operator==(const Footage& footage) {
	return (this->title.compare(footage.title) == 0) ? true : false;
}

Footage& Footage::operator=(const Footage& footage)
{
	this->title = footage.title;
	this->timeOfCreation = footage.timeOfCreation;
	this->timesAccesed = footage.timesAccesed;
	this->location = footage.location;
	this->footagePreview = footage.footagePreview;
	return *this;
}

std::ostream& operator<<(std::ostream& outputStream, const Footage& footage)
{
	const struct tm time = footage.timeOfCreation;
	char timeOfCreation[12];
	    char partOfTime[5];
		sprintf(partOfTime,"%d",time.tm_mon);
//	    itoa(time.tm_mon, partOfTime, 10);
	    if (time.tm_mon < 10) {
		    strcpy(timeOfCreation, "0");
		    strcat(timeOfCreation, partOfTime);
	    }
	    else
		    strcpy(timeOfCreation, partOfTime);

	    strcat(timeOfCreation, "-");
		
		sprintf(partOfTime,"%d",time.tm_mday);
	    //itoa(time.tm_mday, partOfTime, 10);
    	if (time.tm_mday < 10)
	    	strcat(timeOfCreation, "0");
	    strcat(timeOfCreation, partOfTime);

	    strcat(timeOfCreation, "-");

	    sprintf(partOfTime,"%d",time.tm_year);
		//itoa(time.tm_year, partOfTime, 10);
	    strcat(timeOfCreation, partOfTime);

	outputStream << footage.title << ","<< footage.location << ","<< timeOfCreation << ","<< footage.timesAccesed << ","<< footage.footagePreview;
	return outputStream;
}

std::istream& operator>>(std::istream& inputStream, Footage& footage) {
	std::string line;
	std::getline(inputStream, line);
	
	if (line == "")
		return inputStream;

	char lineChar[200];
	strcpy(lineChar, line.c_str());

	char* footageArguments;
	footageArguments = strtok(lineChar, ",");
	footage.title = footageArguments;

	footageArguments = strtok(NULL, ",");
	footage.location = footageArguments;

	struct tm TimeOfCreation;
	footageArguments = strtok(NULL, ",");
	strptime(footageArguments, "%m-%d-%Y", &TimeOfCreation);
	TimeOfCreation.tm_mon += 1;
	TimeOfCreation.tm_year += 1900;
	
	footage.timeOfCreation = TimeOfCreation;

	footageArguments = strtok(NULL, ",");
	footage.timesAccesed = atoi(footageArguments);

	footageArguments = strtok(NULL, ",");
	footage.footagePreview = footageArguments;

	return inputStream;
}
