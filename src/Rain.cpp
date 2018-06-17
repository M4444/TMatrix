#include <cstdlib>
#include "Rain.h"
#include "Random.h"
#include "Terminal.h"

Rain::Rain()
{
	// Create all the rain columns
	int NumberOfColumns = Terminal::getNumberOfColumns();
	for (int i = 0; i < NumberOfColumns; i++) {
		int Speed = Random::Random(1, 2);
		RainColumns.push_back(RainColumn(i, Speed));
	}
}

void Rain::Update()
{
	for (RainColumn &rc : RainColumns) {
		rc.Update();
	}
}
