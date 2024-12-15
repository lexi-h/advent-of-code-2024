#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Tile{
    public:
        char tile;
        bool is_antinode;

        Tile(){
            tile = '.';
            is_antinode = false;
        }

        Tile(char newtile){
            tile = newtile;
            is_antinode = false;
        }
};

using grid_t = std::vector<std::vector<Tile>>;
using dict_t = std::map<char, std::vector<std::pair<int,int>>>;

void print_dict(const dict_t &d){
    std::cout << "{ ";
    for (const auto& [key,v] : d){
        std::cout << key << " : ";
        for(int i = 0; i < v.size(); ++i){
            std::cout << "(" << v[i].first << "," << v[i].second << ")";
            std::cout << ", ";
        }
    }
    std::cout << "}\n";
}

void print_grid(const grid_t &g){
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            std::cout << g[i][j].tile;
        }
        std::cout << std::endl;
    }
}

int count_and_print_antinodes(const grid_t &g){
    int antinode_counter = 0;
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            if(g[i][j].is_antinode){
                std::cout << '#';
                ++antinode_counter;
            }
            else{
                std::cout << '.';
            }
        }
        std::cout << std::endl;
    }
    return antinode_counter;
}

void build_antenna_dict(const grid_t &g, dict_t &antenna_dict){
    //dict
    // {'A' : [1,1], [3,7]; 'B' : [4,10]}
    //dict_t antenna_dict;
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            char antenna = g[i][j].tile;
            //std::cout << antenna;
            //found a letter
            if(antenna != '.'){
                std::pair<int,int> p(i,j);
                antenna_dict[antenna].push_back(p);
            }
        }
        std::cout << std::endl;
    }

    print_dict(antenna_dict);
}

bool is_pair_inbounds(const grid_t &g, const std::pair<int,int> &p){
    //assumes grid is square
    bool inbounds = true;
    if(p.first < 0 || p.first >= g.size() ||
            p.second < 0 || p.second >= g.size()){
        inbounds = false;
    }
    return inbounds;
}

void place_antinodes(grid_t &g, const dict_t &d){
    for (const auto& [key,v] : d){
        for(int i = 0; i < v.size(); ++i){
            for(int j = i+1; j < v.size(); ++j){
                std::pair<int,int> a(v[i]);
                std::pair<int,int> b(v[j]);
                int xdiff = b.first - a.first;
                int ydiff = b.second - a.second;
                std::pair<int,int> antinode0(a.first - xdiff, a.second - ydiff);
                std::pair<int,int> antinode1(b.first + xdiff, b.second + ydiff);

                if(is_pair_inbounds(g, antinode0)){
                    g[antinode0.first][antinode0.second].is_antinode = true;
                }
                if(is_pair_inbounds(g, antinode1)){
                    g[antinode1.first][antinode1.second].is_antinode = true;
                }
            }
        }
    }
}

int main(int argc, char *argv[]){
    std::cout << "concerning the antinodes of easter bunny chocolate antennae...\n";
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
            std::vector<Tile> newrow;
            for(int j = 0; j < line.size(); ++j){
                Tile newtile(line[j]);
                newrow.push_back(newtile);
            }
            grid.push_back(newrow);
            ++num_lines;
        }
        inputfile.close();

        print_grid(grid);
        std::cout << "-------\n";
        dict_t antenna_dict;
        build_antenna_dict(grid, antenna_dict);
        place_antinodes(grid, antenna_dict);
        int num_antinodes = count_and_print_antinodes(grid);
        std::cout << "num antinodes: " << num_antinodes << "\n";
    }

    std::cout << "complete\n";
    return 0;
}
