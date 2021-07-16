//
//  TestCoffeeMachine.hpp
//  CoffeeMachine
//
//  Created by Shilpi Roy on 15/07/21.
//  Copyright © 2021 Shilpi Roy. All rights reserved.
//

#ifndef TestCoffeeMachine_hpp
#define TestCoffeeMachine_hpp

#include <stdio.h>
#include <iostream>
#include "json.hpp"
#include <fstream>
#include "CoffeeMachine.hpp"


using json = nlohmann::json;

class TestCoffeeMachine {
public:
    void RunTestCase1() {
        std::cout<<"Running test case 1....\n\n-----------\n";
         auto j = json::parse(R"(
                               {
                                 "machine": {
                                   "outlets": {
                                     "count_n": 4
                                   },
                                   "total_items_quantity": {
                                     "hot_water": 500,
                                     "hot_milk": 500,
                                     "ginger_syrup": 100,
                                     "sugar_syrup": 100,
                                     "tea_leaves_syrup": 100
                                   },
                                   "beverages": {
                                     "hot_tea": {
                                       "hot_water": 200,
                                       "hot_milk": 100,
                                       "ginger_syrup": 10,
                                       "sugar_syrup": 10,
                                       "tea_leaves_syrup": 30
                                     },
                                     "hot_coffee": {
                                       "hot_water": 100,
                                       "ginger_syrup": 30,
                                       "hot_milk": 400,
                                       "sugar_syrup": 50,
                                       "tea_leaves_syrup": 30
                                     },
                                     "black_tea": {
                                       "hot_water": 300,
                                       "ginger_syrup": 30,
                                       "sugar_syrup": 50,
                                       "tea_leaves_syrup": 30
                                     },
                                     "green_tea": {
                                       "hot_water": 100,
                                       "ginger_syrup": 30,
                                       "sugar_syrup": 50,
                                       "green_mixture": 30
                                     }
                                   }
                                 }
                               }

                               )");
        
        std::cout << std::setw(4) << j << std::endl;
        std::cout<<"\n----------\n";

         CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);

         
         vector<vector<std::string> > expectedResults;
         vector<std::string> expectedResult1;
         expectedResult1.push_back("hot_tea is prepared");
         expectedResult1.push_back("hot_coffee is prepared");
         expectedResult1.push_back("green_tea can't be prepared because green_mixture is not available");
         expectedResult1.push_back("black_tea can't be prepared because hot_water is not sufficient");
         
        vector<std::string> expectedResult2;
        expectedResult2.push_back("hot_tea is prepared");
        expectedResult2.push_back("black_tea is prepared");
        expectedResult2.push_back("green_tea can't be prepared because green_mixture is not available");
        expectedResult2.push_back("hot_coffee can't be prepared because hot_water is not sufficient");


         
         vector<std::string> expectedResult3;
         expectedResult3.push_back("hot_coffee is prepared");
         expectedResult3.push_back("black_tea is prepared");
         expectedResult3.push_back("green_tea can't be prepared because green_mixture is not available");
         expectedResult3.push_back("hot_tea can't be prepared because hot_water is not sufficient");
         
         expectedResults.push_back(expectedResult1);
         expectedResults.push_back(expectedResult2);
         expectedResults.push_back(expectedResult3);
         for(int i = 0; i < expectedResults.size(); i++) {
             sort(expectedResults[i].begin(), expectedResults[i].end());
         }
         
