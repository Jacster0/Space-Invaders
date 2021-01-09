#pragma once
#include <memory>
#include <vector>
#include "Rectangle.h"
#include "Shape.h"
#include <numbers>
#include "Star.h"

//This class handles screen related background stuff (for example drawing the background)
//And handling the game over aftermath

enum ReturnCode { PlayAgain = 1, Quit = 256 /*The enum value SDL_Quit is 256 so we use the same value for compatability*/ };

struct SDL_Texture;
class Renderer;
class BackGroundScreenManager {
public:
    BackGroundScreenManager(const std::shared_ptr<Renderer>& renderer, int numLives);
    ~BackGroundScreenManager();
    void Show();
    int ShowGameOverDisplay();
    void HandleGameOverUserInput();
    void Update(int score);
    void DefenderHit();
    void ClearScreen();

    void CreateStarField();
    void DrawStarField();
    void UpdateStarField();
    
    void Reset(bool playerWon);
private:
    void ScaleStarField();

    void CopyTextureToRenderer(SDL_Texture* texture, int width, int height, int xPos, int yPos);
    SDL_Texture* CreateTextTexture(const std::string& text, int r = 255, int g = 255, int b = 255);

    std::shared_ptr<Renderer> m_renderer;
    std::vector<std::unique_ptr<Shape>> m_defenderLives;
    std::vector<std::unique_ptr<Shape>> m_starField;
    std::vector<Star> m_originalStars;

    SDL_Texture* m_playerScoreTexture     = nullptr;
    SDL_Texture* m_playerHighscoreTexture = nullptr;
    SDL_Texture* m_gameOverTexture        = nullptr;
    SDL_Texture* m_playAgainOrQuitTexture = nullptr;
    SDL_Texture* m_playerLivesTexture     = nullptr;

    int m_numDefenderLives = 0;
    int m_playerScore = 0;
    int m_playerHighscore = 0;

    int m_gameOverReturnCode = 0;

    constexpr static auto m_yPos = 820.0f;

    constexpr static auto m_width = 30;
    constexpr static auto m_height = 30;

    constexpr static auto m_sineWaveAmplitude = 2.0f;
    constexpr static auto m_sineWaveFrequency = 0.25f; 
    constexpr static auto m_sineWavePhase     = 0.5f;

    constexpr static auto twoPi = 2.0f * std::numbers::pi_v<float>;
};
