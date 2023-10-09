#include<iostream>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<unordered_map>

#define cls system("cls")

using namespace std;

void menu_display()
{
	cout << "\n\n*********************************************************************************************************************************************************";
	cout << "\n\t\t\t\t\t\t\t\t CLASSIC CONSOLE GAMES ";
	cout << "\n*********************************************************************************************************************************************************";
	
	cout << "\n\nClassic Game Console is a nostalgic console app that brings three iconic games together in one place. Enjoy the timeless classics of Tic Tac Toe, Pong, and Snake, all in a single, convenient package. Whether you're in the mood for strategic battles, fast-paced sports action, or nostalgic arcade fun, this console app has something to offer for gamers of all ages. Dive into the world of retro gaming and relive the excitement of these beloved classics with Classic Game Console.";

	char b = '\xDB';

	cout << "\n\n"<<"\t\t" << b << b << b << b << b << " GAMES MENU " << b << b << b << b << b << b << b << b << b << b << b << b << b << b << "\n";
	cout << "\t\t" << b << "                             " << b;
	cout << "\n" << "\t\t" << b << " Type 1 for Tic - tac - toe  "<<b;
	cout << "\n" << "\t\t" <<b << "                             " << b;
	cout << "\n" << "\t\t" << b << " Type 2 for Snake Game       "<<b;
	cout << "\n" << "\t\t" <<b << "                             " << b;
	cout << "\n" << "\t\t" << b << " Type 3 for Pong game        "<<b;
	cout << "\n" << "\t\t" << b << "                             " << b;
    cout << "\n" << "\t\t" << b << " Type 4 to EXIT              " << b;
    cout << "\n" << "\t\t" << b << "                             " << b;
	cout << "\n" << "\t\t" << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b << b;

	cout << "\n\n\n" << "\t\t" << "Enter which game you want to Play (1/2/3/4) : ";
}


