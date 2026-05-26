#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>
#include <algorithm>

class FileSystemEntity {
public:
    std::string name;
    virtual ~FileSystemEntity() = default;
    virtual long long getSize() const = 0;
};

class File : public FileSystemEntity {
    long long size;
public:
    File(std::string name, long long size) : size(size) { this->name = name; }
    long long getSize() const override { return size; }
};

class Directory : public FileSystemEntity {
public:
    std::vector<FileSystemEntity*> contents;

    Directory(std::string name) { this->name = name; }

    ~Directory() {
        for (auto* entity : contents) delete entity;
    }

    long long getSize() const override {
        long long total = 0;
        for (const auto* entity : contents) {
            total += entity->getSize();
        }
        return total;
    }
};


Directory* build_file_structure(std::string name, std::vector<std::vector<std::string>>& output) {
    Directory* current_dir = new Directory(name);

    while (!output.empty()) {
        std::vector<std::string> line = output.front();

        if (line[0] == "$") {
            if (line[1] == "cd") {
                if (line[2] != "..") {
                    output.erase(output.begin());
                    current_dir->contents.push_back(build_file_structure(line[2], output));
                    continue;
                } else {
                    output.erase(output.begin());
                    return current_dir;
                }
            }
            output.erase(output.begin());
        } else {
            if (line[0] != "dir") {
                current_dir->contents.push_back(new File(line[1], std::stoll(line[0])));
            }
            output.erase(output.begin());
        }
    }
    return current_dir;
}

void collect_dir_sizes(Directory* dir, std::vector<long long>& dir_sizes) {
    dir_sizes.push_back(dir->getSize());
    for (auto* entity : dir->contents) {
        Directory* sub_dir = dynamic_cast<Directory*>(entity);
        if (sub_dir) {
            collect_dir_sizes(sub_dir, dir_sizes);
        }
    }
}

int main() {
    std::string filename = "test.txt";
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return 1;
    }

    std::vector<std::vector<std::string>> output;
    std::string line_str;
    while (std::getline(file, line_str)) {
        std::stringstream ss(line_str);
        std::string word;
        std::vector<std::string> words;
        while (ss >> word) {
            words.push_back(word);
        }
        if (!words.empty()) output.push_back(words);
    }

    if (!output.empty() && output[0][0] == "$" && output[0][1] == "cd" && output[0][2] == "/") {
        output.erase(output.begin());
    }
    Directory* root_container = build_file_structure("/", output);

    std::vector<long long> dir_sizes;
    collect_dir_sizes(root_container, dir_sizes);
    long long total_used = root_container->getSize();

    // Part 1
    long long part1 = 0;
    for (long long size : dir_sizes) {
        if (size <= 100000) part1 += size;
    }
    std::cout << "Part 1: " << part1 << std::endl;

    // Part 2
    long long total_disk = 70000000;
    long long needed_free = 30000000;
    long long current_free = total_disk - total_used;
    long long to_delete = needed_free - current_free;

    long long part2 = total_used;
    for (long long size : dir_sizes) {
        if (size >= to_delete && size < part2) part2 = size;
    }
    std::cout << "Part 2: " << part2 << std::endl;

    delete root_container;
    return 0;
}
