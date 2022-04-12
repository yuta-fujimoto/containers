#ifndef TIME_HPP
#define TIME_HPP

#include <ctime>
class timer
{
private:
	double checkpoint;
public:
	timer();
	~timer();
	timer(timer const &rhs);
	timer &operator=(timer const &rhs);
	void record(const char *msg);
	void start();
};

#endif
