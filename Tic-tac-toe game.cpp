#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
int cnt = 0;
class variable
{
public:
    string board[9] = {" ", " ", " ", " ", " ", " ", " ", " ", " "};
    int player = 1;
    int position = 0;
    string p1, p2;

};
class winner: public variable
{
protected:
    bool is_winner()
    {
        bool winner = false; //Initially declaring winner as false.

        //Checking the rows.

        if ((board[0] == board[1]) && (board[1] == board[2]) && board[0] != " ")
        {
            winner = true;
        }
        else if ((board[3] == board[4]) && (board[4] == board[5]) && board[3] != " ")
        {
            winner = true;
        }

        else if ((board[6] == board[7]) && (board[7] == board[8]) && board[6] != " ")
        {
            winner = true;
        }

        //checking the columns

        else if ((board[0] == board[3]) && (board[3] == board[6]) && board[0] != " ")
        {
            winner = true;
        }

        else if ((board[1] == board[4]) && (board[4] == board[7]) && board[1] != " ")
        {
            winner = true;
        }

        else if ((board[2] == board[5]) && (board[5] == board[8]) && board[2] != " ")
        {
            winner = true;
        }

        //checking the diagonals

        else if ((board[0] == board[4]) && (board[4] == board[8]) && board[0] != " ")
        {
            winner = true;
        }

        else if ((board[2] == board[4]) && (board[4] == board[6]) && board[2] != " ")
        {
            winner = true;
        }

        return winner;
    }
};
class Position: public winner
{
protected:
    void setposition()
    {
        cout << "Player " << player << "'s turn (Enter: 1-9)"; //1-9 (Enter: (1-9))
        while (!(cin >> position))
        {
            cout << "Please enter a valid number between (1-9)" << endl;
            cin.clear();  //flushing the buffer
            cin.ignore();
        }
        cout << endl;

        while (board[position - 1] != " ") {
            cout << "Oops, that position is already filled\nTry again\n";
            cout << "Player " << player << "'s Turn (Enter 1-9): ";
            cin >> position;
            cout << "\n";
        }
    }
};


class filled: public Position
{
protected:
    bool filled_up()
    {
        bool filled = true;

        for (int i = 0; i < 9; i++)
        {
            if (board[i] == " ")
            {
                filled = false;
            }
        }
        return filled;
    }
};


