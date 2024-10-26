/**
 * @file Kitchen.cpp
 * @brief This file contains the implementation of the Kitchen class, which represents a kitchen in a virtual bistro simulation.
 * 
 * The Kitchen class includes methods to manage and present the details of dishes, including names, ingredients, preparation times, prices, cuisine types, and others.
 * The implementation ensures that the kitchen name is validated and correctly formatted.
 * 
 * @date 10/17/24
 * @author Saveliy Mizerovskiy
 */

#include "Kitchen.hpp"
#include <iostream> 
#include <fstream>
#include <string>
Kitchen::Kitchen() : ArrayBag<Dish*>(), total_prep_time_(0), count_elaborate_(0) {

}
/**
* Parameterized constructor.
* @param filename The name of the input CSV file containing dish
information.
* @pre The CSV file must be properly formatted.
* @post Initializes the kitchen by reading dishes from the CSV file and
storing them as `Dish*`.
*/
Kitchen::Kitchen(std::string filename){
    // Open the text file named "input.txt"
    std::ifstream f(filename);

    // Check if the file is successfully opened
    if (!f.is_open()) {
        std::cout << "Error opening the file!";
    }

    // String variable to store the read data
    ArrayBag<Dish*>();
    std::string line;

    std::string header;
    getline(f,header);

    // Read each line of the file and print it to the
    // standard output stream till the whole file is
  	// completely read
    while (getline(f, line)){
        std::string dishType = line.substr(0, line.find(","));

        
        
        line = line.substr(line.find(",") + 1); // this indexing is definetly gonna be wrong
        std::string name = line.substr(0, line.find(",")); // making the name for the appetizer
        line = line.substr(line.find(",") + 1);
        
        
        
        std::string ingridients = line.substr(0, line.find(",")); //making the vector of ingridients
        std::vector<std::string> ingrid;

        

        while(ingridients.find(";") != std::string::npos) {
            size_t pos = ingridients.find(";");
            ingrid.push_back(ingridients.substr(0, pos));
            ingridients = ingridients.substr(pos + 1);
        }
        ingrid.push_back(ingridients);
        
        line = line.substr(line.find(",") + 1);

        int prep_time =  stoi(line.substr(0, line.find(","))); // getting prep time
        line = line.substr(line.find(",") + 1);

        

        double price = stod(line.substr(0, line.find(","))); // getting price
        line = line.substr(line.find(",") + 1);

        

        Dish::CuisineType type = Dish::OTHER; // getting type
        if(line.substr(0, line.find(",")) == "ITALIAN"){ // ITALIAN, MEXICAN, CHINESE, INDIAN, AMERICAN, FRENCH, OTHER
            type = Dish::ITALIAN;
        } else if(line.substr(0, line.find(",")) == "MEXICAN"){
            type = Dish::MEXICAN;
        } else if(line.substr(0, line.find(",")) == "CHINESE"){
            type = Dish::CHINESE;
        } else if(line.substr(0, line.find(",")) == "INDIAN"){
            type = Dish::INDIAN;
        } else if(line.substr(0, line.find(",")) == "AMERICAN"){
            type = Dish::AMERICAN;
        } else if(line.substr(0, line.find(",")) == "FRENCH"){
            type = Dish::FRENCH;
        } else if(line.substr(0, line.find(",")) == "OTHER"){
            type = Dish::OTHER;
        }
        line = line.substr(line.find(",") + 1);

        
        //already got &name, &ingrid, &prep_time, &price, &type so now i need the other specific ones
         if(dishType == "APPETIZER"){ // appetizer has extra style spice and vegetarian
            Appetizer::ServingStyle style; // getting the serving style
            if(line.substr(0, line.find(";")) == "PLATED"){ // PLATED, FAMILY_STYLE, BUFFET
                style = Appetizer::PLATED;
            } else if(line.substr(0, line.find(";")) == "FAMILY_STYLE"){
                style = Appetizer::FAMILY_STYLE;
            } else if(line.substr(0, line.find(";")) == "BUFFET"){
                style = Appetizer::BUFFET;
            }
            
            line = line.substr(line.find(";") + 1);
            int spice =  stoi(line.substr(0, line.find(","))); // getting spice level
            line = line.substr(line.find(";") + 1);
            bool veget = false; // gets the veget value 
            if(line == "true") veget = true;
            Appetizer *dishToAdd = new Appetizer(name, ingrid, prep_time, price, type, style, spice, veget); // me trying to store it as pointer
            newOrder(dishToAdd);
        } else if (dishType == "MAINCOURSE"){ // has extra enum method, string  protein, side_dishes vector , bool gluten
            MainCourse::CookingMethod method;
            if(line.substr(0, line.find(";")) == "GRILLED"){ // GRILLED, BAKED, BOILED, FRIED, STEAMED, RAW
                method = MainCourse::GRILLED;
            } else if (line.substr(0, line.find(";")) == "BAKED"){
                method = MainCourse::BAKED;
            } else if (line.substr(0, line.find(";")) == "BOILED"){
                method = MainCourse::BOILED;
            } else if (line.substr(0, line.find(";")) == "FRIED"){
                method = MainCourse::FRIED;
            } else if (line.substr(0, line.find(";")) == "STEAMED"){
                method = MainCourse::STEAMED;
            } else if (line.substr(0, line.find(";")) == "RAW"){
                method = MainCourse::RAW;
            }
            line = line.substr(line.find(";") + 1);
            std::string protein = line.substr(0, line.find(";"));
            line = line.substr(line.find(";") + 1);
            std::vector<MainCourse::SideDish> side_dishes;
            std::string sides = line.substr(0, line.find(";"));
            //there are only 2 sides so im not making a loop ---- Check if it doesnt work
            side_dishes.push_back(MainCourse::SideDish());
            side_dishes[0].name = sides.substr(0, sides.find(":"));
            sides = sides.substr(sides.find(":") + 1);
            MainCourse::Category sideCat = MainCourse::GRAIN;
            if(sides.substr(0, sides.find("|")) == "GRAIN"){ // GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE
                sideCat = MainCourse::GRAIN;
            } else if (sides.substr(0, sides.find("|")) == "PASTA"){
                sideCat = MainCourse::PASTA;
            } else if (sides.substr(0, sides.find("|")) == "LEGUME"){
                sideCat = MainCourse::LEGUME;
            } else if (sides.substr(0, sides.find("|")) == "BREAD"){
                sideCat = MainCourse::BREAD;
            } else if (sides.substr(0, sides.find("|")) == "SALAD"){
                sideCat = MainCourse::SALAD;
            } else if (sides.substr(0, sides.find("|")) == "SOUP"){
                sideCat = MainCourse::SOUP;
            } else if (sides.substr(0, sides.find("|")) == "STARCHES"){
                sideCat = MainCourse::STARCHES;
            } else if (sides.substr(0, sides.find("|")) == "VEGETABLE"){
                sideCat = MainCourse::VEGETABLE;
            }
            side_dishes[0].category = sideCat;
            sides = sides.substr(sides.find("|") + 1);

            side_dishes.push_back(MainCourse::SideDish());
            side_dishes[1].name = sides.substr(0, sides.find(":"));
            sides = sides.substr(sides.find(":") + 1);
            if(sides.substr(0, sides.find("|")) == "GRAIN"){ // GRAIN, PASTA, LEGUME, BREAD, SALAD, SOUP, STARCHES, VEGETABLE
                sideCat = MainCourse::GRAIN;
            } else if (sides.substr(0, sides.find("|")) == "PASTA"){
                sideCat = MainCourse::PASTA;
            } else if (sides.substr(0, sides.find("|")) == "LEGUME"){
                sideCat = MainCourse::LEGUME;
            } else if (sides.substr(0, sides.find("|")) == "BREAD"){
                sideCat = MainCourse::BREAD;
            } else if (sides.substr(0, sides.find("|")) == "SALAD"){
                sideCat = MainCourse::SALAD;
            } else if (sides.substr(0, sides.find("|")) == "SOUP"){
                sideCat = MainCourse::SOUP;
            } else if (sides.substr(0, sides.find("|")) == "STARCHES"){
                sideCat = MainCourse::STARCHES;
            } else if (sides.substr(0, sides.find("|")) == "VEGETABLE"){
                sideCat = MainCourse::VEGETABLE;
            }
            side_dishes[1].category = sideCat;
            line = line.substr(line.find(";") + 1);
            bool gluten = false;
            if (line == "true") gluten = true;
            MainCourse *dishToAdd = new MainCourse(name, ingrid, prep_time, price, type, method, protein, side_dishes, gluten); // me trying to store it as pointer
            newOrder(dishToAdd);
        } else if(dishType == "DESSERT"){ // has extra enum flavor, int sweetness, bool nuts
            Dessert::FlavorProfile flavor;
            if(line.substr(0, line.find(";")) == "SWEET"){ // SWEET, BITTER, SOUR, SALTY, UMAMI
                flavor = Dessert::SWEET;
            } else if (line.substr(0, line.find(";")) == "BITTER"){
                flavor = Dessert::BITTER;
            } else if (line.substr(0, line.find(";")) == "SOUR"){
                flavor = Dessert::SOUR;
            } else if (line.substr(0, line.find(";")) == "SALTY"){
                flavor = Dessert::SALTY;
            } else if (line.substr(0, line.find(";")) == "UMAMI"){
                flavor = Dessert::UMAMI;
            }
            line = line.substr(line.find(";") + 1);
            int sweetness = stoi(line.substr(0, line.find(";")));
            line = line.substr(line.find(";") + 1);
            bool nuts = false;
            if(line == "true") nuts = true;
            Dessert *dishToAdd = new Dessert(name, ingrid, prep_time, price, type, flavor, sweetness, nuts); // me trying to store it as pointer
            newOrder(dishToAdd);
        } //*/
    }
    
    // Close the file 
    
    f.close();
}

