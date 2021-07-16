//
//  Recipe.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef Recipe_hpp
#define Recipe_hpp

#include <stdio.h>
#include <map>
#include <string>
#include <vector>
#include "Ingredient.hpp"
#include "json.hpp"
using json = nlohmann::json;

/*
 contains list of
 ingredients used as recipe
 by a beverage
 - add, remove, get ingredient
 */
class Recipe {
protected:
    std::map<std::string, Ingredient*> m_ingredients;
private:
    bool CheckIfQuantityValid(int quantity) {
        return quantity > 0;
    }
    
    bool CheckIfNameValid(std::string name) {
        return name.length() > 0;
    }
public:
    Recipe() {
        
    }
    
    // initialize recipe with ingredient list
    Recipe(json ingredients) {
        for(auto it = ingredients.begin(); it != ingredients.end(); it++) {
            if(CheckIfNameValid(it.key()) && CheckIfQuantityValid(it.value())) {
                m_ingredients[it.key()] = new Ingredient(it.key(), it.value());
            }
        }
    }
    
    // check if recipe contains the ingredient
    bool CheckIfIngredientPresent(std::string name) {
        return m_ingredients.find(name) != m_ingredients.end();
    }
    
    // add ingredient to recipe
    void AddIngredient(std::string name, int quantity) {
        if(!CheckIfNameValid(name) || !CheckIfQuantityValid(quantity)) return;
        m_ingredients[name] = new Ingredient(name, quantity);
    }
    
    // remove ingredient from recipe
    void RemoveIngredient(std::string name) {
        if(!CheckIfIngredientPresent(name)) return;
        m_ingredients.erase(name);
    }
    
    // returns list of ingredients required to prepare the recipe
    std::vector<Ingredient*> GetIngredients() {
        std::vector<Ingredient*> ingredients;
        for(auto it = m_ingredients.begin(); it != m_ingredients.end(); it++) {
            ingredients.push_back(it->second);
        }
        return ingredients;
    }
};
#endif /* Recipe_hpp */
