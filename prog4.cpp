#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE

#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_SIZE = 50;
const int BLACK = 0;
const int DIM_BLUE = 1;
const int DIM_GREEN = 2;
const int DIM_CYAN = 3;
const int DIM_RED = 4;
const int DIM_MAGENTA = 5;
const int DIM_YELLOW = 6;
const int GREY = 7;
const int DIM_GREY = 8;
const int BLUE = 9;
const int GREEN = 10;
const int CYAN = 11;
const int RED = 12;
const int MAGENTA = 13;
const int YELLOW = 14;
const int WHITE = 15;

const int BACK = 0;
const int FORE = 1;

const char RANGE_ERR[] = "Out of Range Input";
const char TYPE_ERR[] = "File type not supported.";
const char BAR[] = "--------------------------";

void color_options();
int color_select();
void cout_color(int fColor, int bColor, const char text[]);
void cout_color(int fColor, int bColor, char letter);
void default1(char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50]);
void default2(char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50]);
void display(char mapname[], int mapdimensions[],
    int background[][50], int foreground[][50], char letter[][50],
    char filename[], char defaulttype[], int edit);
void edit_tiles(char mapname[], int mapdimensions[], int background[][50],
    int foreground[][50], char letter[][50], char filename[],
    char defaulttype[],
    int edit);
bool get_extension(char file_name[]);
void grow_city(int mapdimensions[], int background[][50], int foreground[][50],
    char letter[][50]);
void load_file(char mapname[], int mapdimensions[],
    int background[][50], int foreground[][50], char letter[][50],
    ifstream &fin, char complete_file[], char file_name[], int &loadcheck);
void main_menu(ifstream &fin, ofstream &fout, char mapname[],
    int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50],
    char filename[],
    char complete_file[], char defaulttype[]); 
void process_cammand_line(ifstream &fin, ofstream &fout, char mapname[],
    int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50],
    char filename1[],
    char filename2[], char complete_file[], int loadcheck, int arguments,
    char defaulttype[]);
void save_file(ofstream &fout, char savefilename[], int mapdimensions[],
    int background[][50], char mapname[], int foreground[][50],
    char letter[][50]);
int tile_stats(int color, int mapdimensions[], int background[][50]);
void edit_tiles(char mapname[], int mapdimensions[], int background[][50],
    int foreground[][50], char letter[][50], char filename[],
    char defaulttype[],
    int edit);
void grow_city(int mapdimensions[], int background[][50], int foreground[][50],
    char letter[][50]);

int main(int argc, char* argv[])
{
    ifstream fin; //file object to read data 
    ofstream fout; //file object to  write data
    //charecter array to store the mapname 
    char mapname[MAX_SIZE] = { 'N','o','n','e' }; 
    //stores the mapdimensions
    int mapdimensions[2] = { 2, 2 };
    //stores the foreground color codes
    int foreground[50][50] = { {0} };
    //stores the background color codes
    int background[50][50] = { {7,7},{7,7} };
    //stores the charecter to be printed on the map
    char letter[50][50] = { {'_', '_'}, {'_', '_'} };
    //stores the complete file name
    char complete_file[MAX_SIZE] = " ";
    //stores the file name
    char filename[100] = "     ";
    //used if there are no command line variables
    int ignoreload = 0;
    //used to store the type of the third argument
    char defaulttype[2] = { " " };
    //if there are more than 1 command line arguments
    if (argc > 1)
    {
        //if there are 4 command line arguments
        if (argc == 4)
        {
            //copies the 4th argument to defaulttype variable 
            strcpy(defaulttype, argv[3]);
        }
        //calls the process_cammand_line function
        process_cammand_line(fin, fout, mapname, mapdimensions,
            foreground, background, letter, argv[1], argv[2],
            complete_file, ignoreload, argc, defaulttype);
    }
    //calls the cout_color function to print the title
    cout_color(WHITE, BLACK, "***Land Area Sim***");
    cout << endl;
    //Calls the main_menu function
    main_menu(fin, fout, mapname, mapdimensions,
        foreground, background, letter, filename,
        complete_file, defaulttype);

    cout << "\nGoodbye..." << endl; //End message
    return 0; //Program executed successfully
}

