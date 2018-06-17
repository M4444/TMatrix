#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <string>
#include <vector>

// Singleton
class Terminal
{
	static int NumberOfRows;
	static int NumberOfColumns;
	static std::vector<std::string> Screen;

	Terminal();
	~Terminal();
public:
	Terminal(Terminal const&)	= delete;
	void operator=(Terminal const&)	= delete;

	static Terminal& getInstance()
	{
		static Terminal instance;
		return instance;
	}

	static int getNumberOfRows() { return NumberOfRows; }
	static int getNumberOfColumns() { return NumberOfColumns; }
	static void Draw(int x, int y, const std::string &str, bool isGlowing = false);
	static void Erase(int x, int y);
	static void Flush();
};

#endif
