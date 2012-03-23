#include "Logger.h"
#include "LoggerException.h"
#include <stdexcept>
#include <Windows.h>
#include <sstream>
#include <iomanip>

const static std::string LOGGER_ALERT = "[ALERT]";
const static std::string LOGGER_ERROR = "[ERROR]";
const static std::string LOGGER_INFO  = "[INFO ]";
const static std::string LOGGER_DEBUG = "[DEBUG]";
static SYSTEMTIME systemTime = {0};


Logger::Logger(std::string logFileName, std::string className) {
	::InitializeCriticalSection(&g_cs);
	setDebug(false);
	setInfo(false);
	this->className = className;
	logFile.open(logFileName, std::ofstream::app);
	if (!logFile.is_open())
		throw CannotOpenLogFileException();	
}

Logger::~Logger(void) {
	::DeleteCriticalSection(&g_cs);
	logFile.close();
}

std::string Logger::getTimeString() const {
	stringstream ss;
	ss.str("");
	ss.clear();
	GetLocalTime(&systemTime);
	ss << std::setw(4) << systemTime.wYear << "/" <<
		setw(2) << setfill('0') << systemTime.wMonth << "/" <<
		setw(2) << setfill('0') << systemTime.wDay << " " <<
		setw(2) << setfill('0') << systemTime.wHour << ":" <<
		setw(2) << setfill('0') << systemTime.wMinute  << ":" <<
		setw(2) << setfill('0') << systemTime.wSecond  << "." <<
		setw(3) << setfill('0') << systemTime.wMilliseconds;
	std::string timeString(ss.str());
	return timeString;
}

void Logger::logMsg(std::string msg) {
	if(logFile.is_open()) {
		::EnterCriticalSection(&g_cs);
		std::string logMsg = "";
		logMsg.append(this->getTimeString());
		logMsg.append("-");
		logMsg.append(this->className);
		logMsg.append("-");
		logMsg.append(msg);
		logMsg.append("\n");
		::LeaveCriticalSection(&g_cs);
	} else
		throw LogFileIsNotOpenException();
}

void Logger::LogAlert(std::string msg) {
	string message(LOGGER_ALERT);
	message.append(msg);
	logMsg(message);
}
void Logger::LogError(std::string msg) {
	string message(LOGGER_ERROR);
	message.append(msg);
	logMsg(message);	
}
void Logger::LogInfo(std::string msg) {
	string message(LOGGER_INFO);
	message.append(msg);
	logMsg(message);		
}
void Logger::LogDebug(std::string msg) {
	string message(LOGGER_DEBUG);
	message.append(msg);
	logMsg(message);		
}
void Logger::setDebug(bool _isLogDebug) {
	this->isLogDebug = _isLogDebug;
}
void Logger::setInfo(bool _isLogInfo) {
	this->isLogInfo = _isLogInfo;
}