// SNAKE GAME START 

    bool gameover;
    const int width = 20, height = 20;
    int x, y, fruit_x, fruit_y, score;
    int tailx[200], taily[200];
    int ntail;
    char headchar = '<';
    
    enum direction
    {
        stop = 0, _left, _right, _up, _down
    };
    direction dir;

    void title_display()
    {
        cout << "\n\n************************************************************************************************************************************************";
        cout << "\n\t\t\t\t\t\t\t\t RETRO SNAKE GAME ";
        cout << "\n************************************************************************************************************************************************";

        cout << "\n\nRetro Snake Game Console takes you on a trip down memory lane with the classic Snake game. Navigate a pixelated snake through a grid, gobbling\nup food to grow longer while avoiding collisions with the walls and your own tail. This console-based game offers a simple yet addictive\ngameplay experience, challenging your reflexes and strategic thinking.";
        cout << "\n\n CONTROLS: 'W'(UP), 'A'(LEFT), 'S'(DOWN), 'D'(RIGHT)";
        cout << "\n" << " Press 'X' mid game to stop the game";

    }

    void thanks_message()
    {
        cout << "\n\n========================================================================================================================================================";
        cout << "\n\t\t\t\t\t\t\t         THANK YOU FOR PLAYING";
        cout << "\n=========================================================================================================================================================";
    }

    void loading_bar()
    {
        // to use the extended ASCII table of CP437 Character encoding
        SetConsoleCP(437);
        SetConsoleOutputCP(437);

        char ch1 = 177, ch2 = 219;              // characters used to make loading bar

        cout << "\n\n\n\t\t\t\t\t\t\t            LOADING..... \n";
        cout << "\n\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the base bar in one go
        {
            cout << ch1;
        }
        cout << "\r";                         // takes the cursor to the starting of previous line 
        cout << "\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the loading bar with 75ms time gap between each character
        {
            cout << ch2;
            Sleep(75);
        }
    }

    void setup()
    {
        gameover = false;
        dir = stop;
        x = width / 2, y = height / 2;
        fruit_x = rand() % width;
        fruit_y = rand() % height;
        score = 0;
        ntail = 0;
    }

    void draw()
    {
        system("cls");
        cout << "+";
        for (int i = 1; i < width - 1; i++)
        {
            cout << "-";
        }
        cout << "+";
        cout << endl;

        for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                if (j == 0 || j == width - 1)
                {
                    cout << "|";
                }

                else if (i == y && j == x)
                {
                    cout << headchar;
                }

                else if (i == fruit_y && j == fruit_x)
                {
                    cout << "F";
                }

                else
                {
                    bool print = false;
                    for (int k = 0; k < ntail; k++)
                    {
                        if (tailx[k] == j && taily[k] == i)
                        {
                            cout << "o";
                            print = true;
                        }
                    }
                    if (!print)
                    {
                        cout << " ";
                    }
                }
            }
            cout << endl;
        }

        cout << "+";
        for (int i = 1; i < width - 1; i++)
        {
            cout << "-";
        }
        cout << "+";
        cout << endl;
        cout << "Score = " << score << endl;
    }

    void input()
    {
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'a':
                dir = _left;
                break;
            case 'd':
                dir = _right;
                break;
            case 's':
                dir = _down;
                break;
            case 'w':
                dir = _up;
                break;
            case 'x':
                gameover = true;
                break;
            }
        }
    }

    void logic()
    {
        int prevx = tailx[0];
        int prevy = taily[0];
        int prev2x, prev2y;
        tailx[0] = x;
        taily[0] = y;


        for (int i = 1; i < ntail; i++)
        {
            prev2x = tailx[i];
            prev2y = taily[i];

            tailx[i] = prevx;
            taily[i] = prevy;

            prevx = prev2x, prevy = prev2y;
        }
        switch (dir)
        {
        case _left:
            x--;
            headchar = '<';
            break;
        case _right:
            x++;
            headchar = '>';
            break;
        case _up:
            y--;
            headchar = '^';
            break;
        case _down:
            headchar = 'v';
            y++;
            break;
        default:
            break;
        }

        if (x >= width)
        {
            x = 0;
        }
        else if (x < 0)
        {
            x = width - 1;
        }
        if (y >= height)
        {
            y = 0;
        }
        else if (y < 0)
        {
            y = height - 1;
        }

        for (int i = 0; i < ntail; i++)
        {
            if (tailx[i] == x && taily[i] == y)
            {
                gameover = true;
            }
        }

        if (x == fruit_x && y == fruit_y)
        {
            score += 10;
            fruit_x = rand() % width;
            fruit_y = rand() % height;
            ntail++;
        }
    }

// SNAKE GAME END

