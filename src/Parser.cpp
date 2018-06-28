#include <csignal>

namespace Parser {
	void Parse(char c)
	{
		switch (c) {
		case 'q':
		case 'Q':
			std::raise(SIGINT);
		}
	}
}
