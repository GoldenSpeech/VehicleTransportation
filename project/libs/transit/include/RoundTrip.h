#ifndef ROUND_H_
#define ROUND_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "entity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class RoundTrip : public IStrategy {
public:
    RoundTrip(Vector3 pos_, Vector3 des_, const IGraph* graph_);
    ~RoundTrip();
    void Move(IEntity* entity, double dt);
    bool IsCompleted();

protected:
    Vector3 des;
    Vector3 lastPos;
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
}; //end class
#endif //ROUND_H_
