#ifndef __LOGGER_H__
#define __LOGGER_H__
#include <string>
#include <fstream>
#include <Windows.h>

class Logger
{
public:
	Logger(std::string logFileName, std::string className);
	~Logger();
	void LogAlert(std::string);
	void LogError(std::string);
	void LogInfo(std::string);
	void LogDebug(std::string);
	void setDebug(bool);
	void setInfo(bool);

private:
	std::ofstream logFile;
	bool isLogInfo;
	bool isLogDebug;
	std::string className;

	CRITICAL_SECTION g_cs;
	std::string getTimeString() const;
	void logMsg(std::string msg);
};

#endif // __LOGGER_H__