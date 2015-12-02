#include "WorldModel.h"

namespace ConquestOfCastles {

	WorldModel::WorldModel() {}
	Player* WorldModel::Self() { return self; }
	Terrain* WorldModel::Terrain() { return terrain; }
	vector<GoldMine*> WorldModel::GoldMines() { return goldMines; }
	vector<Player*> WorldModel::Players() { return others; }

	int Terrain::Width() { return terrainWidth; }
	int Terrain::Height() { return terrainHeight; }
	int Terrain::Get(int x, int y) { return terrain[x][y]; }

	WorldModel::WorldModel(Value & data)
	{
		//set goldmines
		SetGoldMines(data["objects"][0]);

		//set others
		int othersCount = data["players"][0].Size();
		for (int i = 0; i < othersCount; i++){
			//if the player is myself, it should just update self
			if (data["players"][0][i]["PlayerId"].GetInt() == self->Id())
				SetSelf(data["players"][0][i]);
			else
				others.push_back(new Player(data["players"][0][i]));
		}

	}

	WorldModel::~WorldModel()
	{
		//deleting mines
		for (GoldMine* mine : goldMines)
			delete mine;
		goldMines.clear(); //does this really required?
		
		//deleting players
		for (Player* player : others)
			delete player;
		others.clear();
	}

	void WorldModel::SetGoldMines(Value& data) {
		if (!goldMines.empty()){
			for (GoldMine* mine : goldMines)
				delete mine;
			goldMines.clear();
		}

		int goldMinesCount = data.Size();
		for (int i = 0; i < goldMinesCount; i++)
			goldMines.push_back(new GoldMine(data[i]));
	}

	Player* WorldModel::self = nullptr;

	void WorldModel::SetSelf(Value & data)
	{
		if (self != nullptr)
			delete self;
		self = new Player(data);
	}

	//initializing terrain to null in order to not let SetTerrain delete "shit"
	Terrain* WorldModel::terrain = nullptr;

	void WorldModel::SetTerrain(Value & data)
	{
		if (terrain != nullptr)
			delete terrain;
		//Why should I explicitly say that this class comes from CoC?
		terrain = new ConquestOfCastles::Terrain(data);
	}

	Terrain::Terrain(Value & data)
	{
		int width = data.Size();
		int height = data[0].Size();

		terrainHeight = height;
		terrainWidth = width;

		terrain = new int*[width];
		for (int i = 0; i < width; i++)
			terrain[i] = new int[height];


		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
				terrain[i][j] = data[i][j].GetInt();
	}
	Terrain::~Terrain() {
		for (int i = 0; i < terrainHeight; ++i)
			delete[] terrain[i];
		delete[] terrain;
	}

}