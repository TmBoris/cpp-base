#pragma once

#include <string>
#include <vector>
#include <map>
#include <deque>
#include <set>
#include <unordered_map>

class Minesweeper {
public:
    struct Cell {
        size_t x = 0;
        size_t y = 0;
    };

    enum class GameStatus {
        NOT_STARTED,
        IN_PROGRESS,
        VICTORY,
        DEFEAT,
    };

    enum CellType {
        CLOSED = -10,
        FLAG = -3,
        BOMB = -1,
    };

    using RenderedField = std::vector<std::string>;

    Minesweeper(size_t width, size_t height, size_t mines_count);
    Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void NewGame(size_t width, size_t height, size_t mines_count);
    void NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines);

    void OpenCell(const Cell& cell);
    void MarkCell(const Cell& cell);

    GameStatus GetGameStatus() const;
    time_t GetGameTime() const;

    RenderedField RenderField() const;

private:
    void FieldCreation(size_t width, size_t height);
    void NumbersOnField();

    time_t start_time_ = -1;
    time_t end_time_ = -1;

    GameStatus curr_status_;
    size_t width_;
    size_t height_;
    size_t mines_count_;
    std::vector<std::vector<int>> playing_field_;
    std::map<int, char> definitions_ = {{0, '-'}};
    std::vector<std::vector<int>> games_field_;
    size_t counter_of_opened_cells_ = 0;
    const std::unordered_map<int, std::string> m_ = {{-10, "-"}, {-3, "?"}, {-1, "*"}, {0, "."}, {1, "1"}, {2, "2"},
                                                     {3, "3"},   {4, "4"},  {5, "5"},  {6, "6"}, {7, "7"}, {8, "8"}};
};
