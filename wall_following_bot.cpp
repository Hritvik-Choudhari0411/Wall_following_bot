/**
 * @file    micromouse.cpp
 * @author Hritvik Choudhari (hac@umd.edu)
 * @brief
 * @version 0.6
 * @date    2022-03-29
 *
 * @copyright Copyright (c) 2022
 *
 */


#include <iostream>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <memory>
#include <unistd.h>
#include "micromouse.h"

int *rwa2group11::Goal::set_goal()
{

    srand((unsigned)time(NULL));

    int flag1 = rand() % 2;
    int flag2 = rand() % 2;

    if (flag1)
    {
        goal[0] = rand() % 15 + 1;
        if (flag2)
        {
            goal[1] = 0;
        }
        else
        {
            goal[1] = 15;
        }
    }

    else
    {
        goal[1] = rand() % 15 + 1;
        if (flag2)
        {
            goal[0] = 0;
        }
        else
        {
            goal[0] = 15;
        }
    }
    return goal.data();
}

void rwa2group11::Goal::color_goal()
{
    // colorize and add text
    Simulator::setColor(goal[0], goal[1], 'Y');
    Simulator::setText(goal[0], goal[1], "G");
    Simulator::setColor(0, 0, 'y');
    Simulator::setText(0, 0, "H");
}

void rwa2group11::Algorithm::left_wall_following(int *dir, int *temp)
{

    int goal_x = *temp;       // Goal Position x coordinate
    int goal_y = *(temp + 1); // Goal Position y coordinate

    while (!(curr_loc[0] == goal_x && curr_loc[1] == goal_y))
    {

        if (Simulator::wallLeft())
        {

            if (Simulator::wallFront())
            {

                // std::cerr << "--- turn right---" << std::endl;
                Simulator::turnRight();
                *dir = *dir + 1;

                if (Simulator::wallFront())
                {

                    // std::cerr << "--- turn right---" << std::endl;
                    Simulator::turnRight();
                    *dir = *dir + 1;
                }
            }
        }
        else
        {

            // std::cerr << "--- turn left ---" << std::endl;
            Simulator::turnLeft();
            *dir = *dir - 1;
        }

        Simulator::moveForward();
        Simulator::setColor(curr_loc[0], curr_loc[1], 'g');
        Algorithm::set_wall(dir);
        path.push_back(std::make_tuple(curr_loc[0], curr_loc[1]));
    }
}

void rwa2group11::Algorithm::right_wall_following(int *dir, int *temp)
{

    int goal_x = *temp;       // Goal Position x coordinate
    int goal_y = *(temp + 1); // Goal Position y coordinate

    while (!(curr_loc[0] == goal_x && curr_loc[1] == goal_y))
    {
        if (Simulator::wallRight())
        {
            if (Simulator::wallFront())
            {
                // std::cerr << "--- turn right---" << std::endl;
                Simulator::turnLeft();
                *dir = *dir - 1;

                if (Simulator::wallFront())
                {
                    // std::cerr << "--- turn right---" << std::endl;
                    Simulator::turnLeft();
                    *dir = *dir - 1;
                }
            }
        }
        else
        {
            // std::cerr << "--- turn left ---" << std::endl;
            Simulator::turnRight();
            *dir = *dir + 1;
        }

        Simulator::moveForward();
        Simulator::setColor(curr_loc[0], curr_loc[1], 'g');
        Algorithm::set_wall(dir);
        path.push_back(std::make_tuple(curr_loc[0], curr_loc[1]));
    }
}

void rwa2group11::Algorithm::set_wall(int *dir)
{

    switch (*dir % 4)                   // Switch case for wall setting
    {
    case 0:
        curr_loc[1]--;
        if (Simulator::wallFront())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 's');
        }
        if (Simulator::wallLeft())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'e');
        }
        if (Simulator::wallRight())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'w');
        }
        break;

    case 1:
        curr_loc[0]--;
        if (Simulator::wallFront())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'w');
        }
        if (Simulator::wallLeft())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 's');
        }
        if (Simulator::wallRight())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'n');
        }
        break;

    case 2:
        curr_loc[1]++;
        if (Simulator::wallFront())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'n');
        }
        if (Simulator::wallLeft())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'w');
        }
        if (Simulator::wallRight())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'e');
        }
        break;

    case 3:
        curr_loc[0]++;
        if (Simulator::wallFront())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'e');
        }
        if (Simulator::wallLeft())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 'n');
        }
        if (Simulator::wallRight())
        {
            Simulator::setWall(curr_loc[0], curr_loc[1], 's');
        }
        break;
    }
}


