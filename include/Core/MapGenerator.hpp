//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MapGenerator class definition
//

#ifndef MAP_GENERATOR_HPP_
# define MAP_GENERATOR_HPP_

# define HARD_WALL_PERC 28
# define SOFT_WALL_PERC 35
# define MOB_NBR 5

# include <iostream>
# include <fstream>
# include <vector>
# include <random>
# include <algorithm>
# include <string>

# include "GameMode.hpp"

typedef struct s_pos {
	int x;
	int y;
} pos_t;

enum RowType {
	EMPTY,
	FULL,
	OTHER
};

enum ElemType {
	HARD,
	SOFT,
	MOB,
	GATE
};

class MapGenerator {
public:
	static std::vector<std::string> generate(pos_t size, GameMode mode);
};

#endif // !MAP_GENERATOR_HPP_
