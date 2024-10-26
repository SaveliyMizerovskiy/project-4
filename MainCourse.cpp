/**
 * @file MainCourse.cpp
 * @brief This file contains the implementation of the MainCourse class, which represents a dish in a virtual bistro simulation.
 * 
 * The MainCourse class includes methods to manage and present the details of a dish, including name, ingredients, preparation time, price, cuisine type, cooking method, protien type, side dishes, and gluten free.
 * The implementation ensures that the MainCourse name is validated and correctly formatted.
 * 
 * @date 10/17/24
 * @author Saveliy Mizerovskiy
 */

#include "MainCourse.hpp"

/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}


/**
    * Displays the main course's details.
    * @post Outputs the main course's details, including name, ingredients,
    preparation time, price, cuisine type, cooking method, protein type,
    side dishes, and gluten-free status to the standard output.
    * The information must be displayed in the following format:
    *
    * Dish Name: [Name of the dish]
    * Ingredients: [Comma-separated list of ingredients
    * Preparation Time: [Preparation time] minutes
    * Price: $[Price, formatted to two decimal places]
    * Cuisine Type: [Cuisine type]
    * Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
    * Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
    * Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
    Vegetables])
    * Gluten-Free: [Yes/No]
    */
    void MainCourse::display() const{
        //std::cout << "CALLED MAIN COURSE DISPLAY" << std::endl;
        std::cout << "Dish Name: " << getName() << std::endl;
        std::cout << "Ingredients: ";
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
        std::cout << "Cooking Method: ";
        switch (getCookingMethod()) {
            case CookingMethod::GRILLED: std::cout << "Grilled";  break;
            case CookingMethod::BAKED: std::cout << "Baked"; break;
            case CookingMethod::BOILED: std::cout << "Boiled"; break;
            case CookingMethod::FRIED: std::cout << "Fried"; break;
            case CookingMethod::STEAMED: std::cout << "Steamed"; break;
            case CookingMethod::RAW: std::cout << "Raw"; break;
        }
        std::cout << std::endl;
        std::cout << "Protein Type: " << getProteinType() << std::endl;
        std::cout << "Side Dishes: " << std::endl; // dont know if i need the endl here---
        for (size_t i = 0; i < getSideDishes().size(); ++i) {
            std::cout << getSideDishes()[i].name << " (Category: ";
            switch (getSideDishes()[i].category) {
                case Category::GRAIN: std::cout << "Grain"; break;
                case Category::PASTA: std::cout << "Pasta"; break;
                case Category::LEGUME: std::cout << "Legume"; break;
                case Category::BREAD: std::cout << "Bread"; break;
                case Category::SALAD: std::cout << "Salad"; break;
                case Category::SOUP: std::cout << "Soup"; break;
                case Category::STARCHES: std::cout << "Starches"; break;
                case Category::VEGETABLE: std::cout << "Vegetable"; break;
            }
            std::cout << ")";
            if (i != getSideDishes().size() - 1) {
                std::cout << std::endl;
            }
        }
        std::cout << std::endl;
        std::cout << "Gluten-Free: ";
        if (isGlutenFree()) std::cout << "Yes" ; else std::cout << "No"; // I did this just by going from the dome so check this if it doesnt display properly
        std::cout << std::endl;
    }


    /**
    * Modifies the main course based on dietary accommodations.
    * @param request A DietaryRequest structure specifying the dietary
    accommodations.
    * @post Adjusts the main course's attributes to meet the specified
    dietary needs.
    * - If `request.vegetarian` is true:
    * - Changes `protein_type_` to "Tofu".
    * - Searches `ingredients_` for any non-vegetarian
    ingredients and replaces the first occurrence with "Beans". If there are
    other non-vegetarian ingredients, the next non-vegetarian ingredient is
    replaced with "Mushrooms". If there are more, they will be removed
    without substitution.
    * Non-vegetarian ingredients are: "Meat", "Chicken",
    "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
    * - If `request.vegan` is true:
    * - Changes `protein_type_` to "Tofu".
    * - Removes dairy and egg ingredients from `ingredients_`.
    * Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
    "Butter", "Cream", "Yogurt".
    * - If `request.gluten_free` is true:
    * - Sets `gluten_free_` to true.
    * - Removes side dishes from `side_dishes_` whose category
    involves gluten.
    * Gluten-containing side dish categories are: `GRAIN`,
    `PASTA`, `BREAD`, `STARCHES`.
    */
    void MainCourse::dietaryAccommodations(const Dish::DietaryRequest request){
        //std::cout << "main course diatery accomedation called" << std::endl;
        if(request.vegetarian){
            //std::cout << "main course request vegetarian" << std::endl;
            setProteinType("Tofu");
            bool first = 1, second = 1;
            std::string s;
            std::vector<std::string> nonVeg = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
            std::vector<std::string> ingrid = getIngredients();
            for (int i = 0; i < (int) ingrid.size(); ++i) {
                for (auto &&j : nonVeg){
                    if(j == ingrid[i]){ // ingrid[i].find(j) != std::string::npos
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
            //std::cout << "main course request vegetarian ended" << std::endl;
            //display();
        }
        if(request.vegan == true){
            //std::cout << "vegan called for some reason" << std::endl; 
            std::string s;
            setProteinType("Tofu");
            //std::cout << "Protiend type: " << getProteinType() << std::endl;
            std::vector<std::string> nonVeg = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
            std::vector<std::string> ingrid = getIngredients();
            for (int i = 0; i < (int) ingrid.size(); ++i) {
                for (auto &&j : nonVeg){
                    if(j == ingrid[i]){ // ingrid[i].find(j) != std::string::npos if it wasnt just a list
                        auto pos = ingrid.begin() + i; // check that this removes properly
                        ingrid.erase(pos);
                    }
                }
            }
            setIngredients(ingrid);
            //display();
        }
        if(request.gluten_free){
            //std::cout << "gluten free called" << std::endl;
            std::string s;
            setGlutenFree(true);
            std::vector<Category> nonVeg = {Category::GRAIN, Category::PASTA, Category::BREAD, Category::STARCHES};
            std::vector<SideDish> dishes = getSideDishes();
            for (int i = 0; i < (int) dishes.size(); ++i) {
                for (auto &&j : nonVeg){
                    if(j == dishes[i].category){
                        auto pos = dishes.begin() + i; // check that this removes properly
                        dishes.erase(pos);
                    }
                }
            }
            side_dishes_ = dishes;
        }
        //std::cout << "main course diatery accomedation ended" << std::endl;
    }