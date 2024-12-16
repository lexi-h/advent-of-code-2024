#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>


using grid_t = std::vector<std::string>;

void reset_xs(grid_t &g){
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            if(g[i][j] == 'x') g[i][j] = '9';
        }
    }
    return;
}

void print_grid(const grid_t &g){
    for(int i = 0; i < g.size(); ++i){
        std::cout << g[i];
        std::cout << std::endl;
    }
}

bool bounds_check(const grid_t &g, int i, int j){
    bool inbounds = true;
    if(i < 0 || j < 0) inbounds = false;
    //assumes square grid
    if(i >= g.size() || j >= g.size()) inbounds = false;
    return inbounds;
}

int chase_trailhead(grid_t &g, int i, int j, char target){
    if(!bounds_check(g,i,j)) return 0;

    if(g[i][j] == target){
        //done!
        if(target == '9'){
            std::cout << "END found at : " << i << "," << j << std::endl;
            g[i][j] = 'x';
            return 1;
        }

        //still searching for next number...
        //search up down left right 
        char next_target = target + 1;
        return chase_trailhead(g, i-1,j,next_target) +
            chase_trailhead(g, i+1,j,next_target) +
            chase_trailhead(g, i,j-1,next_target) +
            chase_trailhead(g, i,j+1,next_target);

    }

    return 0;
}

int process_grid(grid_t &g){
    int running_total = 0;
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            //found a trailhead
            if(g[i][j] == '0'){
                std::cout << "trailhead found at : " << i << "," << j << std::endl;
                running_total += chase_trailhead(g,i,j,'0');
                reset_xs(g);
            }

        }
    }
    return running_total;
}

int main(int argc, char *argv[]){
    std::cout << "concerning the hiking trails through the lava fields...\n";
    if(argc <= 1){
        std::cout << "Need file argument.\n";
    }

    for(int i = 1; i < argc; ++i){
        std::cout << "arg " << i << ": " << argv[i] << std::endl;
        std::ifstream inputfile(argv[i]);
        grid_t grid;
        std::string line;
        int num_lines = 0;
        //get input
        while(inputfile >> line){
            grid.push_back(line);
        }
        inputfile.close();

        std::cout << "-------\n";
        print_grid(grid);
        int grand_total = process_grid(grid);
        std::cout << "grand total: " << grand_total << std::endl;
    }

    std::cout << "complete\n";
    return 0;
}