void default1(char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50])
{
    int i = 0;
    int j = 0;
    for (i = 0; i < MAX_SIZE; i++)
    {
        mapname[i] = ' ';
    }
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            background[i][j] = 0;
            foreground[i][j] = 0;
            letter[i][j] = ' ';
        }
    }
    strcpy(mapname, "Default 1");
    mapdimensions[0] = 20;
    mapdimensions[1] = 20;

    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            if (i < 4)
            {
                background[i][j] = 1;
            }
            else
            {
                background[i][j] = 10;
            }
            foreground[i][j] = 0;
            letter[i][j] = ' ';
        }
    }
}

void default2(char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50])
{
    int i = 0; //Counter
    int j = 0; //counter
    //Resets the mapname
    for (i = 0; i < MAX_SIZE; i++)
    {
        mapname[i] = ' ';
    }
    //resets all the arrays
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            background[i][j] = 0;
            foreground[i][j] = 0;
            letter[i][j] = ' ';
        }
    }

    strcpy(mapname, "Default 2"); //saves the map name as Default 2
    mapdimensions[0] = 16; //sets the columns to 16
    mapdimensions[1] = 16; //sets the rows to 16
    //stores the new map
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            background[i][j] = j;
            foreground[i][j] = i;
            letter[i][j] = 'I';
        }
    }
}

void process_cammand_line(ifstream &fin, ofstream &fout, char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50], char filename1[],
    char filename2[], char complete_file[], int loadcheck,
    int arguments, char defaulttype[])
{
    //calls the load_file function
    load_file(mapname, mapdimensions, background, foreground, letter,
        fin, filename1, complete_file, loadcheck);
    //if the command line arguments are more than 2
    if (arguments > 2)
    {
        //calls the save file function
        save_file(fout, filename2, mapdimensions,
            background, mapname, foreground, letter);
    }
    //if the default type is d1
    if (strcmp(defaulttype, "d1") == 0)
    {
        //calls the default1 function
        default1(mapname, mapdimensions,
            foreground, background, letter);
        //calls the save file function
        save_file(fout, filename2, mapdimensions,
            background, mapname, foreground, letter);

    }
    //if the default type is d2
    else if (strcmp(defaulttype, "d2") == 0)
    {
        //calls the default2 function
        default2(mapname, mapdimensions,
            foreground, background, letter);
        //calls the save file function
        save_file(fout, filename2, mapdimensions,
            background, mapname, foreground, letter);
    }
}

void color_options()
{
    cout << endl;
    cout << "0 None (BLACK) | ";
    cout << "1 Ocean (D BLUE) | ";
    cout << "2 Forest (D GREEN) | ";
    cout << "3 Swamp (D CYAN)" << endl;
    cout << "4 Savana (D RED) | ";
    cout << "5 Marker (D MAGENTA) | ";
    cout << "6 Mountain (D YELLOW) | ";
    cout << "7 Road (GREY)" << endl;
    cout << "8 Rock (DARK GREY) | ";
    cout << "9 River (BLUE) | ";
    cout << "10 Plains (GREEN) | ";
    cout << "11 Marker (CYAN)" << endl;
    cout << "12 Lava (RED) | ";
    cout << "13 Marker (MAGENTA) | ";
    cout << "14 Sand (YELLOW) | ";
    cout << "15 Snow (WHITE)" << endl;
    cout << "-1 CANCEL" << endl;
    cout << BAR << endl;
}

int color_select()
{
    int color = -2;
    //while the color input is within the range
    while (color < -1 || color >15)
    {
        cin >> color; //input color
        //if the color input is out of range
        if (color < -1 || color >15)
        {
            cout << RANGE_ERR << endl; //error message
            cout << "Retry: ";
        }
    }
    return color;
}

