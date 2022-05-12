#include "RoundTrip.h"
#include "routing/roundtrip.h"
#include "routing_api.h"
#include "graph.h"
using namespace routing;

RoundTrip::RoundTrip(Vector3 pos_, Vector3 des_, const IGraph* graph_) {
    std::vector<float> startTemp = {pos_.x, pos_.y, pos_.z};
    std::vector<float> endTemp = {des_.x, des_.y, des_.z};
    startTemp.push_back(pos_.x);
    startTemp.push_back(pos_.y);
    startTemp.push_back(pos_.z);
    endTemp.push_back(des_.x);
    endTemp.push_back(des_.y);
    endTemp.push_back(des_.z);
    std::vector<float> start = graph_->NearestNode(startTemp, EuclideanDistance())->GetPosition();
    std::vector<float> end = graph_->NearestNode(endTemp, EuclideanDistance())->GetPosition();
    path = graph_->GetPath(end, start, TheRoundTrip::Default());
    des = { end[0], end[1], end[2] };
    currentIndex = 0;
    maxIndex = path.size() - 1;
}

bool RoundTrip::IsCompleted(){
    return (des - lastPos).Magnitude()<1.0 && currentIndex == maxIndex;
}//return

void RoundTrip::Move(IEntity* entity, double dt){
    float speed = entity->GetSpeed();
    Vector3 currentPos = entity->GetPosition();
    Vector3 nextPos = { path[currentIndex][0], path[currentIndex][1], path[currentIndex][2] };
    Vector3 dir = (nextPos - currentPos).Unit();
    currentPos = currentPos + dir * speed * dt;
    lastPos = currentPos;
    entity->SetPosition(currentPos);
    entity->SetDirection(dir);
    if ((nextPos - currentPos).Magnitude() < 1.0 && currentIndex < maxIndex)
        currentIndex++;
}