// PONG GAME START

    void title_display1()
    {
        cout << "\n\n************************************************************************************************************************************************";
        cout << "\n\t\t\t\t\t\t\t\t RETRO PONG GAME ";
        cout << "\n************************************************************************************************************************************************";

        cout << "\n\nRetro Pong is a classic and minimalist game that brings the retro Pong experience to your console. Enjoy fast-paced paddle action with a friend\nor challenge yourself to a single-player match. Simple controls and addictive gameplay make it a quick and fun gaming choice.";
        cout << "\n\n" << " Player 1 controls: 'W' to move up and 'S' to move down";
        cout << "\n" << " Player 2 controls: 'I' to move up and 'K' to move down";
        cout << "\n" << " Press 'Q' mid game to stop the game";


    }

    void thanks_message1()
    {
        cout << "\n\n=========================================================================================================================================================";
        cout << "\n\t\t\t\t\t\t\t         THANK YOU FOR PLAYING";
        cout << "\n=========================================================================================================================================================";
    }

    void loading_bar1()
    {
        // to use the extended ASCII table of CP437 Character encoding
        SetConsoleCP(437);
        SetConsoleOutputCP(437);

        char ch1 = 177, ch2 = 219;              // characters used to make loading bar

        cout << "\n\n\n\t\t\t\t\t\t\t            LOADING..... \n";
        cout << "\n\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the base bar in one go
        {
            cout << ch1;
        }
        cout << "\r";                         // takes the cursor to the starting of previous line 
        cout << "\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the loading bar with 75ms time gap between each character
        {
            cout << ch2;
            Sleep(75);
        }
    }

    enum direction1
    {
        stop1 = 0, _left1 = 1, upleft1 = 2, downleft1 = 3, _right1 = 4, upright1 = 5, downright1 = 6
    };

    class cball
    {
    public:
        
        int x, y;
        int orignal_x, orignal_y;
        direction1 dir;

        cball(int posx, int posy)
        {
            orignal_x = posx;
            orignal_y = posy;
            x = posx, y = posy;
            dir = stop1;
        }

        void reset()
        {
            x = orignal_x, y = orignal_y;
            dir = stop1;
        }

        void change_dir(direction1 d)
        {
            dir = d;
        }

        void random_dir()
        {
            dir = (direction1)((rand() % 6) + 1);
        }

        void move()
        {
            switch (dir)
            {
            case stop1:
                break;
            case _left1:
                x--;
                break;
            case downleft1:
                x--, y++;
                break;
            case upleft1:
                x--, y--;
                break;
            case _right1:
                x++;
                break;
            case upright1:
                x++, y--;
                break;
            case downright1:
                x++, y++;
                break;
            default:
                break;
            }
        }

        inline int getx()
        {
            return x;
        }

        inline int gety()
        {
            return y;
        }

        inline direction1 getdir()
        {
            return dir;
        }

        friend ostream& operator<<(ostream& o, cball c)
        {
            o << "Ball [" << c.x << " , " << c.y << "][" << c.dir << "]";
            return o;
        }
    };

    class cpaddle
    {
    public:
        int x, y;
        int orignal_x, orignal_y;
        cpaddle()
        {
            x = y = 0;

        }
        cpaddle(int posx, int posy) :cpaddle()
        {
            orignal_x = posx, orignal_y = posy;
            x = posx, y = posy;

        }

        inline void reset()
        {
            x = orignal_x, y = orignal_y;
        }

        inline int getx()
        {
            return x;
        }

        inline int gety()
        {
            return y;
        }

        inline void moveup()
        {
            y--;
        }

        inline void movedown()
        {
            y++;
        }

        friend ostream& operator<<(ostream& o, cpaddle c)
        {
            o << "Paddle [" << c.x << " , " << c.y << "]";
            return o;
        }

    };

    class game_manager
    {
    public:
        int width, height;
        int score1, score2;

        char up1, down1, up2, down2;
        bool quit;

        cball* ball;
        cpaddle* player1, * player2;

        game_manager(int w, int h)
        {
            srand(time(NULL));
            quit = false;
            up1 = 'w';
            up2 = 'i';
            down1 = 's';
            down2 = 'k';
            score1 = 0, score2 = 0;
            width = w, height = h;

            ball = new cball(w / 2, h / 2);
            player1 = new cpaddle(1, h / 2 - 3);
            player2 = new cpaddle(w - 2, h / 2 - 3);
        }

        ~game_manager()
        {
            delete ball, player1, player2;
        }

        void scoreup(cpaddle* player)
        {
            if (player == player1)
            {
                score1++;
            }
            else if (player == player2)
            {
                score2++;
            }

            ball->reset();
            player1->reset();
            player2->reset();
        }

        void draw1()
        {
            system("cls");
            for (int i = 0; i < width + 2; i++)
            {
                cout << "\xDB";
            }
            cout << endl;

            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width + 2; j++)
                {
                    int ballx = ball->getx();
                    int bally = ball->gety();
                    int player1x = player1->getx();
                    int player1y = player1->gety();
                    int player2x = player2->getx();
                    int player2y = player2->gety();

                    if (j == 0 || j == width)
                    {
                        cout << "\xDB";
                    }

                    if (ballx == j && bally == i)
                    {
                        cout << "O"; // ball
                    }
                    else if (player1x == j && player1y == i)
                    {
                        cout << "\xBB"; // player 1
                    }
                    else if (player2x == j && player2y == i)
                    {
                        cout << "\xC9"; // player 2
                    }

                    else if (player1x == j && player1y + 1 == i)
                    {
                        cout << "\xBA";
                    }
                    else if (player1x == j && player1y + 2 == i)
                    {
                        cout << "\xBA";
                    }
                    else if (player1x == j && player1y + 3 == i)
                    {
                        cout << "\xBC";
                    }

                    else if (player2x == j && player2y + 1 == i)
                    {
                        cout << "\xBA";
                    }
                    else if (player2x == j && player2y + 2 == i)
                    {
                        cout << "\xBA";
                    }
                    else if (player2x == j && player2y + 3 == i)
                    {
                        cout << "\xC8";
                    }

                    else
                    {
                        cout << " ";
                    }

                }
                cout << endl;
            }

            for (int i = 0; i < width + 2; i++)
            {
                cout << "\xDB";
            }
            cout << endl;

            cout << "\n Score 1: " << score1 << endl << " Score 2: " << score2 << endl;
        }

        void input1()
        {
            ball->move();

            int ballx = ball->getx();
            int bally = ball->gety();
            int player1x = player1->getx();
            int player1y = player1->gety();
            int player2x = player2->getx();
            int player2y = player2->gety();

            if (_kbhit())
            {
                char curr = _getch();
                if (curr == up1)
                {
                    if (player1y > 0)
                    {
                        player1->moveup();
                    }
                }
                if (curr == up2)
                {
                    if (player2y > 0)
                    {
                        player2->moveup();
                    }
                }
                if (curr == down1)
                {
                    if (player1y + 4 < height)
                    {
                        player1->movedown();
                    }
                }
                if (curr == down2)
                {
                    if (player2y + 4 < height)
                    {
                        player2->movedown();
                    }
                }

                if (ball->getdir() == stop1)
                {
                    ball->random_dir();
                }
                if (curr == 'q')
                {
                    quit = true;
                }
            }

        }

        void logic1()
        {
            int ballx = ball->getx();
            int bally = ball->gety();
            int player1x = player1->getx();
            int player1y = player1->gety();
            int player2x = player2->getx();
            int player2y = player2->gety();

            //left paddle
            for (int i = 0; i < 4; i++)
            {
                if (ballx == player1x + 1)
                {
                    if (bally == player1y + i)
                    {
                        ball->change_dir((direction1)((rand() % 3 + 4)));
                    }
                }
            }

            //right paddle
            for (int i = 0; i < 4; i++)
            {
                if (ballx == player2x - 1)
                {
                    if (bally == player2y + i)
                    {
                        ball->change_dir((direction1)((rand() % 3 + 1)));
                    }
                }
            }

            // bottom wall
            if (bally == height - 1)
            {
                ball->change_dir(ball->getdir() == downright1 ? upright1 : upleft1);
            }

            // top wall
            if (bally == 0)
            {
                ball->change_dir(ball->getdir() == upright1 ? downright1 : downleft1);
            }

            // right wall
            if (ballx == width - 1)
            {
                scoreup(player1);
            }

            if (ballx == 0)
            {
                scoreup(player2);
            }
        }

        void run()
        {
            while (!quit)
            {
                draw1();
                input1();
                logic1();
                Sleep(40);
            }
        }
    };

