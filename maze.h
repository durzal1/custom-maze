//
// Created by zacky on 7/18/2021.
//

#ifndef CUSTOM_MAZE_MAZE_H
#define CUSTOM_MAZE_MAZE_H
#include <bits/stdc++.h>
#include <SDL2/SDL.h>

class Maze{
public:
    // constants (102 instead of 100 so we can set the 0th and nth visited to true, makes it easier)
    static const int max = 102;

    const int posX = 450, posY = 30;

    // dimensions of the grid (size x size)
    int size;

    // SDL renderer used for drawing
    SDL_Renderer *renderer;

    // height of each square in pixels
    int interv;

    // start and end pos
    std::pair<int,int> start;
    std::pair<int,int> end;

    /// vectors

    // the nodes that have been visited
    bool visited[max][max];

    // initializes all the neighbors of every node
    std::vector<std::pair<int,int>> neighbors[max][max];

    // the correct path to the end (given the x,y cords of the points)
    std::vector<std::pair<int,int>> drawing;

    /// for the solving


    // the cords of the parent of the node
    std::vector<std::pair<int,int>> cameFrom[max][max];

    // the dist away from start
    std::vector<long long> dist[max][max];

    // que
    std::queue<std::pair<int,int>>q;

    // constructor
    Maze(const int Size, SDL_Renderer* renderer, int height, std::pair<int,int> start,std::pair<int,int> end);

    // create the grid
    void Create();

    // uses bfs to find the fastest path from start to end
    void BFS(int x, int y);

    // gets the points of the solution
    void solve(int x, int y);

    // draws the points of the solution
    void draw();
};
#endif //CUSTOM_MAZE_MAZE_H
