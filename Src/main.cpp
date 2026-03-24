//
// Brian Mack, Juan Ipina, Blake Jackson, James Su
// Project #3 Word Search
// Main file for Project 3 (runs search flow and word match scanning)
//
#include "dictionary.hpp"
#include "grid.hpp"

void findMatches(
    const dictionary& dict, const grid& g, const std::string& output_file)
{
    /* Scans the grid from every start cell and direction, and writes matches
     * parameters - dict: sorted dictionary, g: letter grid,
     *              output_file: path to the output file
     * assumptions - dict is sorted before this function is called
     */
    std::ofstream out(output_file.c_str());

    /* Make sure the output file was opened successfully. */
    if (!out)
    {
        throw fileOpenError(output_file);
    }

    /* Arrays for the row increases/decreases. */
    const int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
    const int dc[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    /* Array for the direction names. */
    const std::string dirNames[8] = {
        "north", "south", "east", 
        "west", "northeast", "northwest", 
        "southeast", "southwest"
    };

    /*
        For every cell (i,j)
            For every direction d
                Walk forward in that direction d
                    Build words incrementally
                    Check dictionary when the word's length is larger than 5
    
    */
    for (int i = 0; i < g.num_rows(); i++)
    {
        for (int j = 0; j < g.num_cols(); j++)
        {
            for (int d = 0; d < 8; d++)
            {
                std::string current_word = "";
                int r = i;
                int c = j;

                bool first_step = true;
                while (first_step || r != i || c != j)
                {
                    // Handle at least one cell and loop until it reaches
                    // the starting cells
                    first_step = false;
                    current_word += g.get(r, c);

                    if (current_word.length() >= 5)
                    {
                        int found_index = dict.find(current_word);
                        if (found_index != -1)
                        {
                            out << current_word << " (" << i << "," << j
                                << ") " << found_index << '\n';
                        }
                    }

                    r += dr[d];
                    c += dc[d];

                    // Handle wraparounds
                    if (r < 0)
                    {
                        r = g.num_rows() - 1;
                    }
                    else if (r >= g.num_rows())
                    {
                        r = 0;
                    }

                    if (c < 0)
                    {
                        c = g.num_cols() - 1;
                    }
                    else if (c >= g.num_cols())
                    {
                        c = 0;
                    }
                }
            }
        }
    }
}

void search(void)
{
    /* Runs the full Word Search flow
     * reads grid file name, loads dictionary/grid, sorts dictionary,
     * and writes all found matches
     */
    std::string grid_file;
    std::string dictionary_file = "Dictionary.txt";
    std::string output_file = "matches.txt";
    std::cout << "Enter grid file name: ";
    std::cin >> grid_file;
    dictionary dict;
    grid g;
    dict.store(dictionary_file);
    g.read_grid(grid_file);
    dict.sort();
    findMatches(dict, g, output_file);
    std::cout << "Search complete. Results written to " << output_file << '\n';
}

int main()
{
    /* Runs search() */
    try
    {
        search();
    }
    catch (const baseException& e)
    {
        std::cout << "Error: " << e.what() << '\n';
    }

    return 0;
}