#!/usr/local/bin/lua

local function debug()
	print("==========================")
	print("Nb Line: ", #map)
	print("Nb Enemy: ", #posEn / 2)
	print("Pos: ", pos[1], pos[2])
	print("Tile size: ", tileSize)
	print("Nb bombs:", #posBomb / 2)
	print("Move:", move)
	print("Max bomb:", nbBomb)
	print("Pass wall:", passWall)
	print("==========================\n")
end

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

local function analyse(z, x, goal)
	--print("analyse")
	--print("max", map[z]:sub(x, x))
	if ((map[z]:sub(x, x) == 'X' or map[z]:sub(x, x) == 'C') and nbBomb == 0 and passWall == 0) or
		(#posEn > 0 and goal.z == z and goal.x == x) then
		return true
	end
	return false
end

local function checkEmpty(z, x)
	if map[z]:sub(x, x) ~= '#' and map[z]:sub(x, x) ~= 'F' then
		return true
	end
	return false
end

local function isRightEmpty(pos)
	return checkEmpty(pos.z, pos.x + 1)
end

local function isLeftEmpty(pos)
	return checkEmpty(pos.z, pos.x - 1)
end

local function isTopEmpty(pos)
	return checkEmpty(pos.z - 1, pos.x)
end

local function isBackEmpty(pos)
	return checkEmpty(pos.z + 1, pos.x)
end

local function checkFree(z, x)
	z = math.floor( z )
	x = math.floor( x )
	if (map[z]:sub(x, x) == ' ' and passWall == 0) or (passWall == 1) then
		return true
	end
	return false
end

local function isRightFree(pos)
	return checkFree(pos.z, pos.x + 1)
end

local function isLeftFree(pos)
	return checkFree(pos.z, pos.x - 1)
end

local function isTopFree(pos)
	return checkFree(pos.z - 1, pos.x)
end

local function isBackFree(pos)
	return checkFree(pos.z + 1, pos.x)
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

local function compare(a, b)
	if a.f == b.f then
		return a.h < b.h
	end
	return a.f < b.f
end

local function cleanBombList()
	local i = 1

	while i <= #posBomb do
		table.insert(bombList, createPos(abs(posBomb[i]) / tileSize + 1,
						 abs(posBomb[i + 1]) / tileSize + 1))
		i = i + 2
	end
end

local function isSafe(pos)
	local abscissa = 0
	local ordinate = 0
	escape = createPos(0, 0)

	for i, bomb in ipairs(bombList) do
		if bomb.z == pos.z and distance(bomb, pos) <= 3 then
			abscissa = 1
			escape.z = bomb.z
		end
		if bomb.x == pos.x and distance(bomb, pos) <= 3 then
			ordinate = 1
			escape.x = bomb.x
		end
	end
	if abscissa == 1 or ordinate == 1 then
		return false
	end
	return true
end


local function findFreePath(pos)
	if (isTopFree(pos) == true) then
		table.insert(paths, 1)
	end
	if (isLeftFree(pos) == true) then
		table.insert(paths, -2)
	end
	if (isRightFree(pos) == true) then
		table.insert(paths, 2)
	end
	if (isBackFree(pos) == true) then
		table.insert(paths, -1)
	end
end

local function randChoosePath()
	math.randomseed(os.time())
	if (#paths == 2 and paths[1] * -1 == paths[2] and move ~= 0 and move ~= 26) then
		return move
	else
		return paths[math.random(#paths)]
	end
end

local function isRightSafe(pos)
	local i = pos.x + 1

	while i <= pos.x + range do
		if (passWall == 0 and map[pos.z]:sub(i, i) ~= ' ') or (map[pos.z]:sub(i, i) == '#' or  map[pos.z]:sub(i, i) == 'F') then
			return false
		end
		i = i + 1
	end
	return true
end

local function isLeftSafe(pos)
	local i = pos.x - 1

	while i <= pos.x - range do
		if (passWall == 0 and map[pos.z]:sub(i, i) ~= ' ') or (map[pos.z]:sub(i, i) == '#' or  map[pos.z]:sub(i, i) == 'F') then
			return false
		end
		i = i - 1
	end
	return true
end

local function isTopSafe(pos)
	local i = pos.z - 1

	while i <= pos.z - range do
		if (passWall == 0 and map[i]:sub(pos.x, pos.x) ~= ' ') or (map[i]:sub(pos.x, pos.x) == '#' or map[i]:sub(pos.x, pos.x) == 'F') then
			return false
		end
		i = i - 1
	end
	return true
end

local function isBackSafe(pos)
	local i = pos.z + 1

	while i <= pos.z + range do
		if (passWall == 0 and map[i]:sub(pos.x, pos.x) ~= ' ') or (map[i]:sub(pos.x, pos.x) == '#' or map[i]:sub(pos.x, pos.x) == 'F') then
			return false
		end
		i = i + 1
	end
	return true
end

local function randChooseSafePath(pos)
	local i = 1
	local safe = {}
	math.randomseed(os.time())
	if #paths == 1 then
		return paths[1]
	end
	while i <= #paths do
		if (paths[i] == 1 and isBackSafe(pos) == true) or (paths[i] == -1 and isTopSafe(pos) == true) or (paths[i] == -2 and isLeftSafe(pos) == true) or (paths[i] == 2 and isRightSafe(pos) == true) then
			table.insert(safe, paths[i])
		end
		i = i + 1
	end
	return safe[math.random(#safe)]
end

local function fleeUp(pos)
	move = 1
	if isLeftEmpty(pos) == true then
		move = -2
	elseif isRightEmpty(pos) == true then
		move = 2
	end
end

local function fleeDown(pos)
	move = -1
	if isLeftEmpty(pos) == true then
		move = -2
	elseif isRightEmpty(pos) == true then
		move = 2
	end
end

local function fleeRight(pos)
	move = 2
	if isTopEmpty(pos) == true then
		move = 1
	elseif isBackEmpty(pos) == true then
		move = -1
	end
end

local function fleeLeft(pos)
	move = -2
	if isTopEmpty(pos) == true then
		move = 1
	elseif isBackEmpty(pos) == true then
		move = -1
	end
end

local function flee(pos)
	if (pos.z > escape.z) then
		fleeUp(pos)
	elseif (pos.z < escape.z) then
		fleeDown(pos)
	elseif (pos.x > escape.x) then
		fleeRight(pos)
	elseif (pos.x < escape.x) then
		fleeLeft(pos)
	elseif (pos.z == escape.z and pos.x == escape.x) then
		move = randChooseSafePath(pos)
	end
end

local function dropBomb(pos, goal)
	--print("drop", pos.z, pos.x)
	if (analyse(pos.z - 1, pos.x, goal) or
		analyse(pos.z + 1, pos.x, goal) or
		analyse(pos.z, pos.x + 1, goal) or
		analyse(pos.z, pos.x - 1, goal)) then
		if isSafe(now) == true then
			return true
		end
	end
	return false
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

local function isDest(coord)
	if (coord.z == posEn[1] and coord.x == posEn[2]) then
		return true
	end
	return false
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
	while current.parent do
		if current.parent.z == z[1] and current.parent.x == x[1] then break end
		current = current.parent
	end
	return current
end

local function choosePath(next)
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

paths = {}
bombList = {}
z = {}
x = {}
zE = {}
xE = {}

pos[1] = abs(pos[1]) / tileSize + 1
pos[2] = abs(pos[2]) / tileSize + 1
z[1], z[2] = splitDec(pos[1])
x[1], x[2] = splitDec(pos[2])
if #posEn > 0 then
	posEn[1] = abs(posEn[1]) / tileSize + 1
	posEn[2] = abs(posEn[2]) / tileSize + 1
	zE[1], zE[2] = splitDec(posEn[1])
	xE[1], xE[2] = splitDec(posEn[2])
	goal = createPos(zE[1], xE[1])
end
now = createPos(pos[1], pos[2])
pos[1] = z[1]
pos[2] = x[1]
if z[2] == 0.0 and x[2] == 0.0 then
	if #posBomb ~= 0 then
		cleanBombList()
	end
	findFreePath(now)
	local drop = dropBomb(now, goal)
	local safe = isSafe(now)
	if  drop == false then
		if #bombList > 0 and safe == true then
			move = 0
		elseif safe == false then
			flee(now)
		elseif #posEn == 0 then
			move = randChoosePath()
		else
			local next = pathFinding()
			move = choosePath(next)
		end
	elseif drop == true then
		move = 26
	end
end
--print("move", move)