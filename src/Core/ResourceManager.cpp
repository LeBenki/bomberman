/*
** EPITECH PROJECT, 2018
** ResourceManager
** File description:
** Implementation of ResourceManager
*/

#include "ResourceManager.hpp"

#ifdef __unix__

#include <sys/stat.h>

const char* folder = "/usr/local/share/bomberman/res";

struct stat sb;

const std::string ResourceManager::prefixPath = (stat(folder, &sb) == 0 && S_ISDIR(sb.st_mode)) ? folder : "../res";

#elif defined(_WIN32) || defined(WIN32)
const std::string ResourceManager::prefixPath = "../res";
#endif

const std::string ResourceManager::configPath = "/config.ini";

const std::string ResourceManager::langPath = "/lang.ini";

const std::string ResourceManager::savePath = "/save";

std::map<ResourceManager::Name, std::string> ResourceManager::menuPaths = {
	{MENU_FONT, "/myfont.xml"},
	{MENU_LOADING, "/Loading.png"},
	{MENU_BACKGROUND, "/Menu/menubg.png"},
	{MENU_MAIN_BACKGROUND, "/Menu/Example.png"},
	{MENU_BUTTON, "/Menu/Button.png"},
	{MENU_BUTTON_PRESSED, "/Menu/ButtonPressed.png"},
};

std::map<ResourceManager::Name, std::string> ResourceManager::aiPaths = {
	{AI_MOB, "/ai/star.lua"},
	{AI_BOMBERMAN, "/ai/enemy.lua"},
};

std::map<ResourceManager::Name, std::pair<std::string, std::string>> ResourceManager::paths =
	{{BOMBERMAN1, {
			"/Entities/Player/Bomberman.b3d",
			"/Entities/Player/Skins/Skin1.png"},
	},
	 {BOMBERMAN2, {
			"/Entities/Player/Bomberman.b3d",
			"/Entities/Player/Skins/Skin2.png"},
	 },
	 {BOMBERMAN3, {
			"/Entities/Player/Bomberman.b3d",
			"/Entities/Player/Skins/Skin3.png"},
	 },
	 {BOMBERMAN4, {
			"/Entities/Player/Bomberman.b3d",
			"/Entities/Player/Skins/Skin4.png"},
	 },
	 {BOMB, {
			"/Entities/Bombs/Regular/regular.b3d",
			"/Entities/Bombs/Regular/regular.png"},
	 },
	 {REDBOMB, {
			"/Entities/Bombs/Regular/regular.b3d",
			"/Entities/Bombs/Regular/mega.png"},
	 },
	 {MOUNT, {
			 "/Entities/Mount/mount.md2",
			 "/Entities/Mount/Skin"},
	 },
	 {FIRE, {
			"/cube.obj",
			"/fire.jpg"},
	 },
	 {BEACHMOB, {
	 	        "/Entities/Ennemies/Beach/model.MD2",
                        "/Entities/Ennemies/Beach/skin.png"},
	 },
	 {JUNGLEMOB, {
	                "/Entities/Ennemies/Jungle/model.MD2",
	                "/Entities/Ennemies/Jungle/skin.png"},
	 },
	 {FACTORYMOB, {
                        "/Entities/Ennemies/Factory/model.md2",
                        "/Entities/Ennemies/Factory/skin.png"},
	 },
	 {VOLCANOMOB, {
                        "/Entities/Ennemies/Volcano/model.md2",
                        "/Entities/Ennemies/Volcano/skin.png"},
	 },
	 {ICEMOB, {
	 	        "/Entities/Ennemies/Ice/model.md2",
                        "/Entities/Ennemies/Ice/skin.png"},
	 },
	 {RETROMOB, {
                        "/Entities/Ennemies/Retro/model.md2",
                        "/Entities/Ennemies/Retro/skin.png"},
	 },
	 {CITYMOB, {
                        "/Entities/Ennemies/City/model.md2",
                        "/Entities/Ennemies/City/skin.png"},
	 },
	 {MUSHROOMMOB, {
                        "/Entities/Ennemies/Mushroom/model.md2",
                        "/Entities/Ennemies/Mushroom/skin.png"},
	 },
	 {BONUSSPEED, {
			"/Tiles/Bonus/Roller/voxel.obj",
			"/Tiles/Bonus/Roller/Voxel Texture.png"},
	 },
	 {BONUSSHIELD, {
			"/Tiles/Bonus/Shield/shield.obj",
			"/Tiles/Bonus/Shield/Texture.png"},
	 },
	 {BONUSREDBOMB, {
	 		"/Tiles/Bonus/Mega Bomb/mega.obj",
			"/Tiles/Bonus/Mega Bomb/Texture.png"},
	 },
	 {BONUSRANGE, {
			"/Tiles/Bonus/Fire Up/flame.obj",
			"/Tiles/Bonus/Fire Up/Texture.png"},
	 },
	 {BONUSPASSSOFT, {
	 		"/Tiles/Bonus/Pass/pass.obj",
			"/Tiles/Bonus/Pass/Texture.png"},
	 },
	 {BONUSKICK, {
			"/Tiles/Bonus/Boxing Glove/boxing.obj",
			"/Tiles/Bonus/Boxing Glove/Texture.png"},
	 },
	 {BONUSEGG, {
			"/Tiles/Egg/egg.obj",
			"/Tiles/Egg/Texture.png"},
	 },
	 {BONUSBOMB, {
			"/Tiles/Bonus/Bomb Up/Up.obj",
			"/Tiles/Bonus/Bomb Up/Texture.png"},
	 },
	 {BONUSRANGEMAX, {
			"/Tiles/Bonus/Full Fire/fullfire.obj",
			"/Tiles/Bonus/Full Fire/Texture.png"},
	 },
	 {BONUSSKULL, {
			"/Tiles/Bonus/Skull/voxel.obj",
			"/Tiles/Bonus/Skull/Texture.png"},
	 },
	 {GATECLOSE, {
			"",
			"/Tiles/Gate/close.png"},
	 },
	 {GATEOPEN, {
			"",
			"/Tiles/Gate/open.png"},
	 },
	 {PARTICLES_FIRE, {
			"",
			"/fire.bmp"},
	 },
	 {PARTICLES_SMOKE, {
			"",
			"/smoke.bmp"},
	 },
	 {PARTICLES_SHIELD, {
			"",
			"/shield.bmp"},
	 },
};

