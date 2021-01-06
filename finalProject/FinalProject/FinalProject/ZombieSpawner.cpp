#include "ZombieSpawner.h"

ZombieSpawner::ZombieSpawner(SDL_Renderer* renderer, BulletManager* bulletManager, Player* player, TiledMap* tiledMap) : renderer(renderer), bulletManager(bulletManager), player(player), tiledMap(tiledMap) {};

void ZombieSpawner::init() {
	SDL_Surface* surface = IMG_Load("assets/SPRITES/misc/drone/drone-1.png");
	this->zombieTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}

void ZombieSpawner::update() {
	if (SDL_GetTicks() - lastSpawnTime > WAVE_SPAWN_TIME) {

		for (int i = 0; i < currentWave; i++) {
			if (zombiesShot == waveIncrease) {
				currentWave = currentWave + 1;
				waveIncrease = waveIncrease + 5;
			}
			int location = rand() % 8 + 0;

			if (location == 0) {
				zombies.push_back(Zombie{ 32, 193 });
				tiledMap->MAP_DATA[1][5] = 16;
			}
			else if (location == 1) {
				zombies.push_back(Zombie{ 430,32 });
			}
			else if (location == 2) {
				zombies.push_back(Zombie{ 190, 896 });
				//tiledMap->MAP_DATA[1][5] = 32;
			}
			else if (location == 3) {
				zombies.push_back(Zombie{ 400,450 });
				tiledMap->MAP_DATA[1][5] = 16;

			}
			else if (location == 4){
				zombies.push_back(Zombie{ 32, 800 });
				//tiledMap->MAP_DATA[1][5] = 32;
			}
			else if (location == 7){
				tiledMap->MAP_DATA[17][10] = 24;
			}

		}

		lastSpawnTime = SDL_GetTicks();
	}

	if (SDL_GetTicks() - checkTime > 1000) {
		for (auto& z : zombies) {
			int tileNo = 1;
			const int V = MAP_SIZE_X * (MAP_SIZE_Y-1);
			vector<int> adj[V];
			validatePath(tiledMap->MAP_DATA, 16, 30, V, adj, z.tileX, z.tileY);
			z.nextMove = nMove;
			for (int i = 0; i < 31; i++) {
				for (int j = 0; j < 16; j++) {
					if (tileNo == z.nextMove) {
						z.x = j * 32;
						z.y = i * 32;
					}
					tileNo = tileNo + 1;
				}
			}
		}

		checkTime = SDL_GetTicks();
	}

	for (auto& z : zombies) {

		int oldX = z.x;
		int oldY = z.y;
		for (auto& b : bulletManager->bullets) {
			SDL_Rect bulletRect = { b.x, b.y, 10, 10 };
			SDL_Rect zombieRect = { z.x, z.y, 32, 32 };
			SDL_Rect nullRect;
			if (SDL_IntersectRect(&bulletRect, &zombieRect, &nullRect)) 
			{
				b.distance = 1000;
				z.x = 0xCCCCCCCC;
				zombiesShot += 1;
			}

		}

		SDL_Rect playerRect = { player->position.x, player->position.y, 32, 32 };
		SDL_Rect zombieRect = { z.x, z.y, 32, 32 };

		if (SDL_IntersectRect(&playerRect, &zombieRect, &nullRect))
		{
			z.x = 0xCCCCCCCC;
			player->health = player->health - 50;
		}

		SDL_Rect zomPos = { z.x, z.y,20,20 };
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 16; j++) {
				if (tiledMap->MAP_DATA[i][j] == 11 || tiledMap->MAP_DATA[i][j] == 5 || tiledMap->MAP_DATA[i][j] == 19 || tiledMap->MAP_DATA[i][j] == 9 || tiledMap->MAP_DATA[i][j] == 6 || tiledMap->MAP_DATA[i][j] == 10 || tiledMap->MAP_DATA[i][j] == 1 || tiledMap->MAP_DATA[i][j] == 14 || tiledMap->MAP_DATA[i][j] == 15) {
					SDL_Rect mapTile = { j * 32,i * 32,32,32 };
					if (SDL_HasIntersection(&zomPos, &mapTile)) {
						
					}
				}

				SDL_Rect mapTile = { j * 32,i * 32,32,32 };
				if (SDL_HasIntersection(&zomPos, &mapTile)) {
					z.tileX = i;
					z.tileY = j;
				}
			}
		}

	}

	auto remove = std::remove_if(zombies.begin(), zombies.end(), [](const Zombie& z) {return z.x == 0xCCCCCCCC; });
	auto removeBullet = std::remove_if(bulletManager->bullets.begin(), bulletManager->bullets.end(), [](const Bullets& b) {return b.distance == 1000; });
	zombies.erase(remove, zombies.end());
	bulletManager->bullets.erase(removeBullet, bulletManager->bullets.end());

	if (player->removeZombies) {
		for (auto& z : zombies) {
			zombiesShot = zombiesShot + 1;
		}
		zombies.erase(zombies.begin(), zombies.end());
		player->removeZombies = false;
	}

}