void display(char mapname[], int mapdimensions[],
    int background[][50], int foreground[][50], char letter[][50],
    char filename[], char defaulttype[], int edit)
{
    int i = 0; //Counter
    int j = 0;//Counter
    size_t length = strlen(filename); //stores the length of the filename
    //stores the last character of the file 
    char extension = filename[length - 1]; 
    //output title
    cout << "-----" << mapname << "-----" << endl;
    //if the map width is greater than 9
    if (mapdimensions[0] > 9)
    {
        cout << "  ";
        //output first line of the header
            //for the entire width, 
        for (i = 0; i < mapdimensions[0]; i++)
        {
            //if the current position is under 0, output ' '
            if (i <= 10)
            {
                cout << " ";
            }
            //otherwise output position / 10 with cout
            else
            {
                cout << i / 10;
            }
        }
        cout << endl;
    }
    cout << "  ";
    //output the second line of the header
        //for the entire width, output position %10 with cout
    for (i = 0; i < mapdimensions[0]; i++)
    {
        cout << i % 10;
    }
    cout << endl;
    //for each tile, use cout_color() to output its character and given background and foreground
    for (i = 0; i < mapdimensions[1]; i++)
    {
        //at the beginning of each row, output the row number with width 2
        if (i <= 9)
        {
            cout << " ";
        }
        else
        {
            cout << i / 10;
        }
        cout << i % 10;
        for (j = 0; j < mapdimensions[0]; j++)
        {
            char text = letter[i][j]; //used to input text
            //if the character is a _
            if (text == '_')
            {
                text = ' ';
            }
            //Prints the color to the screen
            cout_color(foreground[i][j], background[i][j], text);
        }
        cout << endl;
    }
}

void load_file(char mapname[], int mapdimensions[],
    int background[][50], int foreground[][50], char letter[][50],
    ifstream &fin, char file_name[], char complete_file[], int &loadcheck)
{
    char extension = ' '; //stores the last charecter of the file name
    char temp_name[50] = { "" }; //stores the file name temporarily
    char tempfilename[MAX_SIZE] = " "; //stores the file name temporarily
    int temp_dimensions[2] = { 0 }; //stores the map dimensions temporarily
    int i = 0; //Counter
    int j = 0; //Counter
    int flag = 0; //flag
    size_t length = 0; //length of the file name
    //if the extension is sim1 or sim2
    if (get_extension(file_name))
    {

        strcpy(tempfilename, file_name); //copies file_name temporarily
        //copies the temporary file back the original
        strcpy(file_name, tempfilename); 
        fin.open(file_name); //Opens the file
        //If the file doesn't open
        if (!fin)
        {
            cout << file_name << " could not be loaded." << endl;
            flag = 1; 
            fin.close(); //closes the file
            fin.clear(); //resets the file object
            
        }
        //if the file opens sucessfully
        if (flag == 0)
        {
            length = strlen(file_name); //stores the length of the file name
             //stores the last character of the file name 
            extension = file_name[length - 1];
            //copies the temporary name to the original name
            strcpy(temp_name, mapname); 
            //copies the dimensions temporarily
            for (i = 0; i < 2; i++)
            {
                temp_dimensions[i] = mapdimensions[i];
            }
            fin.getline(mapname, MAX_SIZE); //reads the mapname
            fin >> mapdimensions[0]; //reads the column
            fin >> mapdimensions[1]; //reads the row
            //if the dimensions are within the bounds
            if (mapdimensions[0] < 2 || mapdimensions[0] > 50
                || mapdimensions[1] < 2 || mapdimensions[1] > 50)
            {
                cout << RANGE_ERR << endl; //error message
                cout << "Size must be between 2 and 50" << endl;
                //stores back the dimensions
                for (i = 0; i < 2; i++)
                {
                    mapdimensions[i] = temp_dimensions[i];
                }
            }
            else
            {
                //stores the data to the arrays 
                for (i = 0; i < mapdimensions[1]; i++)
                {
                    for (j = 0; j < mapdimensions[0]; j++)
                    {
                        fin >> background[i][j];
                        if (extension == '2')
                        {
                            fin >> foreground[i][j];
                            fin >> letter[i][j];
                            //if the charecter is _
                            if (letter[i][j] == '_')
                            {
                                letter[i][j] = ' ';
                            }

                        }
                        else
                        {
                            letter[i][j] = '_';
                        }

                    }
                }
                loadcheck = 1; //Loaded sucessfully
            }
        }
        fin.close(); //closes the file
    }
    else
    {
        cout << TYPE_ERR << endl; //error message
    }
}

