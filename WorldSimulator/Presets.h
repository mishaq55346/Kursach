#pragma once
#include <vector>
#include "Tile.h"

using namespace std;

class Presets
{
public:
	const static int i = 4;
	
	vector<Tile> lots_of_planers = {
	Tile(1,4),
	Tile(2,4),
	Tile(3,4),
	Tile(3,3),
	Tile(2,2),
	Tile(7,8),
	Tile(8,8),
	Tile(9,8),
	Tile(9,7),
	Tile(8,6),
	Tile(2,15),
	Tile(3,15),
	Tile(4,15),
	Tile(4,14),
	Tile(3,13),
	Tile(7,14),
	Tile(8,14),
	Tile(9,14),
	Tile(9,13),
	Tile(8,12),
	Tile(12,5),
	Tile(13,5),
	Tile(14,5),
	Tile(14,4),
	Tile(13,3),
	Tile(12,11),
	Tile(13,11),
	Tile(14,11),
	Tile(14,10),
	Tile(13,9),
	Tile(11,17),
	Tile(12,17),
	Tile(13,17),
	Tile(13,16),
	Tile(12,15),
	Tile(17,17),
	Tile(18,17),
	Tile(19,17),
	Tile(19,16),
	Tile(18,15),
	Tile(17,9),
	Tile(18,9),
	Tile(19,9),
	Tile(19,8),
	Tile(18,7),
	Tile(3, 24),
Tile(4,24),
Tile(5,24),
Tile(5,23),
Tile(4,22),
Tile(23, 8),
Tile(24, 8),
Tile(25, 8),
Tile(25, 7),
Tile(24, 6),
Tile(23, 15),
Tile(24, 15),
Tile(25, 15),
Tile(25, 14),
Tile(24, 13),
Tile(8 ,24),
Tile(9 ,24),
Tile(10, 24),
Tile(10, 23),
Tile(9 ,22),
Tile(14, 23),
Tile(15, 23),
Tile(16, 23),
Tile(16, 22),
Tile(15, 21),
Tile(28, 10),
Tile(29, 10),
Tile(30, 10),
Tile(30, 9),
Tile(29, 8),
Tile(29, 17),
Tile(30, 17),
Tile(31, 17),
Tile(31, 16),
Tile(30, 15),
Tile(35, 15),
Tile(36, 15),
Tile(37, 15),
Tile(37, 14),
Tile(36, 13),
Tile(20, 24),
Tile(21, 24),
Tile(22, 24),
Tile(22, 23),
Tile(21, 22),
Tile(12, 32),
Tile(13, 32),
Tile(14, 32),
Tile(14, 31),
Tile(13, 30),
Tile(1 ,31),
Tile(2 ,31),
Tile(3 ,31),
Tile(3 ,30),
Tile(2 ,29),
Tile(1 ,37),
Tile(2 ,37),
Tile(3 ,37),
Tile(3 ,36),
Tile(2 ,35),
Tile(8 ,37),
Tile(9 ,37),
Tile(10, 37),
Tile(10, 36),
Tile(9 ,35),
Tile(7 ,32	),
Tile(8, 32),
Tile(9, 32),
Tile(9, 31),
Tile(8, 30),
Tile(18, 32),
Tile(19, 32),
Tile(20, 32),
Tile(20, 31),
Tile(19, 30),
Tile(24, 31),
Tile(25, 31),
Tile(26, 31),
Tile(26, 30),
Tile(25, 29),
Tile(26, 24),
Tile(27, 24	),
Tile(27, 23),
Tile(26, 22),
Tile(25, 24),
Tile(31, 26),
Tile(32, 26),
Tile(33, 26),
Tile(33, 25),
Tile(32, 24),
Tile(30, 32),
Tile(31, 32),
Tile(32, 32),
Tile(32, 31),
Tile(31, 30),
Tile(22, 37),
Tile(23, 37),
Tile(24 ,37),
Tile(24, 36),
Tile(23 ,35)
}; 
	
	const static void print(const vector<Tile>& tiles)
			{
			for (const auto t : tiles)
			cout << t.x << " " << t.y << endl;
			cout << endl;
			}
				
};