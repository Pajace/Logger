#include <stdexcept>
using namespace std;

#ifndef __LOGGER_EXCEPTION_H__
#define __LOGGER_EXCEPTION_H__


class CannotOpenLogFileException : public runtime_error {
public:
	CannotOpenLogFileException():runtime_error("Logger: CANNOT Open the log file."){};
};

class LogFileIsNotOpenException : public runtime_error {
public:
	LogFileIsNotOpenException():runtime_error("Logger: Log file wasn't open. Please check the dirctory of log file."){};
};

#endif /* __LOGGER_EXCEPTION_H__ */