void edit_tiles(char mapname[], int mapdimensions[], int background[][50],
    int foreground[][50], char letter[][50], char filename[], char defaulttype[],
    int edit)
{
    int choice = -1; //stores the user response
    int row = 0; //stores the user input for row
    int col = 0; //stores the user input for column
    int back = 0; //stores the user response for the background color
    int fore = 0; //stores the user response for the foreground color
    char charecter = ' '; //stores the user response for the charecter
    //while the user chooses not to exit
    while (choice != 0)
    {
        cout << endl;
        cout << "1) Print Current Image" << endl;
        cout << "2) Change tile" << endl;
        cout << "0) Exit menu" << endl;
        cout << BAR << endl;
        cout << "Selection: ";
        cin >> choice; //input response
        //If the input is invalid
        if (choice > 2 || choice < 0)
        {
            cout << RANGE_ERR << endl; //Error message
        }
        //If the user chooses to display the map
        else if (choice == 1)
        {
            //Calls the display function
            display(mapname, mapdimensions, background, foreground, letter,
                filename, defaulttype, edit);
            edit = 0; //resets edit variable
            
        }
        //if the user chooses to edit a tile
        else if (choice == 2)
        {
            color_options(); //Calls the color_options function
            cout << "Enter the row and column: ";
            cin >> row >> col; //inputs row and column
            cout << "_ will be a space, and X will be a city." << endl;
            cout << "Enter the background color, foreground color, and a character: ";
            back = color_select(); //takes in a input for background color
            fore = color_select(); //takes in a input for foreground color
            cin >> charecter; //takes in user input for a character
            //If the color input is wrong
            if (fore != -1 && back != -1)
            {
                //if the row and column is within the bounds of the map
                if (row >= 0 && row < mapdimensions[0] && col >= 0 && col < mapdimensions[1])
                {
                    background[row][col] = back;
                    foreground[row][col] = fore;
                    //If the charecter is a _, it saves it as a space
                    if (charecter == '_')
                    {
                        charecter = ' ';
                    }

                    letter[row][col] = charecter;
                }
                else
                {
                    cout << RANGE_ERR << endl; //error message
                }
            }

        }
    }

}

bool get_extension(char file_name[])
{
    int i = 0; //Counter
    char sim1[5] = { 's', 'i', 'm', '1' }; //Stores sim1
    char sim2[5] = { 's', 'i', 'm', '2' }; //stores sim2
    char filetype[5] = " "; //Stores the file type
    size_t length; //Stores the length

    length = strlen(file_name); //Stores the length of the file name
    //Extracts the last 4 charecters of the file name
    for (i = 0; i < 4; i++)
    {
        filetype[i] = file_name[length - (4 - i)];
    }
    //If the extension is '.sim1' or '.sim2'
    if (strcmp(filetype, sim1) == 0 || strcmp(filetype, sim2) == 0)
    {
        return true; 
    }
    else
    {
        return false;
    }
}