//PONG GAME END

// TIC TAC TOE START
class tic_tac_toe
{
public:

    void draw_board(char arr[3][3])
    {
        cout << "\n\n\n";
        cout << "\t\t\t\t\t\t\t             |     |    \n";
        cout << "\t\t\t\t\t\t\t          " << arr[0][0] << "  |  " << arr[0][1] << "  |  " << arr[0][2] << "\n";
        cout << "\t\t\t\t\t\t\t         ____|_____|____\n";

        cout << "\t\t\t\t\t\t\t             |     |    \n";
        cout << "\t\t\t\t\t\t\t          " << arr[1][0] << "  |  " << arr[1][1] << "  |  " << arr[1][2] << "\n";
        cout << "\t\t\t\t\t\t\t         ____|_____|____\n";

        cout << "\t\t\t\t\t\t\t             |     |    \n";
        cout << "\t\t\t\t\t\t\t          " << arr[2][0] << "  |  " << arr[2][1] << "  |  " << arr[2][2] << "\n";
        cout << "\t\t\t\t\t\t\t             |     |    \n";
    }

    void title_display()
    {
        cout << "\n\n************************************************************************************************************************************************";
        cout << "\n\t\t\t\t\t\t\t\t TIC-TAC-TOE GAME ";
        cout << "\n************************************************************************************************************************************************";

        char arr[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };
        draw_board(arr);

        cout << "\n\nWelcome to the classic game of Tic-tac-toe! To start Player 1 is 'X' and player 2 is 'O'. Then, when it's your turn, choose a position on the board where you want to place your character. The board is numbered from 1 to 9, starting from the top left and ending at the bottom right.\n\nRemember, you cannot place your character in a position that is already occupied. After each move, the game board will update and the computer will check if there is a winner or if the game is a draw.\n\nGet ready to play and have fun!";


    }

