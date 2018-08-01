#!/usr/local/bin/lua

function sleep(n)
	if n > 0 then os.execute("ping -n " .. tonumber(n+1) .. " localhost > NUL") end
end

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

local function createPos(z, x)
	local pos = {
		z = z,
		x = x
	}
	return pos
end

local function isRightEmpty(pos)
	if (map[pos.z]:sub(pos.x + 1, pos.x + 1) == ' ') then
		return true
	else
		return false
	end
end

local function isLeftEmpty(pos)
	if (map[pos.z]:sub(pos.x - 1, pos.x - 1) == ' ') then
		return true
	else
		return false
	end
end

local function isTopEmpty(pos)
	if (map[pos.z - 1]:sub(pos.x, pos.x) == ' ') then
		return true
	else
		return false
	end
end

local function isBackEmpty(pos)
	if (map[pos.z + 1]:sub(pos.x, pos.x) == ' ') then
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

local function distance(from, to)
	dz = (to.z - from.z) ^ 2
	dx = (to.x - from.x) ^ 2
	local dist = math.sqrt(dz + dx)
	return dist
end

local function g(z, x)
	local from = createPos(pos[1], pos[2])
	local to = createPos(z, x)
	local dist = distance(from, to)
	return dist
end

local function h(z, x)
	local from = createPos(z, x)
	local dist = distance(from, goal)
	return dist
end

local function createNode(zPos, xPos)
	local gVal = g(zPos, xPos)
	local hVal = h(zPos, xPos)
	local fVal = gVal + hVal
	local node = {
		z = zPos,
		x = xPos,
		g = gVal,
		h = hVal,
		f = fVal,
		parent
	}
	return node
end

local function findNeighbors(pos)
	local neighbors = {}
	pos.z = splitDec(pos.z)
	pos.x = splitDec(pos.x)
	if (isTopEmpty(pos) == true) then
		table.insert(neighbors, createNode(pos.z - 1, pos.x))
	end
	if (isLeftEmpty(pos) == true) then
		table.insert(neighbors, createNode(pos.z, pos.x - 1))
	end
	if (isRightEmpty(pos) == true) then
		table.insert(neighbors, createNode(pos.z, pos.x + 1))
	end
	if (isBackEmpty(pos) == true) then
		table.insert(neighbors, createNode(pos.z + 1, pos.x))
	end
	return neighbors
end

local function findFreePath(pos)
    if (isTopEmpty(pos) == true) then
            table.insert(paths, 1)
    end
    if (isLeftEmpty(pos) == true) then
            table.insert(paths, -2)
    end
    if (isRightEmpty(pos) == true) then
            table.insert(paths, 2)
    end
    if (isBackEmpty(pos) == true) then
            table.insert(paths, -1)
    end
end

local function randChoosePath()
    math.randomseed(os.time())
    return paths[math.random(#paths)]
end

local function isDest(coord)
	if (coord.z == posEn[1] and coord.x == posEn[2]) then
		return true
	end
	return false
end

local function compare(a, b)
	if a.f == b.f then
		return a.h < b.h
	end
	return a.f < b.f
end

local function popFirst(list)
	local tmp = list[1]
	table.remove(list, 1)
	return tmp
end

local function popFind(list, elem)
	local tmp
	local pos = -1
	local i = 1

	for k, v in pairs(list) do
		if (v.z == elem.z and v.x == elem.x) then pos = i end
		i = i + 1
	end
	if pos == -1 then return -1 end
	table.remove(list, pos)
	return 0
end

local function isHere(list, elem)
	for k, v in pairs(list) do
		if (v.z == elem.z and v.x == elem.x) then return true end
	end
	return false
end

local function pathFinding()
	local open = {}
	local close = {}
	local neighbors = {}
	local current
	local cost
	local dist

	table.insert(open, createNode(pos[1], pos[2]))
	while #open > 0 do
		current = popFirst(open)
		table.insert(close, current)
		if (current.z == goal.z and current.x == goal.x) then
			break
		end
		neighbors = findNeighbors(current)
		for i, neighbor in ipairs(neighbors) do
			cost = g(current.z, current.x) + distance(current, neighbor)
			if isHere(open, neighbor) == true and cost < g(neighbor.z, neighbor.x) then
				popFind(open, neighbor)
			end
			if isHere(open, neighbor) == false and isHere(close, neighbor) == false then
				neighbor.g = cost
				table.insert(open, neighbor)
				neighbor.parent = current
			end
		end
		table.sort(open, compare)
	end
	if isHere(open, goal) == false and isHere(close, goal) == false then
		blocked = 1
	end
	while current.parent do
		--print(current.z, current.x)
		if current.parent.z == z[1] and current.parent.x == x[1] then break end
		current = current.parent
	end
	return current
end

local function choosePath(next)
	--print("choose", next.z, pos[1], next.x, pos[2])
	if (next.z > pos[1]) then
		move = -1
	elseif (next.z < pos[1]) then
		move = 1
	elseif (next.x > pos[2]) then
		move = 2
	elseif (next.x < pos[2]) then
		move = -2
	end
	return move
end

pos[1] = abs(pos[1]) / tileSize + 1
pos[2] = abs(pos[2]) / tileSize + 1
posEn[1] = abs(posEn[1]) / tileSize + 1
posEn[2] = abs(posEn[2]) / tileSize + 1
--[[move = 1
pos = {}
posEn = {}
map = {
	"#######################",
	"#      #       #   X  #",
	"# # # # # # # # # # # #",
	"#                    X#",
	"# # # # # # # # # # # #",
	"#                     #",
	"# # # # # # # # # # # #",
	"#      #       #      #",
	"# # # # # # # # # # # #",
	"#       XXX           #",
	"# # # # # # # # # # # #",
	"#                     #",
	"# # # # # # # # # # # #",
	"#  #                  #",
	"#######################"
}
map = {
	"###################",
	"#   X X X # XX#X  #",
	"# #X#X#X#X# #X#X# #",
	"#  X X# X   XXXX X#",
	"### # # #X#X#X# #X#",
	"#  X#   X  XXX X  #",
	"# ##### # # #X### #",
	"#XX  XXXX  XX # XX#",
	"# # #X# #X#X#X#X###",
	"# X XXXX XXX XX   #",
	"### #X#####X###X# #",
	"#  XXXXX  X #XXXX #",
	"# # # #X# #X#X### #",
	"#XX #  X XXX    X #",
	"# #X#X#X#X#X#X# # #",
	"#  X    X #X#X#   #",
	"###################"
}
pos[1] = 2
pos[2] = 22
posEn[1] = 2
posEn[2] = 2.4]]

paths = {}
z = {}
x = {}
zE = {}
xE = {}
blocked = 0

z[1], z[2] = splitDec(pos[1])
x[1], x[2] = splitDec(pos[2])
zE[1], zE[2] = splitDec(posEn[1])
xE[1], xE[2] = splitDec(posEn[2])

goal = createPos(zE[1], xE[1])
--print("goal", goal.z, goal.x)
local next = pathFinding()
--print("change pos", blocked, z[2], x[2])
if z[2] == 0.0 and x[2] == 0.0 then
	pos[1] = z[1]
	pos[2] = x[1]
	if (blocked == 1) then
		now = createPos(pos[1], pos[2])
		findFreePath(now)
		move = randChoosePath()
	else
		move = choosePath(next)
	end
end