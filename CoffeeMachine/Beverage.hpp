//
//  Beverage.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef Beverage_hpp
#define Beverage_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "IngredientInventory.hpp"
#include "json.hpp"

using json = nlohmann::json;

using namespace std;

class Beverage {
    std::string m_name;
    Recipe *m_recipe;
public:
    Beverage(string name, json recipe) {
        m_name = name;
        m_recipe = new Recipe(recipe);
    }
    
    void AddRecipe(json recipe) {
        if(m_recipe == nullptr) return;
       m_recipe->AddIngredient(recipe.begin().key(), recipe.begin().value());
    }
    
    vector<Ingredient*> GetRecipe() {
        vector<Ingredient*> res;
        if(m_recipe == nullptr) return res;
        return m_recipe->GetIngredients();
    }
    
    std::string GetName() {
        return m_name;
    }
    
};
#endif /* Beverage_hpp */
