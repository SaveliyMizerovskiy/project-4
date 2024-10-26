/** 
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class, which represents a dish in a virtual bistro simulation.
 * 
 * The Appetizer class includes methods to manage and present the details of a dish, including name, ingredients, preparation time, price, cuisine type, serving style, spiceness level, and vegetarian.
 * The implementation ensures that the Appetizer name is validated and correctly formatted.
 * 
 * @date 10/17/24
 * @author Saveliy Mizerovskiy
 */

#include "Appetizer.hpp"
#include <iomanip> // For std::fixed and std::setprecision
#include <vector>

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}


/**
* Displays the appetizer's details.
* @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Serving Style: [Serving style: Plated, Family Style, or Buffet]
* Spiciness Level: [Spiciness level]
* Vegetarian: [Yes/No]
*/

void Appetizer::display() const{
    //std::cout << "CALLED APPETIZER DISPLAY" << std::endl;
    std::cout << "Dish Name: " << getName() << std::endl;
    std::cout << "Ingredients: ";
    //std::cout << "Ingrid Size: " << getIngredients().size() << std::endl;
    for (size_t i = 0; i < getIngredients().size(); ++i) {
        std::cout << getIngredients()[i];
        if (i != getIngredients().size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;
    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << std::fixed << std::setprecision(2) << "Price: $" << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;
    std::cout << "Serving Style: ";
    switch (getServingStyle()) {
        case ServingStyle::PLATED: 
            std::cout << "Plated";
            break;
        case ServingStyle::FAMILY_STYLE: 
            std::cout << "Family Style";
            break;
        case ServingStyle::BUFFET: 
            std::cout << "Buffet";
            break;
    }
    std::cout << std::endl;
    std::cout << "Spiciness Level: " << getSpicinessLevel() << std::endl;
    std::cout << "Vegetarian: ";
    if (isVegetarian()) std::cout << "Yes" ; else std::cout << "No"; // I did this just by going from the dome so check this if it doesnt display properly
    std::cout << std::endl;
}

/**
* Modifies the appetizer based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the appetizer's attributes to meet the specified
MainCourse Class
dietary needs.
* - If `request.vegetarian` is true:
* - Sets `vegetarian_` to true.
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.low_sodium` is true:
* - Reduces `spiciness_level_` by 2 (minimum of 0).
* - If `request.gluten_free` is true:
* - Removes gluten-containing ingredients from
`ingredients_`.
* Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/
void Appetizer::dietaryAccommodations(const Dish::DietaryRequest request){
    if(request.vegetarian){ // vegeterian condition
        bool first = 1, second = 1;
        std::string s;
        std::vector<std::string> nonVeg = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
        std::vector<std::string> ingrid = getIngredients();
        setVegetarian(request.vegetarian);
        for (int i = 0; i < (int) ingrid.size(); ++i) {
            for (auto &&j : nonVeg){
                if(j == ingrid[i]){
                    if(first){
                        ingrid[i] = "Beans";
                        first = false;
                    } else if(second){
                        ingrid[i] = "Mushrooms";
                        second = false;
                    } else {
                        auto pos = ingrid.begin() + i; // check that this removes properly
                        ingrid.erase(pos);
                    }
                }
            }
        }
        setIngredients(ingrid);
    }

    if(request.low_sodium){ // low sodium
        int spice = getSpicinessLevel() - 2;
        if (spice < 0){
            spice = 0;
        }
        setSpicinessLevel(spice);
    }

    if(request.gluten_free){ // gluten free
        std::string s;
        std::vector<std::string> glut = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"};
        std::vector<std::string> ingrid = getIngredients();
        for (int i = 0; i < (int) ingrid.size(); ++i) {
            for (auto &&j : glut){
                if(j == ingrid[i]){
                    auto pos = ingrid.begin() + i; // check that this removes properly
                    ingrid.erase(pos);
                }
            }
            
        }
        setIngredients(ingrid);
    }
}