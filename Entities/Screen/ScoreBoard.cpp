#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
	: ScoreBoard({ 230,230,230 })
{}

ScoreBoard::ScoreBoard(SDL_Color col)
{
	mColor = col;
	SetScore(0);
}


ScoreBoard::~ScoreBoard()
{
	ClearScoreBoard();
}

void ScoreBoard::ClearScoreBoard()
{
	mScore.clear();
}

void ScoreBoard::SetScore(int score)
{
	ClearScoreBoard();

	if (score == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			mScore.push_back(new Texture("0", "SEAS.ttf", 32, mColor));
			mScore[i]->SetParent(this);
			mScore[i]->SetPos(Vector2d(-32.0f * i, 0.0f));
		}
	}
	else
	{
		std::string sscore = std::to_string(score);
		for (int i = 0; i <= sscore.length() - 1; i++)
		{
			mScore.push_back(new Texture(sscore.substr(i, 1), "SEAS.ttf", 32, mColor));
			mScore[i]->SetParent(this);
			mScore[i]->SetPos(Vector2d(-32.0f * (sscore.length() - 1 - i), 0.0f));
		}
	}

}

void ScoreBoard::Render()
{
	for (int i = 0; i < mScore.size(); i++)
		mScore[i]->Render();
}