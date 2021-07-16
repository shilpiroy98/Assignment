//
//  BeverageInventory.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef BeverageInventory_hpp
#define BeverageInventory_hpp

#include <stdio.h>
#include <map>
#include <unordered_map>
#include <string>
#include <vector>
#include "Beverage.hpp"
#include "json.hpp"
using json = nlohmann::json;

class BeverageInventory {
    std::map<std::string, Beverage*> m_beverages;
    
public:
    BeverageInventory(json beverageList) {
        for(auto it = beverageList.begin(); it != beverageList.end(); it++) {
            AddBeverage(it.key(), it.value());
        }
    }
    
    std::vector<Beverage*> GetBeverages() {
        vector<Beverage*> beverages;
        for(auto it = m_beverages.begin(); it != m_beverages.end(); it++) {
            beverages.push_back(it->second);
        }
        return beverages;
    }
    
    bool CheckIfBeverageExists(std::string name) {
        return m_beverages.find(name) != m_beverages.end();
    }
    
    void AddBeverage(std::string name, json recipe) {
        m_beverages[name] = new Beverage(name, recipe);
    }
    
    void AddBeverageRecipe(std::string name, json recipe) {
        if(!CheckIfBeverageExists(name)) return;
        m_beverages[name]->AddRecipe(recipe);
    }
    
    void RemoveBeverage(std::string name) {
        if(!CheckIfBeverageExists(name)) return;
        m_beverages.erase(name);
    }
};
#endif /* BeverageInventory_hpp */