void save_file(ofstream &fout, char savefilename[], int mapdimensions[],
    int background[][50], char mapname[], int foreground[][50],
    char letter[][50])
{
    int i = 0; //Counter
    int j = 0; //Counter
    size_t length; //Stores the length of an array
    char filetype[5] = ""; //Stores the type of the file 
    char extension = ' '; //Stores the last charecter of the file name
    size_t maplength = strlen(mapname); //stores the length of the map name
    length = strlen(savefilename); //stors the length of file name to be saved
    extension = savefilename[length - 1]; //Stores the last charecter

    //Stores the last 4 charecters of the file name
    for (i = 0; i < 4; i++)
    {
        filetype[i] = savefilename[length - (4 - i)];
    }
    //If the file is not a .sim1 or .sim2
    if (strcmp(filetype, "sim1") != 0 && strcmp(filetype, "sim2") != 0)
    {
        cout << TYPE_ERR << endl; //Error message
    }
    else
    {
        //Opens file to write
        fout.open(savefilename);
        //If the file is not opened
        if (!fout)
        {
            cout << savefilename << " could not be opened." << endl;
        }
        else
        {
            //Writes the mapname to the file
            for (i = 0; i < maplength; i++)
            {
                fout << mapname[i];
            }
            fout << endl;
            //Writes the mapdimensions to the file
            fout << mapdimensions[0] << " " << mapdimensions[1];
            fout << endl;
            //Writes the map contents to the file
            for (i = 0; i < mapdimensions[1]; i++)
            {
                for (j = 0; j < mapdimensions[0]; j++)
                {
                    fout << background[i][j] << " ";
                    //If the file is of type .sim2
                    if (extension == '2')
                    {
                        fout << foreground[i][j] << " ";
                        //If the input is a _
                        if (isspace(letter[i][j]))
                        {
                            fout << "_" << " ";
                        }
                        else
                        {
                            fout << letter[i][j] << " ";
                        }
                    }
                }
                fout << endl;
            }
            fout.close(); //Closes the file
        }
    }
}

int tile_stats(int color, int mapdimensions[], int background[][50])
{
    int i = 0; //Count i
    int j = 0; //Count j
    int counter = 0; //Counter
    //Counts the number of tiles of a specific  color
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            if (background[i][j] == color)
            {
                counter++;
            }
        }
    }
    return counter;  //returns the count
}

void grow_city(int mapdimensions[], int background[][50], int foreground[][50], char letter[][50])
{
    int i = 0;
    int j = 0;
    int m = 0;
    int n = 0;
    int newcityback[50][50] = { };
    int newcityfore[50][50] = { };
    char newcityletter[50][50] = {  };

    //TODO copy map so we don't use a new city tile
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            newcityback[i][j] = background[i][j];
            newcityfore[i][j] = foreground[i][j];
            newcityletter[i][j] = letter[i][j];
        }
    }

    //for each tile
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            //if it is a plain or road
            if (letter[i][j] == 'X' && (background[i][j] == 7 || background[i][j] == 10))
            {
                //check all neighboring tiles (-1 to +1 along row and column)
                for (m = i - 1; m < i + 2; m++)
                {
                    for (n = j - 1; n < j + 2; n++)
                    {
                        //if this neighbor is within bounds
                        if ((m >= 0 && m < mapdimensions[1]) && (n >= 0 && n < mapdimensions[0]))
                        {
                            //If the text marks the neighbor as a city
                            if (background[m][n] == 7 || background[m][n] == 10)
                            {
                                //mark the current tile in the map copy (not the neighbor) as a city
                                newcityletter[m][n] = 'X';
                                //and copy the foreground over
                                newcityfore[m][n] = foreground[i][j];
                            }
                            //newcityletter[m][n] = 'X';
                            // newcityfore[m][n] = foreground[i][j];
                        }
                    }

                }
            }
        }
    }
    //copy new city location and foreground colors to the original
    for (i = 0; i < mapdimensions[1]; i++)
    {
        for (j = 0; j < mapdimensions[0]; j++)
        {
            foreground[i][j] = newcityfore[i][j];
            letter[i][j] = newcityletter[i][j];
        }
    }
}