void rwa2group11::Algorithm::way_back(int *dir)
{

    Simulator::turnLeft();                          // Turning the robot after goal is reached
    Simulator::turnLeft();
    *dir = *dir + 2;

    for (unsigned int i = 0; i < path.size(); i++)  // Loop for keeping the track of optimal path
    {
        if (count(path_f.begin(), path_f.end(), path.at(i)) > 0)
        {
            path_f.pop_back();
            i--;
        }
        else
        {
            path_f.push_back(path.at(i));
        }
    }

    std::vector<int> temp_x;
    std::vector<int> temp_y;

    Simulator::setColor(0, 0, 'w');

    for (auto [X, Y] : path_f)
    {
        temp_x.push_back(X);
        temp_y.push_back(Y);
        Simulator::setColor(X, Y, 'w');
        usleep(50000);
    }

    temp_x.insert(temp_x.begin(), 0);
    temp_y.insert(temp_y.begin(), 0);

    // temp_x.push_back(-1);
    // temp_y.push_back(-1);

    int x_flag;
    int y_flag;

    for (int i = temp_x.size() - 1; i > 0; i--)
    {
        x_flag = temp_x.at(i - 1) - temp_x.at(i);
        y_flag = temp_y.at(i - 1) - temp_y.at(i);

        switch (y_flag)                             // Switch-case for robot orientation when returning back
        {
        case 1:
            switch (*dir % 4)
            {

            case 2:
                curr_loc[1]++;
                Simulator::moveForward();
                break;

            case 3:
                curr_loc[1]++;
                Simulator::turnLeft();
                *dir = *dir - 1;
                Simulator::moveForward();
                break;

            case 1:
                curr_loc[1]++;
                Simulator::turnRight();
                *dir = *dir + 1;
                Simulator::moveForward();
                break;
            }
            break;

        case -1:
            switch (*dir % 4)
            {

            case 3:
                curr_loc[1]--;
                Simulator::turnRight();
                *dir = *dir + 1;
                Simulator::moveForward();
                break;

            case 0:
                curr_loc[1]--;
                Simulator::moveForward();
                break;

            case 1:
                curr_loc[1]--;
                Simulator::turnLeft();
                *dir = *dir - 1;
                Simulator::moveForward();
                break;
            }
            break;
        }

        switch (x_flag)
        {
        case 1:
            switch (*dir % 4)
            {

            case 2:
                curr_loc[0]++;
                Simulator::turnRight();
                *dir = *dir + 1;
                Simulator::moveForward();
                break;

            case 3:
                curr_loc[0]++;
                Simulator::moveForward();
                break;

            case 0:
                curr_loc[0]++;
                Simulator::turnLeft();
                *dir = *dir - 1;
                Simulator::moveForward();
                break;
            }
            break;

        case -1:
            switch (*dir % 4)
            {

            case 2:
                curr_loc[0]--;
                Simulator::turnLeft();
                *dir = *dir - 1;
                Simulator::moveForward();
                break;

            case 0:
                curr_loc[0]--;
                Simulator::turnRight();
                *dir = *dir + 1;
                Simulator::moveForward();
                break;

            case 1:
                curr_loc[0]--;
                Simulator::moveForward();
                break;
            }
            break;
        }
    }
}

void rwa2group11::Algorithm::set_borders()
{

    for (int i = 0; i <= 15; i++)
    {
        for (int j = 0; j <= 15; j++)
        {
            switch (i)
            {
            case 0:
                Simulator::setWall(i, j, 'w');
                break;

            case 15:
                Simulator::setWall(i, j, 'e');
                break;
            }
            switch (j)
            {
            case 0:
                Simulator::setWall(i, j, 's');
                break;

            case 15:
                Simulator::setWall(i, j, 'n');
                break;
            }
        }
    }
}
