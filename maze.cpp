//
// Created by zacky on 7/18/2021.
//
#include "maze.h"
Maze::Maze(const int Size, SDL_Renderer *renderer, int height, std::pair<int,int> start,std::pair<int,int> end) {
    this->size = Size;
    interv = height;
    this->renderer = renderer;
    this->start = start;
    this->end = end;

    // sets the boundaries to true so it wont visit them
    for (int i = 0; i <=size+1;i++){
        for (int j =0; j <= size+1; j++){
            if (i == 0 || j == 0 || i == size+1 || j== size+1) visited[i][j] = true;
        }
    }

    // sets the neighbors
    for (int i = 1; i <= size; i++){
        for (int j = 1; j <= size; j++){
            // checks left, right, up, and down
            // only the borders will be visited
            if (!visited[i+1][j]){
                neighbors[i][j].emplace_back(i+1,j);
            }
            if (!visited[i-1][j]){
                neighbors[i][j].emplace_back(i-1,j);
            }
            if (!visited[i][j+1]){
                neighbors[i][j].emplace_back(i,j+1);
            }
            if (!visited[i][j-1]){
                neighbors[i][j].emplace_back(i,j-1);
            }
        }
    }
    // initailizes the distance of the start point to 0
    dist[start.first][start.second].push_back(0);

    // creates the custom maze
    Create();

    // solves the maze
    BFS(start.first, start.second);

    // gets points for solution
    solve(cameFrom[end.first][end.second][0].first,cameFrom[end.first][end.second][0].second);

    // draws the solution
    draw();
}
void Maze::Create() {
    // while they are still building the maze
    bool build = true;

    SDL_Event e;
    SDL_PumpEvents();

    // x and y cords of the mouse
    int xMouse = 1,yMouse = 1;

    while (build){
        while(SDL_PollEvent(&e) != 0){
            if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)){
                SDL_GetGlobalMouseState(&xMouse,&yMouse);
                xMouse -= posX;
                yMouse -= posY;
                int newX = xMouse / interv * interv;
                int newY = yMouse / interv * interv;

                // base case (if it hits the start or ends the creation)
                if (newX+interv == start.first*interv && newY+interv == start.second * interv || newX + interv == end.first * interv && newY + interv == end.second * interv){
                    build = false;
                    break;
                }

                // creates and draws the rect
                SDL_Rect rect = {newX, newY, interv, interv};

                SDL_SetRenderDrawColor(renderer, 230, 250, 47, SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(renderer, &rect);

                // updates the screen
                SDL_RenderPresent(renderer);

                // makes the walls visited so when bfs runs it wont go there
                visited[newX / interv + 1][newY / interv + 1] = true;
            }
        }
    }
}
void Maze::BFS(int x, int y) {

    visited[x][y] = true;
    q.emplace(x,y);
    while (!q.empty()){
        std::pair<int,int> front = q.front();
        q.pop();
        if (front.first == end.first && front.second == end.second){
            return;
        }
        for (std::pair<int,int> neighbor:neighbors[front.first][front.second]){
            if (!visited[neighbor.first][neighbor.second]){
                // neighbor has not been visited yet
                visited[neighbor.first][neighbor.second] = true;

                // dist from original point
                long long min = dist[front.first][front.second][0];

                // adds the dist and where it came from
                dist[neighbor.first][neighbor.second].push_back(min + 1);
                cameFrom[neighbor.first][neighbor.second].emplace_back(front.first,front.second);

                q.emplace(neighbor.first, neighbor.second);

            }
        }
    }

}
void Maze::solve(int x, int y) {
    // if it gets to the start then we are finished
    if (x == start.first && y == start.second) return;

    drawing.emplace_back(x,y);

    // gets the next point
    solve(cameFrom[x][y][0].first, cameFrom[x][y][0].second);
}
void Maze::draw(){
    // sets color of line
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    // iterates through the points
    for (std::pair<int,int> Pair:drawing){
        // creates the rect
        SDL_Rect rect = {(Pair.first - 1)*interv, (Pair.second - 1)*interv, interv, interv};

        // draws the rect
        SDL_RenderFillRect(renderer, &rect);
    }
    // updates the screen
    SDL_RenderPresent(renderer);
    SDL_Delay(50000000);
}