void main_menu(ifstream &fin, ofstream &fout, char mapname[], int mapdimensions[],
    int foreground[][50], int background[][50], char letter[][50],
    char filename[], char complete_file[], char defaulttype[])
{

    int mainresponse = -1; // stores the response for the main menu
    char savefilename[100] = ""; //Saves the file name to save
    int flag = 0; //  flag indicator
    int loadcheck = 0; //Checks if the file is loaded
    int colorcheck = 0; //Makes sure valid response is inputted
    int colorcount = 0; //Counts the number of tiles of a certain color
    int edit = 0; //Makes sure the file is edited

    //While the user chooses to exit
    while (mainresponse != 0)
    {
        cout << endl;
        //Calls the display function
        display(mapname, mapdimensions, background, foreground, letter,
            filename, defaulttype, edit);
        cout << "1) Load image \n";
        cout << "2) Change Title \n";
        cout << "3) Save image \n";
        cout << "4) Count tiles of type\n";
        cout << "5) Edit tiles\n";
        cout << "6) Grow Cities\n";
        cout << "0) Exit" << endl;
        cout << BAR << endl;
        cout << "Selection: ";
        cin >> mainresponse; //inputs the mainresponse
         //If the input is not a valid choice
        if (mainresponse > 6 || mainresponse < 1 && mainresponse != 0)
        {
            cout << RANGE_ERR << endl;
        }
        //If the user chooses to load a file
        else if (mainresponse == 1)
        {
            cout << "Please enter a file name: ";
            cin >> filename; //Iinputs file name
            //Calls the load_file function
            load_file(mapname, mapdimensions, background, foreground, letter,
                fin, filename, complete_file, loadcheck);
            //if the file is loaded 
            if (loadcheck == 1)
            {
                cout << "Loaded successfully." << endl;
            }
        }
        //If the user chooses to change the title of the map
        else if (mainresponse == 2)
        {
            cout << "New title: ";
            cin.ignore(); //ignores the last input
            cin.getline(mapname, 50); //inputs the new name for the map
        }
        //If the user chooses to save the current file
        else if (mainresponse == 3)
        {
            cout << "Enter a name for the file: ";
            cin >> savefilename; //inputs the new file name to save
            //Calls the save file function
            save_file(fout, savefilename, mapdimensions, background,
                mapname, foreground, letter);
        }
        //If the user chooses to count the number of tiles of a specific color
        else if (mainresponse == 4)
        {
            //While the user chooses not to exit the menu
            while (colorcheck != -1)
            {
                color_options(); // Calls the color_options function
                cout << "Choose the color to count (-1 to end): ";
                colorcheck = color_select(); //Gets a color input
                //While the user chooses not to exit the color count menu
                if (colorcheck != -1)
                {
                    //Counts the number of tiles of a specific color
                    colorcount = tile_stats(colorcheck, mapdimensions,
                        background);
                    cout << "The number of tiles of that type are "
                        << colorcount;
                    cout << endl;
                }
            }
        }
        //If the user chooses to edit tiles on the map
        else if (mainresponse == 5)
        {
            //Calls the edit_tiles function
            edit_tiles(mapname, mapdimensions, background,
                foreground, letter, filename, defaulttype, edit);
        }
        //If the user chooses to grow city
        else if (mainresponse == 6)
        {
            //Calls the grow_city function
            grow_city(mapdimensions, background, foreground, letter);
        }
    }
}

void cout_color(int fColor, int bColor, char letter)
{
    char text[2] = "";
    text[0] = letter;
    cout_color(fColor, bColor, text);
}

void cout_color(int fColor, int bColor, const char text[])
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (fColor + (bColor * 16)));
    cout << text;

    //reset color
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (WHITE + (BLACK * 16)));
}