    void thanks_message()
    {
        cout << "\n\n================================================================================================================================================";
        cout << "\n\t\t\t\t\t\t\t         THANK YOU FOR PLAYING";
        cout << "\n================================================================================================================================================";
    }

    void loading_bar()
    {
        // to use the extended ASCII table of CP437 Character encoding
        SetConsoleCP(437);
        SetConsoleOutputCP(437);

        char ch1 = 177, ch2 = 219;              // characters used to make loading bar

        cout << "\n\n\n\t\t\t\t\t\t\t            LOADING..... \n";
        cout << "\n\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the base bar in one go
        {
            cout << ch1;
        }
        cout << "\r";                         // takes the cursor to the starting of previous line 
        cout << "\t\t\t\t\t\t            ";
        for (int i = 0; i < 25; i++)             // prints the loading bar with 75ms time gap between each character
        {
            cout << ch2;
            Sleep(75);
        }
    }

    bool isvalid(char arr[3][3], int pos)
    {
        if (pos < 1 || pos>9)
        {
            return false;
        }

        pos--;
        int row_no = pos / 3, col_no = pos % 3;

        char ch = arr[row_no][col_no];
        if (ch == 'X' || ch == 'O')
        {
            return false;
        }

        return true;
    }

    bool player_win(char arr[3][3], char ch)
    {
        if (arr[0][0] == ch && arr[0][1] == ch && arr[0][2] == ch)
        {
            return true;
        }
        else if (arr[1][0] == ch && arr[1][1] == ch && arr[1][2] == ch)
        {
            return true;
        }
        else if (arr[2][0] == ch && arr[2][1] == ch && arr[2][2] == ch)
        {
            return true;
        }

        else if (arr[0][0] == ch && arr[1][0] == ch && arr[2][0] == ch)
        {
            return true;
        }
        else if (arr[0][1] == ch && arr[1][1] == ch && arr[2][1] == ch)
        {
            return true;
        }
        else if (arr[0][2] == ch && arr[1][2] == ch && arr[2][2] == ch)
        {
            return true;
        }

        else if (arr[0][0] == ch && arr[1][1] == ch && arr[2][2] == ch)
        {
            return true;
        }
        else if (arr[0][2] == ch && arr[1][1] == ch && arr[2][0] == ch)
        {
            return true;
        }

        return false;
    }

