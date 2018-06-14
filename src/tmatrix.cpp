#include <time.h>
#include <unistd.h>

#include "Terminal.h"
#include "Rain.h"

#define RUN_SPEED 100

int main()
{
	Terminal::getInstance();

	srand (time(NULL));

	Rain rain;
	while (true) {
		usleep(1000*RUN_SPEED);

		rain.Update();
	}

	return 0;
}
