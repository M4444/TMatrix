#include <unistd.h>
#include "Rain.h"
#include "Terminal.h"

#define RUN_SPEED 100

int main()
{
	Terminal::getInstance();

	Rain rain {};
	while (true) {
		usleep(1000*RUN_SPEED);

		rain.Update();
		Terminal::Flush();
	}
}