    bool board_full(char arr[3][3])
    {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (arr[i][j] != 'X' && arr[i][j] != 'O')
                {
                    return false;
                }
            }
        }

        return true;
    }

    void main_tic_tac_toe()
    {
        title_display();                                                //1st time title display
        loading_bar();                                                  // then loading bar for looks

        cout << "\n\n\n\t\t\t\t\t\t\t      Press any key to START";
        _getch();

        //main logic starts from here

        unordered_map<int, char> m;
        m.insert({ 1,'X' });
        m.insert({ 2,'O' });

        char play_again;
        do
        {
            char arr[3][3] = { {'1','2','3'},{'4','5','6'},{'7','8','9'} };

            int curr_player = 0;  // starting from player 1
            int no_of_moves[2] = { 0 };

            while (true)
            {
                cls;
                cout << "\n Current state of board:- ";
                draw_board(arr);

                int ip_curr_player;
                cout << "\n\nPlayer " << curr_player + 1 << ", Enter the position where you want to place " << m[curr_player + 1] << " = ";
                cin >> ip_curr_player;

                if (ip_curr_player == -1) // during development in case we need to break the loop immediately.
                {
                    break;
                }

                while (!(isvalid(arr, ip_curr_player))) // to check if position entered is valid or not 
                {
                    int updated_pos;
                    cout << "\n **** The position you have entered is invalid. It may already be occupied or out of bounds. ****\n\nPlease provide a valid position = ";
                    cin >> updated_pos;
                    ip_curr_player = updated_pos;
                }

                no_of_moves[curr_player]++;

                ip_curr_player--;
                arr[ip_curr_player / 3][ip_curr_player % 3] = m[curr_player + 1];  // makin changes to board

                cout << "\nMOVE REGISTERED !! \n";

                if (no_of_moves[curr_player] >= 3 && player_win(arr, m[curr_player + 1]))  // to check if there is a win after recent move
                {
                    cls;
                    cout << "\n Current state of board:- ";
                    draw_board(arr);
                    cout << "\n PLAYER " << curr_player + 1 << " WON !!!";
                    break;
                }
                else if (board_full(arr))  // to check if there is a draw after recent move
                {
                    cls;
                    cout << "\n Current state of board:- ";
                    draw_board(arr);
                    cout << "\n THE GAME IS A DRAW !!!";
                    break;
                }

                curr_player = !curr_player;  // switching players
                cout << "\n Ongoing...";
                system("pause");
            }

            cout << "\n\n Do you want to play again ? (y/Y-yes or n/N-no) : ";
            cin >> play_again;

        } while (play_again == 'Y' || play_again == 'y');

        //main logic ends here

        thanks_message();
    }
};
//TIC TAC TOE END

int main()
{
    abc:
	cls;
    system("color 0b");
	menu_display();
	int choice;
	cin >> choice;

	switch (choice)
	{
	case 1:
		cls;
        system("color B0");
		tic_tac_toe tic;
        tic.main_tic_tac_toe();
		break;
	case 2:
       cls;
        system("color A0");
        title_display();                                                //1st time title display
        loading_bar();                                                  // then loading bar for looks

        cout << "\n\n\n\t\t\t\t\t\t\t      Press any key to START";
        _getch();

        char play_again;

        do {

            setup();
            while (gameover != true)
            {
                draw();
                input();
                logic();

                Sleep(75);
            }

            cout << "\n\n GAME OVER, FINAL SCORE = " << score << "\n";

            cout << "\n\n Do you want to play again ? (y/Y-yes or n/N-no) : ";
            cin >> play_again;
        } while (play_again == 'y' || play_again == 'Y');
 

        thanks_message();
		break;
    
		
	case 3:

       cls;
        system("color E0");
        title_display1();                                                //1st time title display
        loading_bar1();                                                  // then loading bar for looks

        cout << "\n\n\n\t\t\t\t\t\t\t      Press any key to START";
        _getch();

        char play_again1;

        do {

            game_manager c(40, 20);
            c.run();
            
            cout << "\n\n GAME OVER, FINAL SCORE: Player 1 = " << c.score1<< " Player 2 = "<<c.score2<<"\n";
            if (c.score1 > c.score2)
            {
                cout << "\n PLAYER 1 WON";
            }
            else if (c.score1 < c.score2)
            {
                cout << "\n PLAYER 2 WON";
            }
            else
            {
                cout << "\n DRAW";
            }

            cout << "\n\n Do you want to play again ? (y/Y-yes or n/N-no) : ";
            cin >> play_again1;
        
        } while (play_again1 == 'y' || play_again1 == 'Y');



        thanks_message1();
        break;
    
    case 4:
        break;

	default:
		cout << "\n\n INVALID CHOICE";
		break;
	}

    if (choice != 4)
    {
        goto abc;
    }

    cout << "\n\n=========================================================================================================================================================";
    cout << "\n\t\t\t\t\t\t\t THANK YOU FOR TRYING MY GAMES CONSOLE";
    cout << "\n=========================================================================================================================================================";

	cout << "\n\n\n\n\n\n\n";
	return 0;
}