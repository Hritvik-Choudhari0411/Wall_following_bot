/**
 * @file    micromouse.h
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief 
 * @version 0.1
 * @date    2022-03-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef ___MICROMOUSE_H___
#define ___MICROMOUSE_H___

#include <iostream>
#include <array>
#include "../simulator/simulator.h"



namespace rwa2group11
{
    
    class Goal
    {
    protected:
        std::array<int, 2> goal;

    public:
        
        int *set_goal();

      
        void color_goal();
    };

 
    class Algorithm
    {
    private:
        std::array<int, 2> curr_loc{0, 0};
        std::vector<std::tuple<int, int>> path;
        std::vector<std::tuple<int, int>> path_f;

    public:

        void left_wall_following(int *dir, int *temp);

        void right_wall_following(int *dir, int *temp);

        void way_back(int *dir);


        void set_wall(int *dir);

        void set_borders();
    };

}

#endif
