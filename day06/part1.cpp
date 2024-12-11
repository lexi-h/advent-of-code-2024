#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void print_maze(std::vector<std::string> maze){
    for(int i = 0; i < maze.size(); ++i){
        std::cout << maze[i] << std::endl;
    }
    return;
}

std::vector<int> find_char(char c, std::vector<std::string> maze){
    //std::cout << "time to find " << c << std::endl;
    for(int i = 0; i < maze.size(); ++i){
        for(int j = 0; j < maze[i].size(); ++j){
            //std::cout << maze[i][j];
            if(maze[i][j] == c){
                //std::cout << i << "," << j << std::endl;
                std::vector<int> coords{i,j};
                //std::cout << coords[0] << "," << coords[1] << std::endl;
                return coords;
            }
        }
        //std::cout << std::endl;
    }
    //not found... :(
    std::vector<int> coords(-1,-1);
    return coords;
}

int move_guard(std::vector<std::string> &maze){
    std::vector<int> guard = find_char('^', maze);

    bool guard_in_maze = true;
    char guard_direction = 'N';
    int occupied = 1;
    while(guard_in_maze){
        switch (guard_direction){
            case 'N':
                if(guard[0] == 0){
                    guard_in_maze = false;
                    break;
                }
                if(maze[guard[0] - 1][guard[1]] == '#'){
                    guard_direction = 'E';
                }
                else{
                    guard[0]--;
                }
                break;
            case 'S':
                if(guard[0] >= maze.size() - 1){
                    guard_in_maze = false;
                    break;
                }
                if(maze[guard[0] + 1][guard[1]] == '#'){
                    guard_direction = 'W';
                }
                else{
                    guard[0]++;
                }
                break;
            case 'E':
                if(guard[1] >= maze[guard[0]].size() - 1){
                    guard_in_maze = false;
                    break;
                }
                if(maze[guard[0]][guard[1] + 1] == '#'){
                    guard_direction = 'S';
                }
                else{
                    guard[1]++;
                }
                break;
            case 'W':
                if(guard[1] == 0){
                    guard_in_maze = false;
                    break;
                }
                if(maze[guard[0]][guard[1] - 1] == '#'){
                    guard_direction = 'N';
                }
                else{
                    guard[1]--;
                }
                break;
        }
        if(maze[guard[0]][guard[1]] == '.'){
            ++occupied;
            maze[guard[0]][guard[1]] = 'X';
        }
    }

    return occupied;
}

int main(){
    std::cout << "Concerning the 1518 guard's path:\n";

    std::ifstream inputfile("input");

    std::vector<std::string> maze;
    if(inputfile.is_open()){
        std::string maze_row = "";
        while(getline(inputfile, maze_row)){
            maze.push_back(maze_row);
        }
    }
    else{
        std::cout << "could not open file :(\n";
    }
    inputfile.close();

    print_maze(maze);

    int spaces_occupied = move_guard(maze);

    int grand_total = spaces_occupied;
    std::cout << "final maze!\n";
    print_maze(maze);

    std::cout << "the guard shall visit " << grand_total << " tiles" << std::endl;
    return 0;
}
