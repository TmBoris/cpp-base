#pragma once

#include <string>
#include <string_view>
#include <vector>

class UnixPath {
private:
    std::vector<std::string> initial_dir_;
    std::vector<std::string> curr_abs_dir_;
    std::vector<std::string> path_;

public:
    UnixPath(std::string_view initial_dir);

    void ChangeDirectory(std::string_view path);

    std::string GetAbsolutePath() const;
    std::string GetRelativePath() const;
};
