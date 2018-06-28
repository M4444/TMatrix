#include <unistd.h>
#include "Parser.h"
#include "Rain.h"
#include "Terminal.h"

#define RUN_SPEED 100

int main()
{
	Terminal::getInstance();

	Rain rain {};
	while (true) {
		Parser::Parse(Terminal::ReadInputChar());
		usleep(1000*RUN_SPEED);

		rain.Update();
		Terminal::Flush();
	}
}
