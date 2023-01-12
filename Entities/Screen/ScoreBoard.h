#pragma once
#include "../Textures/Texture.h"
#include <vector>

class ScoreBoard : public GameEntity
{
public:
	void SetScore(int score);
	void Render();

	ScoreBoard();
	ScoreBoard(SDL_Color col);
	~ScoreBoard();
private:
	std::vector<Texture*> mScore;
	void ClearScoreBoard();

	SDL_Color mColor;
};

