#include "minesweeper.h"

#include <random>

void Minesweeper::FieldCreation(size_t width, size_t height) {
    playing_field_.clear();
    games_field_.clear();
    width_ = width;
    height_ = height;
    std::vector<int> tmp(width);
    std::vector<int> games(width, CellType::CLOSED);
    for (size_t i = 0; i < height; ++i) {
        playing_field_.push_back(tmp);
        games_field_.push_back(games);
    }
}
void Minesweeper::NumbersOnField() {
    size_t counter;
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            if (playing_field_[i][j] == 0) {
                counter = 0;
                for (int x = -1; x < 2; ++x) {
                    for (int y = -1; y < 2; ++y) {
                        if (0 <= i + x && i + x < height_ && 0 <= j + y && j + y < width_ &&
                            playing_field_[i + x][j + y] == CellType::BOMB) {
                            counter++;
                        }
                    }
                }
                playing_field_[i][j] = counter;
            }
        }
    }
}
Minesweeper::Minesweeper(size_t width, size_t height, size_t mines_count) {
    NewGame(width, height, mines_count);
}
Minesweeper::Minesweeper(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    NewGame(width, height, cells_with_mines);
}
void Minesweeper::NewGame(size_t width, size_t height, size_t mines_count) {
    std::vector<Cell> tmp;
    for (size_t i = 0; i < width; ++i) {
        for (size_t j = 0; j < height; ++j) {
            Cell c;
            c.x = i;
            c.y = j;
            tmp.push_back(c);
        }
    }
    std::shuffle(tmp.begin(), tmp.end(), std::mt19937(std::random_device()()));
    tmp.resize(mines_count);
    NewGame(width, height, tmp);
}
void Minesweeper::NewGame(size_t width, size_t height, const std::vector<Cell>& cells_with_mines) {
    FieldCreation(width, height);
    mines_count_ = cells_with_mines.size();
    for (auto& cell : cells_with_mines) {
        playing_field_[cell.y][cell.x] = CellType::BOMB;
    }
    NumbersOnField();
    curr_status_ = GameStatus::NOT_STARTED;
    if (mines_count_ == 0) {
        curr_status_ = GameStatus::VICTORY;
    }
}
void Minesweeper::MarkCell(const Minesweeper::Cell& cell) {
    if (curr_status_ != GameStatus::DEFEAT && curr_status_ != GameStatus::VICTORY) {
        if (games_field_[cell.y][cell.x] == CellType::CLOSED) {
            games_field_[cell.y][cell.x] = CellType::FLAG;
        } else if (games_field_[cell.y][cell.x] == CellType::FLAG) {
            games_field_[cell.y][cell.x] = CellType::CLOSED;
        }
    }
}
void Minesweeper::OpenCell(const Minesweeper::Cell& cell) {
    std::deque<std::pair<size_t, size_t>> for_open;
    std::set<std::pair<size_t, size_t>> already_done;
    if (curr_status_ == GameStatus::DEFEAT || curr_status_ == GameStatus::VICTORY ||
        games_field_[cell.y][cell.x] == CellType::FLAG) {
        return;
    } else {
        if (playing_field_[cell.y][cell.x] == CellType::BOMB) {
            games_field_ = playing_field_;
            curr_status_ = GameStatus::DEFEAT;
            end_time_ = time(0);
        } else if (playing_field_[cell.y][cell.x] > 0) {
            games_field_[cell.y][cell.x] = playing_field_[cell.y][cell.x];
            if (counter_of_opened_cells_ == 0) {
                start_time_ = time(0);
                curr_status_ = GameStatus::IN_PROGRESS;
            }
            counter_of_opened_cells_++;
            if (counter_of_opened_cells_ == width_ * height_ - mines_count_) {
                curr_status_ = GameStatus::VICTORY;
                end_time_ = time(0);
            }
        } else {
            already_done.insert(std::make_pair(cell.x, cell.y));
            for_open.push_back(std::make_pair(cell.x, cell.y));
            Cell tmp;
            while (!for_open.empty()) {
                tmp.x = for_open.front().first;
                tmp.y = for_open.front().second;
                for_open.pop_front();
                if (playing_field_[tmp.y][tmp.x] == 0) {
                    for (int x = -1; x < 2; ++x) {
                        for (int y = -1; y < 2; ++y) {
                            if (!already_done.contains(std::make_pair(tmp.x + x, tmp.y + y)) && tmp.x + x < width_ &&
                                tmp.y + y < height_ && games_field_[tmp.y + y][tmp.x + x] != CellType::FLAG) {
                                for_open.push_back(std::make_pair(tmp.x + x, tmp.y + y));
                                already_done.insert(std::make_pair(tmp.x + x, tmp.y + y));
                            }
                        }
                    }
                }
                games_field_[tmp.y][tmp.x] = playing_field_[tmp.y][tmp.x];
                if (counter_of_opened_cells_ == 0) {
                    start_time_ = time(0);
                    curr_status_ = GameStatus::IN_PROGRESS;
                }
                counter_of_opened_cells_++;
                if (counter_of_opened_cells_ == width_ * height_ - mines_count_) {
                    curr_status_ = GameStatus::VICTORY;
                    end_time_ = time(0);
                }
            }
        }
    }
}

Minesweeper::GameStatus Minesweeper::GetGameStatus() const {
    return curr_status_;
}
time_t Minesweeper::GetGameTime() const {
    if (end_time_ == -1 && start_time_ == -1) {
        return 0;
    } else if (end_time_ == -1) {
        return time(0) - start_time_;
    }
    return end_time_ - start_time_;
}
Minesweeper::RenderedField Minesweeper::RenderField() const {
    RenderedField ans;
    std::string for_ans;
    for (auto& x : games_field_) {
        for (auto y : x) {
            for_ans += m_.at(y);
        }
        ans.push_back(for_ans);
        for_ans = "";
    }
    return ans;
}