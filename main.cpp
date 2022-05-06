#include <iostream>
#include <string>
#include <vector>
// #include <algorithm>
#include <queue>

#include <cmath> // pow()


struct Node
{
    int x;
    int y;
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};


std::ostream& operator<<(std::ostream& os, const Node& node)
{
    os << "x: " << node.x << ", y: " << node.y;
    return os;
}


struct NeighborNodes
{
    std::vector<Node> neighbor_nodes;

    std::vector<Node>::const_iterator begin()
    {
        if ( neighbor_nodes.size() > 0 ) return neighbor_nodes.begin();
        else return end();
    }
    std::vector<Node>::const_iterator end()
    {
        return neighbor_nodes.end();
    }
};


class Grid
{
    void print_column_indices(std::string::size_type max_row_index_length);
    void print_row_indices(std::string::size_type max_row_index_length);
public:
    // Grid(void);
    // Grid(char empty_char) : empty_character(empty_char) {}

    void print(void);

    int width;
    int height;

    char empty_character = ' ';

    std::vector<std::vector<char>> grid;
};


void Grid::print(void)
{
    std::string::size_type max_row_index_length = std::to_string(grid.size()).length();

    print_column_indices(max_row_index_length);
    print_row_indices(max_row_index_length);
}


void Grid::print_column_indices(std::string::size_type max_row_index_length)
{
    std::vector<char>::size_type column_count = grid[0].size();

    std::string::size_type max_column_index_length = std::to_string(column_count).length();

    for (ssize_t digit_index = max_column_index_length - 1; digit_index >= 0; digit_index--)
    {
        std::cerr << std::string(max_row_index_length, empty_character);

        for (std::vector<char>::size_type column_index = 0; column_index < column_count; column_index++)
        {
            int div = static_cast<int>(std::pow(10.0, digit_index));
            int digit = column_index / div % 10;

            if (div <= column_index || (column_index == 0 && digit_index == 0))
            {
                std::cerr << digit;
            }
            else
            {
                std::cerr << empty_character;
            }
        }

        std::cerr << std::endl;
    }
}


void Grid::print_row_indices(std::string::size_type max_row_index_length)
{
    for (int row_index = 0; row_index < grid.size(); row_index++)
    {
        std::vector<char> row = grid[row_index];

        std::string::size_type row_index_length = std::to_string(row_index).length();

        std::cerr << std::string(max_row_index_length - row_index_length, empty_character);

        std::cerr << row_index;

        for (char cell : row)
        {
            std::cerr << cell;
        }
        std::cerr << std::endl;
    }
}


class Game
{
    int alarm_length;

    int player_x;
    int player_y;

    Grid grid;

    void init_parse(void);

    void parse(void);
    void parse_player_position(void);
    void parse_grid(void);

    std::vector<Node> bfs(void);
    NeighborNodes get_neighbor_nodes(Node node);

    bool node_is_out_of_bounds(Node node);
    bool node_is_wall(Node node);
public:
    Game(void);
    void run(void);
};


Game::Game(void)
{
    init_parse();
}


void Game::init_parse(void)
{
    std::cin >> grid.height >> grid.width >> alarm_length; std::cin.ignore();
}


void Game::run(void)
{
    while (1)
    {
        parse();
        grid.print();
        const std::vector<Node> path = bfs();
        break;
    }
}


void Game::parse(void)
{
    parse_player_position();
    parse_grid();
}


std::vector<Node> Game::bfs(void)
{
    const Node start_node = {
        .x = player_x,
        .y = player_y
    };

    const std::vector<Node> start_path = { start_node };

    std::queue<std::vector<Node>> paths;

    paths.push(start_path);

    while (!paths.empty())
    {
        const std::vector<Node> path = paths.front(); paths.pop();

        for (const Node &neighbor_node : get_neighbor_nodes(path.back()))
        {
            std::cerr << neighbor_node << std::endl;

            if (node_is_out_of_bounds(neighbor_node) || node_is_wall(neighbor_node))
            {
                continue;
            }

            std::vector<Node> neighbor_path(path);

            neighbor_path.push_back(neighbor_node);

            paths.push(neighbor_path);
        }
    }
}


NeighborNodes Game::get_neighbor_nodes(Node node)
{
    NeighborNodes neighbor_nodes;

    std::vector<std::vector<int>> offsets {
        {  0, -1 },
        {  0,  1 },
        { -1,  0 },
        {  1,  0 }
    };

    for (const std::vector<int> offset : offsets)
    {
        neighbor_nodes.neighbor_nodes.push_back({
            .x = node.x + offset[0],
            .y = node.y + offset[1]
        });
    }

    return neighbor_nodes;
}


bool Game::node_is_out_of_bounds(Node node)
{
    return (
        node.x <= -1 || node.x >= grid.width ||
        node.y <= -1 || node.y >= grid.height
    );
}


bool Game::node_is_wall(Node node)
{
    return grid.grid[node.y][node.x] == '#';
}


void Game::parse_player_position(void)
{
    std::cin >> player_y >> player_x; std::cin.ignore();
}


void Game::parse_grid(void)
{
    for (int i = 0; i < grid.height; i++) {
        std::string row;
        std::cin >> row; std::cin.ignore();
        grid.grid.push_back(std::vector<char>(row.begin(), row.end()));
    }
}


int main()
{
    Game game = Game();

    game.run();
}
