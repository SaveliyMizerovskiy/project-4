#include "Kitchen.hpp"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
    Kitchen kit = Kitchen("Balling.csv");
    struct Dish::DietaryRequest request;
    request.vegetarian = true;
    //request.vegan = true;
    //request.gluten_free = true;
    request.low_sugar = true;
    kit.dietaryAdjustment(request);
    kit.displayMenu();
    return 0;
}