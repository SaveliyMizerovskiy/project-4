/**
 * FIX THIS 
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class, which represents a kithcen in a virtual bistro simulation.
 * 
 * The kithcen class includes methods to manage and present the details of a dishes, including names, ingredients, preparation times, prices, cuisine types and others.
 * The implementation ensures that the kitchen name is validated and correctly formatted.
 * 
 * @date 10/17/24
 * @author Saveliy Mizerovskiy
 */

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "ArrayBag.hpp"
#include "Dish.hpp"
#include "Appetizer.hpp"
#include "Dessert.hpp"
#include "MainCourse.hpp"
#include <vector>
// for round
#include <cmath>

class Kitchen : public ArrayBag<Dish*> {
    public:
        Kitchen();
        /**
        * Parameterized constructor.
        * @param filename The name of the input CSV file containing dish
        information.
        * @pre The CSV file must be properly formatted.
        * @post Initializes the kitchen by reading dishes from the CSV file and
        storing them as `Dish*`.
        */
        Kitchen(std::string filename);
        bool newOrder(Dish* new_dish);
        bool serveDish(Dish* dish_to_remove);
        int getPrepTimeSum() const;
        int calculateAvgPrepTime() const;
        int elaborateDishCount() const;
        double calculateElaboratePercentage() const;
        int tallyCuisineTypes(const std::string& cuisine_type) const;
        int releaseDishesBelowPrepTime(const int& prep_time);
        int releaseDishesOfCuisineType(const std::string& cuisine_type);
        void kitchenReport() const;


        //Store Pointers ????????????????
        //Modify the Kitchen class to store pointers to Dish objects ( Dish* ), allowing for polymorphic behavior.


        /**
        * Adjusts all dishes in the kitchen based on the specified dietary
        accommodation.
        * @param request A DietaryRequest structure specifying the dietary
        accommodations.
        * @post Calls the `dietaryAccommodations()` method on each dish in the
        kitchen to adjust them accordingly.
        */
        void dietaryAdjustment(Dish::DietaryRequest request) const;
        /**
        * Displays all dishes currently in the kitchen.
        * @post Calls the `display()` method of each dish.
        */
        void displayMenu() const;
        /**
        * Destructor.
        * @post Deallocates all dynamically allocated dishes to prevent memory
        leaks.
        */
        ~Kitchen();
        //std::vector<Dish*> getDishes() const;
        //void setDishes(const std::vector<Dish*> dishes);


    private:
        int total_prep_time_;
        int count_elaborate_;
        //std::vector<Dish*> dishes_;
    
};

#endif // KITCHEN_HPP