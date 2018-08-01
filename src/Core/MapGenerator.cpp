//
// EPITECH PROJECT, 2018
// Indie Studio
// File description:
// MapGenerator class implementation
//

#include "MapGenerator.hpp"

void _checkMapSize(pos_t &size)
{
	if (size.x < 13)
		size.x = 13;
	if (size.y < 11)
		size.y = 11;
	if (size.x % 2 == 0)
		size.x++;
	if (size.y % 2 == 0)
		size.y++;
}

std::string _generateLine(pos_t size, RowType type)
{
	std::string ret;

	for (int i = 0; i < size.x ; i++)
		switch (type) {
			case EMPTY:
				ret += " ";
				break;
			case FULL:
				ret += "#";
				break;
			default:
				i % 2 ? ret += "#" : ret += " ";
		}
	return ret;
}

void _initMap(std::vector<std::string> &content, pos_t size)
{
	for (int i = 0; i < size.y ; i++)
		i % 2 ? content.push_back(_generateLine(size,
			RowType::OTHER))
			: content.push_back(_generateLine(size,
			RowType::EMPTY));
}

void _lockSpawnPos(std::vector<std::string> &content, pos_t size)
{
	content[0][0] = 'S';
	content[0][1] = 'S';
	content[1][0] = 'S';
	content[0][size.x - 1] = 'S';
	content[1][size.x - 1] = 'S';
	content[0][size.x - 2] = 'S';
	content[size.y - 1][size.x - 1] = 'S';
	content[size.y - 1][size.x - 2] = 'S';
	content[size.y - 2][size.x - 1] = 'S';
	content[size.y - 1][0] = 'S';
	content[size.y - 1][1] = 'S';
	content[size.y - 2][0] = 'S';
}

void _unlockSpawnPos(std::vector<std::string> &content)
{
	for (auto &line : content)
		std::replace(line.begin(), line.end(), 'S', ' ');
}

bool cellIsPossibleHardWall(std::vector<std::string> content, pos_t size,
	pos_t cellPos)
{
	return content[cellPos.y][cellPos.x] == ' '
	       && ((cellPos.x - 1 >= 0 && cellPos.x + 1 < size.x
		&& content[cellPos.y][cellPos.x - 1] == '#'
		&& content[cellPos.y][cellPos.x + 1] == '#')
	|| (cellPos.x - 1 == -1 && cellPos.x + 1 < size.x
		&& content[cellPos.y][cellPos.x + 1] == '#')
	|| (cellPos.x - 1 >= 0 && cellPos.x + 1 == size.x
		&& content[cellPos.y][cellPos.x - 1] == '#')
	|| (cellPos.y - 1 >= 0 && cellPos.y + 1 < size.y
		&& content[cellPos.y - 1][cellPos.x] == '#'
		&& content[cellPos.y + 1][cellPos.x] == '#')
	|| (cellPos.y - 1 == -1 && cellPos.y + 1 < size.y
		&& content[cellPos.y + 1][cellPos.x] == '#')
	|| (cellPos.y - 1 >= 0 && cellPos.y + 1 == size.y
		&& content[cellPos.y - 1][cellPos.x] == '#'));
}

std::vector<pos_t> _getHardWallPosiblePositions(std::vector<std::string>
	content, pos_t size)
{
	std::vector<pos_t> emptyCellPos;

	for (int y = 0 ; y < size.y ; y++)
		for (int x = 0 ; x < size.x ; x++)
			if (cellIsPossibleHardWall(content, size, {x,y}))
				emptyCellPos.push_back({x, y});
	return emptyCellPos;
}

std::vector<pos_t> _getSoftWallPosiblePositions(std::vector<std::string>
	content, pos_t size)
{
	std::vector<pos_t> emptyCellPos;

	for (int y = 0 ; y < size.y ; y++)
		for (int x = 0 ; x < size.x ; x++)
			if (content[y][x] == ' ')
				emptyCellPos.push_back({x, y});
	return emptyCellPos;
}

bool haveAdjacentEmptyTile(std::vector<std::string> content, pos_t size,
                            pos_t cellPos)
{
	return content[cellPos.y][cellPos.x] == ' '
	       && ((cellPos.y + 1 < size.y && content[cellPos.y + 1][cellPos.x] == ' ')
		|| (cellPos.y - 1 > 0 && content[cellPos.y - 1][cellPos.x] == ' ')
                || (cellPos.x + 1 < size.x && content[cellPos.y][cellPos.x + 1] == ' ')
                || (cellPos.x - 1 > 0 && content[cellPos.y][cellPos.x - 1] == ' '));
}

