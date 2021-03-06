//
//  Ingredient.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef Ingredient_hpp
#define Ingredient_hpp

#include <stdio.h>
#include <string>

/*
 contains ingredient info
 - name & quantity
 - deduct or add ingredient amount
 */
class Ingredient {
    std::string m_name;
    int m_quantity;
public:
    Ingredient(std::string name, int quantity) {
        m_name = name;
        m_quantity = quantity;
    }
    
    int GetQuantity() {
        return m_quantity;
    }
    
    std::string GetName() {
        return m_name;
    }
    
    // deduct ingredient amount
    void DeductAmount(int amount) {
        m_quantity -= amount;
    }
    
    // add ingredient amount
    void AddAmount(int amount) {
        m_quantity += amount;
    }
};
#endif /* Ingredient_hpp */