std::map<std::string, std::string> ResourceManager::soundPaths = {
	// Effects
	{"Bomb", "/Sound/Effects/Bomb.wav"},
	{"BombKick", "/Sound/Effects/BombKick.wav"},
	{"Door", "/Sound/Effects/Door.wav"},
	{"ItemGet", "/Sound/Effects/ItemGet.wav"},
	{"P1Up", "/Sound/Effects/P1Up.wav"},
	{"PlayerOut", "/Sound/Effects/PlayerOut.wav"},
	{"PlayerWalk", "/Sound/Effects/PlayerWalk.wav"},
	{"Quit", "/Sound/Effects/Quit.wav"},
	{"TimeUp", "/Sound/Effects/TimeUp.wav"},
	{"Applause", "/Sound/Effects/Applause.wav"},
	{"Disease", "/Sound/Effects/Disease.wav"},
	{"TransIn", "/Sound/Effects/TransIn.wav"},

	// Music
	{"Beach", "/Sound/Music/Beach.wav"},
	{"City", "/Sound/Music/City.wav"},
	{"Jungle", "/Sound/Music/Jungle.wav"},
	{"Factory", "/Sound/Music/Factory.wav"},
	{"Ice", "/Sound/Music/Ice.wav"},
	{"Retro", "/Sound/Music/Retro.wav"},
	{"Mushroom", "/Sound/Music/Mushroom.wav"},
	{"Volcano", "/Sound/Music/Volcano.wav"},
	{"Title", "/Sound/Music/Title.wav"},
	{"TitleHD", "/Sound/Music/TitleHD.wav"},

	// Voice
	{"1Up", "/Sound/Voice/1Up.wav"},
	{"BombUp", "/Sound/Voice/BombUp.wav"},
	{"FireUp", "/Sound/Voice/FireUp.wav"},
	{"FullFire", "/Sound/Voice/FullFire.wav"},
	{"Go", "/Sound/Voice/Go.wav"},
	{"HurryUp", "/Sound/Voice/HurryUp.wav"},
	{"Kick", "/Sound/Voice/Kick.wav"},
	{"Ready", "/Sound/Voice/Ready.wav"},
	{"RedBomb", "/Sound/Voice/RedBomb.wav"},
	{"Shield", "/Sound/Voice/Shield.wav"},
	{"Skull", "/Sound/Voice/Skull.wav"},
	{"SpeedUp", "/Sound/Voice/SpeedUp.wav"},
	{"Yeah", "/Sound/Voice/Yeah.wav"},
	{"Start", "/Sound/Voice/Start.wav"},

	//Yoshi
	{"Death", "/Sound/Yoshi/Death.wav"},
	{"Mlem", "/Sound/Yoshi/Mlem.wav"},
	{"Name", "/Sound/Yoshi/Name.wav"}
};