class update: public filled
{
protected:
    void update_board()
    {
        if (player == 1) {
            board[position - 1] = "X";   //1-9        0-8
        }
        else
        {
            board[position - 1] = "O";
        }
    }
};
class playerchange: public update
{
protected:
    void change_player() {
        if (player == 1) {
            player++;
        }
        else {
            player--;
        }
    }
};
class Draw: public playerchange
{
protected:
    void draw()
    {
        cout <<  "     |     |      \n";
        cout << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
        cout << "_____|_____|_____ \n";
        cout << "     |     |      \n";
        cout << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
        cout << "_____|_____|_____ \n";
        cout << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
        cout << "     |     |      \n";
        cout << "\n";
    }
};
class end: public Draw
{
public:
    void end_game();
};
void end::end_game()
{
    ofstream file("Tic_Tac_Toe.txt");
    if (is_winner())
    {
        cout << "So! the winner is" << endl;
        for (int i = 1 ; i <= 6 ; i++)
        {
            cout << '!';
            Sleep(500);
        }
        cout << endl;
        (player == 1) ? cout << p2 : cout << p1;
        cout << " is winner" << endl;
        file << "  Game result:\n" << endl;
        file << "It has been announced that ";
        (player == 1) ? file << p2 : file << p1;
        file << " is winner\n\n" << endl;
        file << " ****The overall gamechart ****" << endl;
        file << "_____________________________" << "\n\n";
        file <<  "     |     |      \n";
        file << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
        file << "_____|_____|_____ \n";
        file << "     |     |      \n";
        file << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
        file << "_____|_____|_____ \n";
        file << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
        file << "     |     |      \n";
        file << "\n";
        file.close();
    }
    else if (filled_up())
    {
        cout << "There is a tie!" << endl;
        file << "There is a tie!" << "\n\n" ;
        file << " ****The overall gamechart ****" << endl;
        file << "_____________________________" << "\n\n";
        file <<  "     |     |      \n";
        file << "  " << board[0] << "  |  " << board[1] << "  |  " << board[2] << "\n";
        file << "_____|_____|_____ \n";
        file << "     |     |      \n";
        file << "  " << board[3] << "  |  " << board[4] << "  |  " << board[5] << "\n";
        file << "_____|_____|_____ \n";
        file << "  " << board[6] << "  |  " << board[7] << "  |  " << board[8] << "\n";
        file << "     |     |      \n";
        file << "\n";
        file.close();
    }
};
class gameplay: public end
{
public:
    friend int take_turn(gameplay obj)
    {
        char gamer;
        while (1)
        {
            if (cnt == 1)
            {
                char final;
                cout << "\n\n***Game is finished.Want to see the result again (Y/N)***" << endl;
                cin >> final;
                if (final == 'Y')
                {
                    if (obj.is_winner())
                    {
                        cout << "\n\nWinner is ";
                        (obj.player == 1) ? cout << obj.p2 : cout << obj.p1;
                        cout << endl;
                        cout << "...The overall gameplay chart..." << endl;
                        obj.draw();
                        cout << "\nThanks for playing the game" << endl;
                        goto label;
                    }
                    else if (!obj.is_winner() && obj.filled_up())
                    {
                        cout << "\n\nThe game was tied" << "\n\n";
                        cout << "****The overall gameplay chart****" << endl;
                        cout << "_____________________________" << "\n\n";
                        obj.draw();
                        cout << "\nThanks for playing the game" << endl;
                        goto label;
                    }
                }
                else
                {
                    cout << "\nThanks for playing the game" << endl;
                    goto label;
                }
            }
            cout << "\nPress 1 to play" << endl;
            cout << "Press 2 to see result" << endl;
            cout << "Press 3 to know gameplay rules" << endl;
            cin >> gamer;
            switch (gamer)
            {
            case '1':
                cnt++;
                cout << "\n\nEnter player 1 name" << endl;
                cin >> obj.p1;
                cout << "\n\nEnter player 2 name" << endl;
                cin >> obj.p2;
                while (!obj.is_winner() && !obj.filled_up())
                {
                    //invoking the functions
                    obj.setposition();
                    obj.update_board();
                    obj.change_player();
                    obj.draw();
                    obj.end_game();
                }
                break;
            case '2':
                if (!obj.filled_up() && !obj.is_winner())
                {
                    cout << "\n\nNo previous record is found" << endl;
                    break;
                }
                else if (obj.is_winner())
                {
                    cout << "\n\nWinner is ";
                    (obj.player == 1) ? cout << obj.p2 : cout << obj.p1;
                    cout << endl;
                    cout << "...The overall gameplay chart..." << endl;
                    obj.draw();
                    break;
                }
                else if (!obj.is_winner() && obj.filled_up())
                {
                    cnt++;
                    cout << "\n\nThe game was tied" << "\n\n";
                    cout << "****The overall gameplay chart****" << endl;
                    cout << "_____________________________" << "\n\n";
                    obj.draw();
                    break;
                }
            case '3':
                cout << "\n\n1.The game is played on a grid that's 3 squares by 3 squares." << "\n";
                cout << "2.You are X, your friend (or the computer in this case) is O. Players take turns putting their marks in empty squares." << "\n";
                cout << "3.The first player to get 3 of her marks in a row (up, down, across, or diagonally) is the winner." << endl;
                cout << "4.When all 9 squares are full, the game is over." << "\n";
            }
        }
        label:return 0;
    }
};
    int main()
    {
        cout << "Press [Enter] to begin: ";
        getchar();
        cout << "\n";
        cout << "\n";
        cout << "***********\n";
        cout << "Tic-Tac-Toe\n";
        cout << "***********\n";
        cout << "Player 1) X\n";
        cout << "Player 2) O\n";
        cout << "The 3x3 grid is shown below:\n\n";
        cout << "     |     |      \n";
        cout << "  1  |"; Sleep(1000); cout << "  2  |"; Sleep(1000); cout << "  3  \n";
        cout << "_____|_____|_____ \n";
        Sleep(500);
        cout << "     |     |      \n";
        cout << "  4  |"; Sleep(1000); cout << "  5  |"; Sleep(1000); cout << "  6  \n";
        cout << "_____|_____|_____ \n";
        Sleep(500);
        cout << "     |     |      \n";
        cout << "  7  |"; Sleep(1000); cout << "  8  |"; Sleep(1000); cout << "  9  \n";
        cout << "_____|_____|_____ \n";
        Sleep(1000);
        cout << "\n\n";
        cout << "Game is starting" << endl;
        for (int i = 1 ; i <= 6 ; i++)
        {
            cout << ".";
            Sleep(500);
        }
        cout << endl;
        cout << "Almost reaching" << endl;
        for (int i = 1 ; i <= 3 ; i++)
        {
            cout << ".";
            Sleep(500);
        }
        cout << endl;
        gameplay obj;
        take_turn(obj);
        return 0;
    }
