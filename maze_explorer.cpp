/*
Author: Ryan McCamy
Assignment: Maze Explorer
Description: This program runs a simple maze that the user navigates.
*/

#include <iostream>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>

const int WIDTH = 15;
const int HEIGHT = 15;
const char WALL = '#';
const char PATH = ' ';
const char START = 'S';
const char END = 'E';
const char PLAYER = '.';

struct Position {
    int x, y;
};

void initializeMaze(std::vector<std::vector<char>>& maze) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            maze[i][j] = WALL;
        }
    }
}

void generateMaze(std::vector<std::vector<char>>& maze, Position start) {
    std::stack<Position> stack;
    stack.push(start);
    maze[start.y][start.x] = PATH;

    std::vector<Position> directions = {{2, 0}, {-2, 0}, {0, 2}, {0, -2}};
    std::srand(std::time(0));

    while (!stack.empty()) {
        Position current = stack.top();
        std::vector<Position> neighbors;

        for (auto& dir : directions) {
            Position neighbor = {current.x + dir.x, current.y + dir.y};
            if (neighbor.x > 0 && neighbor.x < WIDTH - 1 && neighbor.y > 0 && neighbor.y < HEIGHT - 1) {
                if (maze[neighbor.y][neighbor.x] == WALL) {
                    neighbors.push_back(neighbor);
                }
            }
        }

        if (!neighbors.empty()) {
            Position next = neighbors[std::rand() % neighbors.size()];
            maze[next.y][next.x] = PATH;
            maze[(current.y + next.y) / 2][(current.x + next.x) / 2] = PATH;
            stack.push(next);
        } else {
            stack.pop();
        }
    }
}

void printMaze(const std::vector<std::vector<char>>& maze, Position player) {
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            if (i == player.y && j == player.x) {
                std::cout << PLAYER;
            } else {
                std::cout << maze[i][j];
            }
        }
        std::cout << '\n';
    }
}

bool isValidMove(const std::vector<std::vector<char>>& maze, Position pos) {
    return pos.x >= 0 && pos.x < WIDTH && pos.y >= 0 && pos.y < HEIGHT && maze[pos.y][pos.x] != WALL;
}

int main() {
    std::vector<std::vector<char>> maze(HEIGHT, std::vector<char>(WIDTH));
    Position start = {1, 1};
    Position end = {WIDTH - 2, HEIGHT - 2};
    Position player = start;

    initializeMaze(maze);
    generateMaze(maze, start);
    maze[start.y][start.x] = START;
    maze[end.y][end.x] = END;

    char move;
    while (true) {
        system("clear"); // Use "cls" for Windows
        printMaze(maze, player);
        std::cout << "Move (WASD): ";
        std::cin >> move;

        Position newPos = player;
        if (move == 'W' || move == 'w') newPos.y--;
        else if (move == 'S' || move == 's') newPos.y++;
        else if (move == 'A' || move == 'a') newPos.x--;
        else if (move == 'D' || move == 'd') newPos.x++;

        if (isValidMove(maze, newPos)) {
            player = newPos;
        }

        if (player.x == end.x && player.y == end.y) {
            system("clear"); // Use "cls" for Windows
            printMaze(maze, player);
            std::cout << "Congratulations! You've reached the exit!\n";
            break;
        }
    }

    return 0;
}
