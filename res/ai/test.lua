#!/usr/local/bin/lua

function abs(num)
	return num < 0 and (num * -1) or num
end

local function g(z, x)
	dz = abs(z - 13)
	dx = abs(x - 13)
	return (dz + dx)
end

local function h(z, x)
	dz = abs(2 - z)
	dx = abs(2 - x)
	return (dz + dx)
end

local function createNode(zPos, xPos, visited)
	local gVal = g(zPos, xPos)
	local hVal = h(zPos, xPos)
	local node = {
		z = zPos,
		x = xPos,
		g = gVal,
		h = hVal,
		f = gVal + hVal,
		visited = visited or false
	}
	return node
end

local function compare(a, b)
	return a.f < b.f
end

open = {}
local x

for i = 1, 4 do
	if (i % 2 == 0) then x = i else x = i - 2 end
	table.insert(open, createNode(1, x, false))
end

for k, v in pairs(open) do
	print(v.f)
end
print("===")
table.sort(open, compare)
print("first:", open[1].f)
table.remove(open, 1)
for k, v in pairs(open) do
	print(v.f)
end