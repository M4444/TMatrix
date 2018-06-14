#include <cstdlib>
#include "Rain.h"
#include "Terminal.h"

Rain::Rain()
{
	// Create all the rain columns
	int NumberOfColumns = Terminal::getNumberOfColumns();
	for (int i = 1; i < NumberOfColumns+1; i++) {
		int Speed = rand() % 2 + 1;
		RainColumns.push_back(RainColumn(i, Speed));
	}
}

void Rain::Update()
{
	for (RainColumn &rc : RainColumns) {
		rc.Update();
	}
}
