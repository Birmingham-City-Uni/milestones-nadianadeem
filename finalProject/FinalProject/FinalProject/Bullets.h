#pragma once

//Simple structs for the bullets. Stores their x, y rotation angle and distance travelled.
//This data is used to draw the bullets correctly to the window and delete them accordingly.
struct Bullets {
	float x, y, rotation, distance;
};
