/*
** EPITECH PROJECT, 2018
** IndieExceptions
** File description:
** Declaration of SaveManager
*/

#ifndef INDIE_STUDIO_SAVE_MAMAGER_HPP
#define INDIE_STUDIO_SAVE_MAMAGER_HPP

#include <fstream>
#include <exception>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

#include "Scene.hpp"

class SaveManager {
public:
    static void saveScene(Scene &scene);
    static void loadScene(const std::string &filename, Scene &scene);
};

#endif //INDIE_STUDIO_SAVE_MAMAGER_HPP
