#include <iostream>
#include <string>
#include <vector>
// #include <algorithm>
#include <queue>

using namespace std;

struct Node
{
    int x;
    int y;
    friend ostream& operator<<(ostream& os, const Node& node);
};

struct NeighborNodes
{
    vector<Node> neighbor_nodes;

    vector<Node>::const_iterator begin()
    {
        if ( neighbor_nodes.size() > 0 ) return neighbor_nodes.begin();
        else return end();
    }
    vector<Node>::const_iterator end()
    {
        return neighbor_nodes.end();
    }
};

ostream& operator<<(ostream& os, const Node& node)
{
    os << "x: " << node.x << ", y: " << node.y;
    return os;
}

class Game
{
    int rows;
    int columns;
    int alarm_length;

    int player_x;
    int player_y;

    vector<vector<char>> maze;

    void init_parse(void);

    void parse(void);
    void parse_player_position(void);
    void parse_maze(void);

    vector<Node> bfs(void);
    NeighborNodes get_neighbor_nodes(Node node);

    void print_maze(void);
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
    cin >> rows >> columns >> alarm_length; cin.ignore();
}

void Game::run(void)
{
    while (1)
    {
        parse();
        print_maze();
        const vector<Node> path = bfs();
        break;
    }
}

void Game::parse(void)
{
    parse_player_position();
    parse_maze();
}

vector<Node> Game::bfs(void)
{
    const Node start_node = {
        .x = player_x,
        .y = player_y
    };

    const vector<Node> start_path = { start_node };

    queue<vector<Node>> paths;

    paths.push(start_path);

    while (!paths.empty())
    {
        const vector<Node> path = paths.front(); paths.pop();

        for (auto neighbor_node : get_neighbor_nodes(path.back()))
        {
            cerr << neighbor_node << endl;
            // paths.push(neighbor_path)
        }
    }
}

NeighborNodes Game::get_neighbor_nodes(Node node)
{
    NeighborNodes neighbor_nodes;

    vector<vector<int>> offsets {
        {  0, -1 },
        {  0,  1 },
        { -1,  0 },
        {  1,  0 }
    };

    for (const vector<int> offset : offsets)
    {
        neighbor_nodes.neighbor_nodes.push_back({
            .x = node.x + offset[0],
            .y = node.y + offset[1]
        });
    }

    return neighbor_nodes;
}

void Game::parse_player_position(void)
{
    cin >> player_y >> player_x; cin.ignore();
}

void Game::parse_maze(void)
{
    for (int i = 0; i < rows; i++) {
        string row;
        cin >> row; cin.ignore();
        maze.push_back(vector<char>(row.begin(), row.end()));
    }
}

void Game::print_maze(void)
{
    for (vector<char> row : maze)
    {
        for (char cell : row)
        {
            cerr << cell;
        }
        cerr << endl;
    }
}

int main()
{
    Game game = Game();

    game.run();
}