bool Kitchen::newOrder(Dish* new_dish)
{
    if (add(new_dish))
    {
        total_prep_time_ += (*new_dish).getPrepTime();
        //std::cout<< "Dish added: "<<new_dish.getName() << std::endl;
        //if the new dish has 5 or more ingredients AND takes an hour or more to prepare, increment count_elaborate_
        if ((*new_dish).getIngredients().size() >= 5 && (*new_dish).getPrepTime() >= 60)
        {
            //std::cout << "Elaborate dish added: "<<new_dish.getName() << std::endl;
            count_elaborate_++;
        }
        return true;
    }
    return false;
}
bool Kitchen::serveDish(Dish* dish_to_remove)
{
    if (getCurrentSize() == 0)
    {
        return false;
    }
    if (remove(dish_to_remove))
    {
        total_prep_time_ -= (*dish_to_remove).getPrepTime();
        if ((*dish_to_remove).getIngredients().size() >= 5 && (*dish_to_remove).getPrepTime() >= 60)
        {
            count_elaborate_--;
        }
        return true;
    }
    return false;
}
int Kitchen::getPrepTimeSum() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    return total_prep_time_;
}
int Kitchen::calculateAvgPrepTime() const
{
    if (getCurrentSize() == 0)
    {
        return 0;
    }
    double total_prep_time_ = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        total_prep_time_ += (*items_[i]).getPrepTime();
    }
    total_prep_time_ = total_prep_time_ / getCurrentSize();
    // std::cout<< "Total prep time: "<<total_prep_time_ << std::endl;
    // std::cout<<"rounded: "<<round(total_prep_time_)<<std::endl;
    return round(total_prep_time_);
}
int Kitchen::elaborateDishCount() const
{
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return count_elaborate_;
}
double Kitchen::calculateElaboratePercentage() const
{
    // //Computes the percentage of vegetarian dishes in the kitchen rounded up to 2 decimal places.
    // double elaborate_dish = count_elaborate_;
    // std::cout << elaborate_dish << std::endl;

    // double total_dish = getCurrentSize();
    // std::cout << total_dish << std::endl;

    // double percentage = (elaborate_dish / total_dish) * 10000;
    // std::cout << percentage << std::endl;
    // percentage = round(percentage);
    // std::cout << percentage << std::endl;
    // percentage = percentage / 100;
    // std::cout << percentage << std::endl;

    // return percentage;
    if (getCurrentSize() == 0 || count_elaborate_ == 0)
    {
        return 0;
    }
    return round(double(count_elaborate_) / double(getCurrentSize()) * 10000)/100;

    //return count_elaborate_ / getCurrentSize();
}
int Kitchen::tallyCuisineTypes(const std::string& cuisine_type) const{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if ((*items_[i]).getCuisineType() == cuisine_type)
        {
            count++;
        }
    }
    return count;
}
int Kitchen::releaseDishesBelowPrepTime(const int& prep_time)
{
    int count = 0;
    int num= getCurrentSize();
    for (int i = 0; i < num; i++)
    {
        if ((*items_[i]).getPrepTime() < prep_time)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}

int Kitchen::releaseDishesOfCuisineType(const std::string& cuisine_type)
{
    int count = 0;
    for (int i = 0; i < getCurrentSize(); i++)
    {
        if ((*items_[i]).getCuisineType() == cuisine_type)
        {
            count++;
            serveDish(items_[i]);
        }
    }
    return count;
}
void Kitchen::kitchenReport() const
{
    std::cout << "ITALIAN: " << tallyCuisineTypes("ITALIAN") << std::endl;
    std::cout << "MEXICAN: " << tallyCuisineTypes("MEXICAN") << std::endl;
    std::cout << "CHINESE: " << tallyCuisineTypes("CHINESE") << std::endl;
    std::cout << "INDIAN: " << tallyCuisineTypes("INDIAN") << std::endl;
    std::cout << "AMERICAN: " << tallyCuisineTypes("AMERICAN") << std::endl;
    std::cout << "FRENCH: " << tallyCuisineTypes("FRENCH") << std::endl;
    std::cout << "OTHER: " << tallyCuisineTypes("OTHER") << std::endl<<std::endl;
    std::cout << "AVERAGE PREP TIME: " << calculateAvgPrepTime() << std::endl;
    std::cout << "ELABORATE DISHES: " << calculateElaboratePercentage() << "%" << std::endl;
}

/**
* Adjusts all dishes in the kitchen based on the specified dietary
accommodation.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Calls the `dietaryAccommodations()` method on each dish in the
kitchen to adjust them accordingly.
*/
void Kitchen::dietaryAdjustment(Dish::DietaryRequest request) const{
    int count = 0;
    for (Dish* i : items_)
    {
        count ++;
        if(count <= item_count_){
            (*i).dietaryAccommodations(request);
        }
        
    }
}

/**
* Displays all dishes currently in the kitchen.
* @post Calls the `display()` method of each dish.
*/

void Kitchen::displayMenu() const{
    //std::cout << "display menu called" << std::endl;
    int count = 0;
    for (Dish* i : items_)
    {
        count ++;
        if(count <= item_count_){
            (*i).display();
            std::cout <<std::endl;
        }
    }
    //std::cout << "display menu ended" << std::endl;
}

Kitchen::~Kitchen(){
    for (Dish *i : items_)
    {
        delete i;
    } 
}