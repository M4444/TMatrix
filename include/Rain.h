#ifndef _RAIN_H_
#define _RAIN_H_

#include <vector>
#include "Active.h"
#include "RainColumn.h"

class Rain : public Active {
	std::vector<RainColumn> RainColumns;
public:
	Rain();

	void Update();
};

#endif