std::map<BiomeManager::Name, ResourceManager::Name> ResourceManager::biomeEnnemies = {
	{BiomeManager::Name::BEACH, BEACHMOB},
	{BiomeManager::Name::JUNGLE, JUNGLEMOB},
	{BiomeManager::Name::FACTORY, FACTORYMOB},
	{BiomeManager::Name::VOLCANO, VOLCANOMOB},
	{BiomeManager::Name::ICE, ICEMOB},
	{BiomeManager::Name::RETRO, RETROMOB},
	{BiomeManager::Name::CITY, CITYMOB},
	{BiomeManager::Name::MUSHROOM, MUSHROOMMOB}
};

std::map<BiomeManager::Name, std::string> ResourceManager::biomeMusics = {
	{BiomeManager::Name::BEACH, "Beach"},
	{BiomeManager::Name::JUNGLE, "Jungle"},
	{BiomeManager::Name::FACTORY, "Factory"},
	{BiomeManager::Name::VOLCANO, "Volcano"},
	{BiomeManager::Name::ICE, "Ice"},
	{BiomeManager::Name::RETRO, "Retro"},
	{BiomeManager::Name::CITY, "City"},
	{BiomeManager::Name::MUSHROOM, "Mushroom"}
};

std::map<ResourceManager::Name, std::string> ResourceManager::iconsPaths = {
	{BONUSBOMB, "/HUD/Icons/Bonus/Up.png"},
	{BONUSKICK, "/HUD/Icons/Bonus/Glove.png"},
	{BONUSSPEED, "/HUD/Icons/Bonus/Roller.png"},
	{BONUSPASSSOFT, "/HUD/Icons/Bonus/Pass.png"},
	{BONUSSHIELD, "/HUD/Icons/Bonus/Shield.png"},
	{BONUSREDBOMB, "/HUD/Icons/Bonus/Mega.png"},
	{BONUSEGG, "/HUD/Icons/Bonus/Egg.png"},
	{BONUSRANGE, "/HUD/Icons/Bonus/Flame.png"},
	{BONUSSKULL, "/HUD/Icons/Bonus/Skull.png"},
	{TIMER_HUD, "/HUD/Timer.png"}
};

std::map<Settings::Language, std::map<ResourceManager::Name, std::string>> ResourceManager::messagesPaths = {
	{Settings::ENGLISH,
		{
			{WIN, "/Messages/Victory.png"},
			{LOSE, "/Messages/Defeat.png"},
			{DRAW, "/Messages/Draw.png"},
		},
	},
	{Settings::FRENCH,
		{
			{WIN, "/Messages/Victoire.png"},
			{LOSE, "/Messages/Defaite.png"},
			{DRAW, "/Messages/Egalite.png"},
		},
	},
	{Settings::SPANISH,
		{
			{WIN, "/Messages/Victoria.png"},
			{LOSE, "/Messages/Derrota.png"},
			{DRAW, "/Messages/Igualdad.png"},
		},
	},
};

std::vector<std::string> ResourceManager::playerIconsPaths =
{
	"/HUD/Icons/Player/White.png",
	"/HUD/Icons/Player/Red.png",
	"/HUD/Icons/Player/Yellow.png",
	"/HUD/Icons/Player/Black.png"
};

const std::string
ResourceManager::getRes(ResourceManager::Type type, ResourceManager::Name name)
{
	if (type == TEXTURE && name == MOUNT)
		return prefixPath + paths[name].second + std::to_string(BiomeManager::getRandomBiome(1, 4)) + ".pcx";
	if (type == MODEL)
		return prefixPath + paths[name].first;
	else
		return prefixPath + paths[name].second;
}

const std::string
ResourceManager::getResIcon(ResourceManager::Name name)
{
	return prefixPath + iconsPaths[name];
}

const std::string
ResourceManager::getMusicByBiome(BiomeManager::Name biome)
{
	return biomeMusics[biome];
}

const std::string
ResourceManager::getPlayerIcon(int id)
{
	return prefixPath + playerIconsPaths[id];
}

const std::string ResourceManager::getConfigPath()
{
	return prefixPath + configPath;
}

const std::string ResourceManager::getLangPath()
{
	return prefixPath + langPath;
}

const std::string ResourceManager::getSavePath()
{
	return prefixPath + savePath;
}

const std::string ResourceManager::getMenuPath(ResourceManager::Name name)
{
	return prefixPath + menuPaths[name];
}

const std::string ResourceManager::getAiPath(ResourceManager::Name name)
{
	return prefixPath + aiPaths[name];
}

const ResourceManager::Name &
ResourceManager::getEnnemyByBiome(BiomeManager::Name biome)
{
	return biomeEnnemies[biome];
}

const std::string ResourceManager::getMessagePath(ResourceManager::Name name,
						  Settings::Language lang)
{
	return prefixPath + messagesPaths[lang][name];
}
