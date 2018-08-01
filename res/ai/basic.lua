#!/usr/local/bin/lua

function abs(num)
    return num < 0 and (num * -1) or num
end

local function roundToNNumber( num, n )
    local mult = 10 ^ (n or 0)
    return math.floor(num * mult + 0.5) / mult
end

local function splitDec(num)
    local integer, decimal = math.modf(roundToNNumber(num, 1))
    return integer, decimal
end

local function debug()
    print("==========================")
    print("Nb Line: ", #map)
    print("Nb Enemy: ", #posEn / 2)
    print("Pos: ", pos[1], pos[2])
    print("Tile size: ", tileSize)
    print("Angle: ", angle)
    print("Tmp:", tmpMove)
    print("==========================\n")
end

local function isRightEmpty()
    if (map[z[1]]:sub(x[1] + 1, x[1] + 1) == ' ') then
        return true
    else
        return false
    end
end

local function isLeftEmpty()
    if (map[z[1]]:sub(x[1] - 1, x[1] - 1) == ' ') then
        return true
    else
        return false
    end
end

local function isTopEmpty()
    if (map[z[1] - 1]:sub(x[1], x[1]) == ' ') then
        return true
    else
        return false
    end
end

local function isBackEmpty()
    if (map[z[1] + 1]:sub(x[1], x[1]) == ' ') then
        return true
    else
        return false
    end
end

local function isFrontFree()
    if move == 1 then
        return isTopEmpty()
    end
    if move == -1 then
        return isBackEmpty()
    end
    if move == 2 then
        return isRightEmpty()
    end
    if move == -2 then
        return isLeftEmpty()
    end
    return false
end

local function findFreePath()
    if (isTopEmpty() == true) then
        if (not(move == -1 and isFrontFree() == true)) then
            table.insert(paths, 1)
        end
    end
    if (isLeftEmpty() == true) then
        if (not(move == 2 and isFrontFree() == true)) then
            table.insert(paths, -2)
        end
    end
    if (isRightEmpty() == true) then
        if (not(move == -2 and isFrontFree() == true)) then
            table.insert(paths, 2)
        end
    end
    if (isBackEmpty() == true) then
        if (not(move == 1 and isFrontFree() == true)) then
            table.insert(paths, -1)
        end
    end
end

local function choosePath()
    math.randomseed(os.time())
    return paths[math.random(#paths)]
end

pos[1] = abs(pos[1]) / tileSize + 1
pos[2] = abs(pos[2]) / tileSize + 1

paths = {}
z = {}
x = {}

z[1], z[2] = splitDec(pos[1])
x[1], x[2] = splitDec(pos[2])

findFreePath()
if (z[2] == 0.0 and x[2] == 0.0) then
    move = choosePath()
end