         vector<std::string> actualResult = cm->PrepareBeverage();
         sort(actualResult.begin(), actualResult.end());
         bool isExpected = false, idx = -1;
          for(int i = 0; i < expectedResults.size(); i++) {
              bool result = std::equal(actualResult.begin(), actualResult.end(), expectedResults[i].begin());
              if(result) {
                  isExpected = true;
                  idx = i;
                  break;
              }
          }
         assert(isExpected == true);
         std::cout<<"Matches output id: "<<idx + 1<<"\n"<<"-------------\n";
    }
    
    void RunTestCase2() {
        std::cout<<"Running test case 2....\n\n-----------\n";
         auto j = json::parse(R"(
                               {
                                 "machine": {
                                   "outlets": {
                                     "count_n": 3
                                   },
                                   "total_items_quantity": {
                                     "hot_water": 50,
                                     "hot_milk": 50,
                                     "sugar_syrup": 50,
                                     "coffee_beans": 50
                                   },
                                   "beverages": {
                                     "dark_coffee": {
                                       "hot_water": 25,
                                       "hot_milk": 25,
                                       "sugar_syrup": 25,
                                       "coffee_beans": 25
                                     },
                                     "capuchhino_coffee": {
                                       "hot_water": 25,
                                       "hot_milk": 25,
                                       "sugar_syrup": 25,
                                       "coffee_beans": 25
                                     },
                                     "latte_coffee": {
                                       "hot_water": 25,
                                       "hot_milk": 25,
                                       "sugar_syrup": 25,
                                       "coffee_beans": 25
                                     }
                                   }
                                 }
                               }

                               )");
        
        std::cout << std::setw(4) << j << std::endl;
        std::cout<<"\n----------\n";

         CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);


         vector<vector<std::string> > expectedResults;
         vector<std::string> expectedResult1;
         expectedResult1.push_back("dark_coffee is prepared");
         expectedResult1.push_back("capuchhino_coffee is prepared");
         expectedResult1.push_back("latte_coffee can't be prepared because coffee_beans is not sufficient");

        vector<std::string> expectedResult2;
        expectedResult2.push_back("latte_coffee is prepared");
        expectedResult2.push_back("capuchhino_coffee is prepared");
        expectedResult2.push_back("dark_coffee can't be prepared because coffee_beans is not sufficient");


         vector<std::string> expectedResult3;
         expectedResult3.push_back("latte_coffee is prepared");
         expectedResult3.push_back("dark_coffee is prepared");
         expectedResult3.push_back("capuchhino_coffee can't be prepared because coffee_beans is not sufficient");

         expectedResults.push_back(expectedResult1);
         expectedResults.push_back(expectedResult2);
         expectedResults.push_back(expectedResult3);
         for(int i = 0; i < expectedResults.size(); i++) {
             sort(expectedResults[i].begin(), expectedResults[i].end());
         }
         
         vector<std::string> actualResult = cm->PrepareBeverage();
         sort(actualResult.begin(), actualResult.end());
         bool isExpected = false, idx = -1;
          for(int i = 0; i < expectedResults.size(); i++) {
              bool result = std::equal(actualResult.begin(), actualResult.end(), expectedResults[i].begin());
              if(result) {
                  isExpected = true;
                  idx = i;
                  break;
              }
          }
         assert(isExpected == true);
         std::cout<<"Matches output id: "<<idx + 1<<"\n"<<"-------------\n";
    }
    
    void RunTestCase3() {
        std::cout<<"Running test case 3....\n\n-----------\n";
        auto j = json::parse(R"(
                            {
                              "machine": {
                                "outlets": {
                                  "count_n": 5
                                },
                                "total_items_quantity": {
                                    "milk_powder": 50,
                                    "hot_water": 50,
                                    "sugar_syrup": 40,
                                    "coffee_beans": 50,
                                    "chocolate_powder": 50,
                                    "ginger_syrup": 40
                                },
                                "beverages": {
                                  "dark_coffee": {
                                    "dark_matter": 10,
                                    "sugar_syrup": 50,
                                    "coffee_beans": 10
                                  },
                                  "capuchino_coffee": {
                                    "milk_powder": 100,
                                    "sugar_syrup": 20,
                                    "coffee_beans": 20
                                  },
                                  "ginger_tea": {
                                    "hot_water": 25,
                                    "ginger_syrup": 25,
                                    "sugar_syrup": 15
                                  },
                                  "hot_milk": {
                                    "hot_water": 30,
                                    "milk_powder": 30,
                                    "sugar_syrup": 25
                                  },
                                  "chocolate_milk": {
                                    "hot_water": 20,
                                    "milk_powder": 20,
                                    "chocolate_powder": 10,
                                    "sugar_syrup": 20
                                  }
                                }
                              }
                            }


                              )");
        std::cout << std::setw(4) << j << std::endl;
        std::cout<<"\n----------\n";

        CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);
        
         vector<vector<std::string> > expectedResults;
         vector<std::string> expectedResult1;
         vector<std::string> expectedResult2;
         vector<std::string> expectedResult3;
         expectedResult1.push_back("dark_coffee can't be prepared because dark_matter is not available");
         expectedResult1.push_back("capuchino_coffee can't be prepared because milk_powder is not sufficient");
        expectedResult2 = expectedResult3 = expectedResult1;
        expectedResult1.push_back("ginger_tea is prepared");
        expectedResult1.push_back("chocolate_milk is prepared");
        expectedResult3 = expectedResult1;
        expectedResult1.push_back("hot_milk can't be prepared because hot_water is not sufficient");
        expectedResult3.push_back("hot_milk can't be prepared because sugar_syrup is not sufficient");
        expectedResult2.push_back("hot_milk is prepared");
        expectedResult2.push_back("ginger_tea can't be prepared because hot_water is not sufficient");
        expectedResult2.push_back("chocolate_milk can't be prepared because sugar_syrup is not sufficient");
        
         expectedResults.push_back(expectedResult1);
         expectedResults.push_back(expectedResult2);
         expectedResults.push_back(expectedResult3);
         for(int i = 0; i < expectedResults.size(); i++) {
             sort(expectedResults[i].begin(), expectedResults[i].end());
         }
         
         vector<std::string> actualResult = cm->PrepareBeverage();
         sort(actualResult.begin(), actualResult.end());
         bool isExpected = false, idx = -1;
          for(int i = 0; i < expectedResults.size(); i++) {
              bool result = std::equal(actualResult.begin(), actualResult.end(), expectedResults[i].begin());
              if(result) {
                  isExpected = true;
                  idx = i;
                  break;
              }
          }
         assert(isExpected == true);
         std::cout<<"Matches output id: "<<idx + 1<<"\n"<<"-------------\n";
    }
    
    
    void RunTestCase4() {
        std::cout<<"Running test case 4....\n\n-----------\n";
        auto j = json::parse(R"(
                            {
                                "machine": {
                                  "outlets": {
                                    "count_n": 0
                                  },
                                  "total_items_quantity": {

                                  },
                                  "beverages": {

                                  }
                                }
                              }

                              )");
        
        std::cout << std::setw(4) << j << std::endl;
        std::cout<<"\n----------\n";

        CoffeeMachine *cm = new CoffeeMachine(j["machine"]["outlets"]["count_n"], j["machine"]["beverages"], j["machine"]["total_items_quantity"]);
        vector<std::string> result = cm->PrepareBeverage();
        assert(result.size() == 0);
        std::cout<<"No beverages to prepare \n----------\n";
    }
public:
    void RunTests() {
        RunTestCase1();
        RunTestCase2();
        RunTestCase3();
        RunTestCase4();
    }
};
#endif /* TestCoffeeMachine_hpp */
