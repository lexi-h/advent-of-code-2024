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
    std::vector<int> coords{-1,-1};
    return coords;
}

void reset_maze(std::vector<std::string> &maze){
    for(int i = 0; i < maze.size(); ++i){
        for(int j = 0; j < maze[i].size(); ++j){
            //std::cout << maze[i][j];
            switch(maze[i][j]){
                case '|':
                case '-':
                case '+':
                    maze[i][j] = '.';
            }
        }
    }
    maze[6][4] = '^';
}

int move_guard(std::vector<std::string> &maze){
    //init
    std::cout << "starting moveguard...\n";
    int total = 0;
    std::cout << "resetting maze...\n";
    reset_maze(maze);
    std::cout << "finding chars...\n";
    std::vector<int> guard = find_char('^', maze);
    std::vector<int> barrel = find_char('O', maze);
    bool barrel_placed = true;
    if(barrel[0] == -1){
        barrel_placed = false;
    }

    bool guard_in_maze = true;
    char guard_direction = 'N';
    bool is_loop = false;
    maze[guard[0]][guard[1]] = '|';

    std::cout << "entering gameloop...\n";
    //gameloop
    while(guard_in_maze){
        //print_maze(maze);
        switch (guard_direction){
            case 'N':
                //we made it out
                if(guard[0] == 0){
                    guard_in_maze = false;
                    break;
                }
                //we found a wall; lets spin
                if(maze[guard[0] - 1][guard[1]] == '#' || 
                        maze[guard[0] - 1][guard[1]] == 'O'){
                    guard_direction = 'E';
                    maze[guard[0]][guard[1]] = '+';
                }
                //should only be accessed in first call from main
                else if(!barrel_placed){
                    //place the barrel temporarily for our simulation
                    char temp = maze[guard[0] - 1][guard[1]];
                    maze[guard[0] - 1][guard[1]] = 'O';
                    //run barrel simulation
                    //should return 1 if is loop, 0 if not
                    //this should be a deep copy
                    std::vector<std::string> tempmaze = maze;
                    total += move_guard(tempmaze);

                    //remove the barrel and continue with the real deal
                    maze[guard[0] - 1][guard[1]] = temp;
                    guard[0]--;
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
                if(maze[guard[0] + 1][guard[1]] == '#' ||
                        maze[guard[0] + 1][guard[1]] == 'O'){
                    guard_direction = 'W';
                    maze[guard[0]][guard[1]] = '+';
                }
                //should only be accessed in first call from main
                else if(!barrel_placed){
                    //place the barrel
                    char temp = maze[guard[0] + 1][guard[1]];
                    maze[guard[0] + 1][guard[1]] = 'O';
                    //run barrel simulation
                    total += move_guard(maze);

                    //reset path
                    maze[guard[0] + 1][guard[1]] = temp;
                    guard[0]++;
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
                if(maze[guard[0]][guard[1] + 1] == '#' ||
                        maze[guard[0]][guard[1] + 1] == 'O'){
                    guard_direction = 'S';
                    maze[guard[0]][guard[1]] = '+';
                }
                //should only be accessed in first call from main
                else if(!barrel_placed){
                    //place the barrel temporarily for our simulation
                    char temp = maze[guard[0]][guard[1] + 1];
                    maze[guard[0]][guard[1] + 1] = 'O';
                    //run barrel simulation
                    //should return 1 if is loop, 0 if not
                    total += move_guard(maze);

                    //remove the barrel and continue with the real deal
                    maze[guard[0]][guard[1] + 1] = temp;
                    guard[1]++;
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
                if(maze[guard[0]][guard[1] - 1] == '#' || 
                        maze[guard[0]][guard[1] - 1] == 'O'){
                    guard_direction = 'N';
                    maze[guard[0]][guard[1]] = '+';
                }
                //should only be accessed in first call from main
                else if(!barrel_placed){
                    //place the barrel temporarily for our simulation
                    char temp = maze[guard[0]][guard[1] - 1];
                    maze[guard[0]][guard[1] - 1] = 'O';
                    //run barrel simulation
                    //should return 1 if is loop, 0 if not
                    total += move_guard(maze);

                    //remove the barrel and continue with the real deal
                    maze[guard[0]][guard[1] - 1] = temp;
                    guard[1]--;
                }
                else{
                    guard[1]--;
                }
                break;
        }

        //update the maze, and perhaps discover if we are looping
        if(maze[guard[0]][guard[1]] == '.'){
            switch(guard_direction){
                case 'N':
                case 'S':
                    maze[guard[0]][guard[1]] = '|';
                    break;
                case 'E':
                case 'W':
                    maze[guard[0]][guard[1]] = '-';
                    break;
            }
        }
        else if(maze[guard[0]][guard[1]] == '|'){
            if (guard_direction == 'N' || guard_direction == 'S'){
                is_loop = true;
                break;
            }
            else{
                maze[guard[0]][guard[1]] = '+';
            }
        }
        else if(maze[guard[0]][guard[1]] == '-'){
            if (guard_direction == 'E' || guard_direction == 'W'){
                is_loop = true;
                break;
            }
            else{
                maze[guard[0]][guard[1]] = '+';
            }
        }
    }

    //debug
    if(is_loop){
        std::cout << "FOUND LOOP\n";
        print_maze(maze);
    }

    return total + is_loop;
}

int main(){
    std::cout << "Concerning the 1518 guard's path:\n";

    std::ifstream inputfile("simpleinput");

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

    int num_loops = move_guard(maze);

    int grand_total = num_loops;
    std::cout << "final maze!\n";
    print_maze(maze);

    std::cout << "there are " << grand_total << " opportunities for barrels" << std::endl;
    return 0;
}