void ZombieSpawner::draw() {
	for (auto& z : zombies) {
		SDL_Rect dest = { z.x, z.y, 32, 32 };
		SDL_RenderCopy(renderer, zombieTexture, 0, &dest);
	}
}

void ZombieSpawner::clean()
{
	SDL_DestroyTexture(zombieTexture);
}


//Program to find the shortest path between nodes to help the character escape the maze.

//createEdge - creates edges inbetween the nodes of the graph.
//Parameters passed through - 
//adj - The graph that the edges will be added to.
//firstNode & secondNode - the two nodes that the edges will be created for.
void ZombieSpawner::createEdge(vector<int> adj[], int firstNode, int secondNode) {
	adj[firstNode].push_back(secondNode);
	adj[secondNode].push_back(firstNode);
};

//Breadth First Search algorithm.
bool ZombieSpawner::BFS(vector<int> adj[], int s, int d, const int v, int previousVertex[])
{
	// a queue to check through all the vertices and their adjacent nodes.
	list<int> queue;

	//A boolean array to store what vertexs have been visited during Breadth First Search.
	bool visited[1024];

	//Sets all vertexs as unvisited.
	//Sets the previousVertex to -1 as the graph hasn't been traversed yet.
	for (int i = 0; i < v; i++) {
		visited[i] = false;
		previousVertex[i] = -1;
	}


	//The source is visited first and the distance is set to 0.
	visited[s] = true;
	queue.push_back(s);


	//BFS algorithm
	while (!queue.empty()) {
		//Stores current vertex.
		int u = queue.front();
		queue.pop_front();
		//Iterates through edges.
		for (int i = 0; i < adj[u].size(); i++) {
			//Mark edges as visited if they were not visited before.
			if (visited[adj[u][i]] == false) {
				visited[adj[u][i]] = true;
				previousVertex[adj[u][i]] = u;
				queue.push_back(adj[u][i]);

				// If destination is found return true.
				if (adj[u][i] == d)
					return true;
			}
		}
	}

	//If destination is not found return false.
	return false;
}

//Output Path - Outputs the shortest path from the starting node to the destination node.
void ZombieSpawner::outputPath(vector<int> adj[], int s, int d, int v, int col)
{

	//PreviousVertex stores the previous 'i' values to backtrack and find a path.
	int previousVertex[1024];

	//Run the Breadth First Search on the algorithm
	if (BFS(adj, s, d, v, previousVertex) == false) {
		return;
	}

	// vector path stores the shortest path
	vector<int> path;
	//The destination node is stored in crawl and added to the path vector.
	int crawl = d;
	path.push_back(crawl);
	//Backtracks and adds the previous nodes to the vector path until the starting node has been reached..
	while (previousVertex[crawl] != -1) {
		path.push_back(previousVertex[crawl]);
		crawl = previousVertex[crawl];
	}

	nMove = path[1];

}


//Walkable - Checks if the adjacent node is walkable i.e the node isn't an 'x'.
//Checks if the node is in the maze's dimensions.
//Returns a bool stating whether it is walkable or not.
bool ZombieSpawner::walkable(int i, int j, vector<vector<int>> M, int row, int col)
{
	if ((j < 0 || j >= col) || (i < 0 || i >= row) || M[i][j] == 50)
	{
		return true;
	}

	//Returns true if valid.
	return false;
}

// Find Path - Creates the graph of the maze, setting up each node with its adjacent nodes,
// along with storing data about the start and end nodes (if they are in the file).
// This is done so a Breadth First Search can be executed on the graph.
// Takes the maze vector, the height, width and area of the maze and the graph vector.
void ZombieSpawner::validatePath(vector<vector<int>> M, int col, int row, int V, vector<int> adj[], int tileX, int tileY)
{
	// source and destination
	int s, d;

	// each element of the text file is a node and will be a vertex in the graph.
	int currentVertex = 1;

	//I and J are used to iterate through the text file.
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			//Checks if the current node if valid.
			if (M[i][j] == 50) {
				//Checks if the adjacent nodes are valid, 
				//if they are 2 edges connecting both and created.
				if (walkable(i, j + 1, M, row, col))
					createEdge(adj, currentVertex, currentVertex + 1);
				if (walkable(i, j - 1, M, row, col))
					createEdge(adj, currentVertex, currentVertex - 1);
				if (i < V-1 && walkable(i + 1, j, M, row, col))
					createEdge(adj, currentVertex, currentVertex + col);
				if (i > 0 && walkable(i - 1, j, M, row, col))
					createEdge(adj, currentVertex, currentVertex - col);
			}

			// Store the information of the starting node.
			if (i == player->playerTileX && j == player->playerTileY) {
				s = currentVertex;
			}

			// Store the information of the destination node,
			if (i == tileX && j == tileY) {
				d = currentVertex;
			}
			currentVertex++;
		}
	}



	//Triggers the execution of the method to get the 
	//shortest path where the Breadth First Search method is triggered.
	return outputPath(adj, s, d, V, col);
}

int ZombieSpawner::getZombiesHit()
{
	return zombiesShot;
}

