/*
 * HelperTemplates.h
 *
 *  Created on: Jun 6, 2015
 *      Author: colman
 */

#ifndef HELPERTEMPLATES_H_
#define HELPERTEMPLATES_H_

#include <queue>
#include <vector>

using namespace std;
typedef pair<unsigned, GridPosition> pel;
class comparPriorityPair{
public :
	inline bool operator ()(const pel& lhs,const pel& rhs){
			return lhs.first > rhs.first;
		}
};

class MyPq{
private :

	priority_queue<pel, vector<pel>,comparPriorityPair> elements;

public:
	inline bool empty() {
			return elements.empty();
		}

		inline void put(GridPosition item, unsigned priority) {
			//elements.emplace(priority, item);
			elements.push({priority,item});
		}

		inline GridPosition get() {
			GridPosition best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
};

#endif /* HELPERTEMPLATES_H_ */
