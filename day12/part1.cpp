#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Tile{
    public:
        char tile;
        bool has_been_counted;
        int x;
        int y;

        Tile(){
            tile = '.';
            has_been_counted = false;
            x = -1;
            y = -1;
        }

        Tile(char newtile, int newx, int newy){
            tile = newtile;
            has_been_counted = false;
            x = newx;
            y = newy;
        }
};

using grid_t = std::vector<std::vector<Tile>>;
using region_t = std::vector<Tile>;
using regions_t = std::vector<region_t>;
//using dict_t = std::map<char, region_t>;

void print_grid(const grid_t &g){
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            std::cout << g[i][j].tile;
        }
        std::cout << std::endl;
    }
}

bool is_pair_inbounds(const grid_t &g, int i, int j){
    //assumes grid is square
    bool inbounds = true;
    if(i < 0 || i >= g.size() ||
            j < 0 || j >= g.size()){
        inbounds = false;
    }
    return inbounds;
}

void chase_region(grid_t &g, region_t &r, char target, int i, int j,int &p,int &a){
    //std::cout << "chasing "<<target<<" at "<<i<<","<<j<<"\n";
    if(!is_pair_inbounds(g,i,j)){
    
        ++p;
        return;
    }

    //match!
    if(g[i][j].tile == target){
        //add tile to region
        g[i][j].tile = '-';
        g[i][j].has_been_counted = true;
        r.push_back(g[i][j]);
        ++a;

        //check NSEW
        chase_region(g,r,target,i-1,j,p,a);
        chase_region(g,r,target,i+1,j,p,a);
        chase_region(g,r,target,i,j-1,p,a);
        chase_region(g,r,target,i,j+1,p,a);
    }
    else{
        if(g[i][j].tile != '-'){
            ++p;
        }
    }

    return;
}

void reset_grid(grid_t &g){
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            if(g[i][j].tile == '-'){
                g[i][j].tile = '@';
            }
        }
    }
}

int build_regions(grid_t &g, regions_t &rs){
    int running_total = 0;
    for(int i = 0; i < g.size(); ++i){
        for(int j = 0; j < g[i].size(); ++j){
            if(!g[i][j].has_been_counted){
                std::cout << "checking " << i<<","<<j<<"\n";
                region_t r;
                int perimeter = 0;
                int area = 0;
                chase_region(g,r,g[i][j].tile,i,j,perimeter,area);
                reset_grid(g);
                rs.push_back(r);
                std::cout << "perimeter:" << perimeter << "area:" << area << std::endl;
                running_total += perimeter * area;
            }
        }
    }
    return running_total;
}

int area(const region_t &r){
    return r.size();
}

int perimeter(region_t &r){
    //TODO
    return 0;
}

int score_regions(const grid_t &g, regions_t &rs){
    int running_total = 0;
    for(region_t r : rs){
        running_total += area(r) * perimeter(r);
    }
    return running_total;
}

int main(int argc, char *argv[]){
    std::cout << "concerning the gardens of the elves...\n";
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
                Tile newtile(line[j],num_lines,j);
                newrow.push_back(newtile);
            }
            grid.push_back(newrow);
            ++num_lines;
        }
        inputfile.close();

        print_grid(grid);
        std::cout << "-------\n";
        int grand_total = 0;
        regions_t regions;
        grand_total = build_regions(grid, regions);
        std::cout << "num regions: " << regions.size() << "\n";
        //int grand_total = score_regions(grid, regions);
        std::cout << "grand total: " << grand_total << "\n";
    }

    std::cout << "complete\n";
    return 0;
}