std::vector<pos_t> _getMobAndGatelPosiblePositions(std::vector<std::string>
                                                   content, pos_t size)
{
	std::vector<pos_t> emptyCellPos;

	for (int y = 0 ; y < size.y ; y++)
		for (int x = 0 ; x < size.x ; x++)
			if (content[y][x] == ' ' &&
			    (y >= size.y / 2 || x >= size.x / 2)
				&& haveAdjacentEmptyTile(content, size, {x, y}))
				emptyCellPos.push_back({x, y});
	return emptyCellPos;
}

void _addElems(std::vector<std::string> &content, int nbr,
               std::vector<pos_t> &emptyCellsPos, ElemType type)
{
	std::mt19937 rng;

	rng.seed(std::random_device()());
	for (int i = 0 ; i < nbr ; i++) {
		std::uniform_int_distribution<std::mt19937::result_type>
		distribution(0, emptyCellsPos.size() - 1);
		auto index = distribution(rng);
		auto randomPos = emptyCellsPos[index];
		switch (type) {
			case HARD:
				content[randomPos.y][randomPos.x] = '#';
				break;
			case SOFT:
				content[randomPos.y][randomPos.x] = 'X';
				break;
			case MOB:
				content[randomPos.y][randomPos.x] = 'M';
				break;
			case GATE:
				content[randomPos.y][randomPos.x] = 'G';
				break;
		}
		emptyCellsPos.erase(emptyCellsPos.begin() + index);
	}
}

void fillSurrounedTiles(std::vector<std::string> &content, pos_t size)
{
	for (int y = 1 ; y < size.y ; y++)
		for (int x = 1 ; x < size.x ; x++)
			if (content[y][x + 1] == '#'
				&& content[y][x - 1] == '#'
				&& content[y + 1][x] == '#'
				&& content[y - 1][x] == '#')
			content[y][x] = '#';
}

void _addInternalWalls(std::vector<std::string> &content, pos_t size,
                       GameMode mode)
{
	int cellNbr = 0;
	for (const auto &line : content)
		cellNbr += line.length();

	int staticHardWallNumber = ((size.x - 1) / 2) * ((size.y - 1) / 2);
	int totalHardWallNumber = HARD_WALL_PERC * cellNbr / 100;

	int softWallsToAdd =
		(mode == GameMode::PVP ? SOFT_WALL_PERC : SOFT_WALL_PERC - 10)
		* cellNbr / 100;
	int hardWallsToAdd = totalHardWallNumber - staticHardWallNumber;

	auto hardWallPossiblePos = _getHardWallPosiblePositions(content, size);
	_addElems(content, hardWallsToAdd, hardWallPossiblePos, ElemType::HARD);

	auto softWallPossiblePos = _getSoftWallPosiblePositions(content, size);
	_addElems(content, softWallsToAdd, softWallPossiblePos, ElemType::SOFT);
}

void _addMobsAndGate(std::vector<std::string> &content, pos_t size)
{
	auto mobAndGatePossiblePos = _getMobAndGatelPosiblePositions(content,
		size);
	_addElems(content, MOB_NBR, mobAndGatePossiblePos, ElemType::MOB);
	_addElems(content, 1, mobAndGatePossiblePos, ElemType::GATE);
}

void _addExternalWalls(std::vector<std::string> &content, pos_t size)
{
	std::vector<std::string> ret;

	ret.push_back(_generateLine(size, RowType::FULL));
	ret.insert(ret.end(), content.begin(), content.end());
	ret.push_back(_generateLine(size, RowType::FULL));
	for (auto &line : ret)
		line = "#" + line + "#";
	content = ret;
}

std::vector<std::string> MapGenerator::generate(pos_t size, GameMode mode)
{
	std::vector<std::string> mapContent;

	_checkMapSize(size);
	_initMap(mapContent, size);
	_lockSpawnPos(mapContent, size);
	_addInternalWalls(mapContent, size, mode);
	if (mode == GameMode::PVE)
		_addMobsAndGate(mapContent, size);
	_addExternalWalls(mapContent, size);
	fillSurrounedTiles(mapContent, size);
	_unlockSpawnPos(mapContent);
	return mapContent;
}
