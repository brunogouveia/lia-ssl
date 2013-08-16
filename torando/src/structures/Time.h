/*
 * Time.h
 *
 *  Este módulo ajuda a marcar o tempo.
 */

#ifndef TIME_H_
#define TIME_H_

#include <sys/time.h>

class Time {
	private:
		Time() {}
		~Time() {}
	public:

		static long int now() {
			struct timeval time;

			gettimeofday(&time, NULL);

			long int mtime, seconds, useconds;

			seconds = time.tv_sec;
			useconds = time.tv_usec;

			mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;

			return mtime;

		}
};

#endif /* TIME_H_ */
