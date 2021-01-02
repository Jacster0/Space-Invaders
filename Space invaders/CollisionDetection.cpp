#include "CollisionDetection.h"
#include <algorithm>

//Checks if to rectangles has collided
//This code is inspired from the accepted answer on https://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
bool CollisionDetection::CheckCollison(const Rectangle& firstRectangle, const Rectangle& secondRectangle) {
    //calculate the top left and bottom right corners for the rectangles
    //first rectangle
    auto FirstPt = firstRectangle.GetPoint();
    
    auto topLeftFirstRect      = Point2D(FirstPt.x, FirstPt.y);
    auto bottomRightFirstRect  = Point2D(topLeftFirstRect.x + firstRectangle.GetWidth(), topLeftFirstRect.y + firstRectangle.GetHeight());

    //second rectangle
    auto secondPt = secondRectangle.GetPoint();

    auto topLeftSecondRect     = Point2D(secondPt.x, secondPt.y);
    auto bottomRightSecondRect = Point2D(topLeftSecondRect.x + secondRectangle.GetWidth(), topLeftSecondRect.y + secondRectangle.GetHeight());

    return topLeftFirstRect.x < bottomRightSecondRect.x && bottomRightFirstRect.x > topLeftSecondRect.x
        && topLeftFirstRect.y < bottomRightSecondRect.y && bottomRightFirstRect.y > topLeftSecondRect.y;
}
