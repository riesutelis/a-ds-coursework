// Checkers.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GameLogic.h"
#include "AI.h"


char c_for_e[11];	// characters that represent spaces on the board
bool player1 = true;		// True for player, false for AI
bool player2 = true;		// True for player, false for AI
int winner;			// When a winner is determined this gets assigned to either 1 or 2
std::deque<move> replay;	// After a game is complete this is assigned the history deque from game logic adn can be used to replay a game

int const AI_dificulty = 2;



// Prints the current board
void printBoard(GameLogic gl)
{
	std::array<std::array<space, 8>, 8> board;
	board = gl.getBoard();
	// Print some empty space to separate from previous prints
	std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == black || board[i][j] == blackKing || board[i][j] == selectedBlack || board[i][j] == selectedBlackKing)
				std::cout << (char)201 << (char)205 << (char)205 << (char)205 << (char)187;
			else if (board[i][j] == white || board[i][j] == whiteKing || board[i][j] == selectedWhite || board[i][j] == selectedWhiteKing)
				std::cout << (char)218 << (char)196 << (char)196 << (char)196 << (char)191;
			else if (board[i][j] == moveTo)
				std::cout << "     ";
			else
				std::cout << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]];
		}
		std::cout << std::endl;
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == black || board[i][j] == blackKing)
				std::cout << (char)186 << " " << c_for_e[board[i][j]] << " " << (char)186;
			else if (board[i][j] == white || board[i][j] == whiteKing)
				std::cout << (char)179 << " " << c_for_e[board[i][j]] << " " << (char)179;
			else if (board[i][j] == selectedBlack || board[i][j] == selectedBlackKing)
				std::cout << (char)186 << "(" << c_for_e[board[i][j]] << ")" << (char)186;
			else if (board[i][j] == selectedWhite || board[i][j] == selectedWhiteKing)
				std::cout << (char)179 << "(" << c_for_e[board[i][j]] << ")" << (char)179;
			else if (board[i][j] == moveTo)
				std::cout << " " << " " << c_for_e[board[i][j]] << " " << " ";
			else
				std::cout << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]];
		}
		std::cout << std::endl;
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == black || board[i][j] == blackKing || board[i][j] == selectedBlack || board[i][j] == selectedBlackKing)
				std::cout << (char)200 << (char)205 << (char)205 << (char)205 << (char)188;
			else if (board[i][j] == white || board[i][j] == whiteKing || board[i][j] == selectedWhite || board[i][j] == selectedWhiteKing)
				std::cout << (char)192 << (char)196 << (char)196 << (char)196 << (char)217;
			else if (board[i][j] == moveTo)
				std::cout << "     ";
			else
				std::cout << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]] << c_for_e[board[i][j]];
		}
		std::cout << std::endl;
	}
}




// Main
int main()
{
	replay = std::deque<move>();
	GameLogic gl = GameLogic();
	AI p1AI = AI(1, AI_dificulty);
	AI p2AI = AI(2, AI_dificulty);

	{
		// Assign chars for enums
		c_for_e[white] = 'w';
		c_for_e[whiteKing] = 'W';
		c_for_e[black] = 'b';
		c_for_e[blackKing] = 'B';
		c_for_e[selectedWhite] = 'w';
		c_for_e[selectedWhiteKing] = 'W';
		c_for_e[selectedBlack] = 'b';
		c_for_e[selectedBlackKing] = 'B';
		c_for_e[empty] = ' ';
		c_for_e[unused] = 219;
		c_for_e[moveTo] = 'X';
	}


	while (true)
	{
		std::cout << "Enter 1 to start the game." << std::endl;
		if (player1)
			std::cout << "Enter 2 to use AI for player 1." << std::endl;
		else
			std::cout << "Enter 2 to have player 1 be controlled by a player." << std::endl;
		if (player2)
			std::cout << "Enter 3 to use AI for player 2." << std::endl;
		else
			std::cout << "Enter 3 to have player 2 be controlled by a player." << std::endl;
		if (replay.size() > 0)
			std::cout << "Enter 4 to show a replay of the last game." << std::endl;
		std::cout << "Enter EXIT to exit." << std::endl;

		std::string tmp = "";
		std::getline(std::cin, tmp);
		// Player vs player game
		if (tmp == "1")
		{
			// Cycle through selections until a piece is selected
			while (true)
			{
				// AI
				if ((gl.getPlayer() == 1 && !player1) || (gl.getPlayer() == 2 && !player2))
				{
					p1AI.playerMove(gl);
					p2AI.playerMove(gl);
					std::list<move> moves;
					if (gl.getPlayer() == 1)
						moves = p1AI.getBestTurn();
					else
						moves = p2AI.getBestTurn();
					for (move m : moves)
						winner = gl.executeMove(m);
					if (winner > 0)
					{
						std::cout << "Player " << gl.getWinner() << " won!" << std::endl;
						break;
					}
					if (player1 == false && player2 == false)
					{
						printBoard(gl);
						std::cout << "Press Enter to see the next turn." << std::endl;
						if (gl.getHistory().size() > 0)
							std::cout << "Press U to undo a move." << std::endl;
						std::cout << "Press Q followed by ENTER to abandon game." << std::endl;
						std::getline(std::cin, tmp);
						if (tmp == "q" || tmp == "Q")
							break;
						// Undo
						else if (tmp == "u" || tmp == "U")
						{
							gl.undo();
							gl.undo();
							continue;
						}
					}
				}
				// Human players
				else
				{
					printBoard(gl);

					std::string tmp = "";
					std::cout << "Press ENTER for next available piece." << std::endl;
					std::cout << "Press + or # followed by ENTER for previous available piece." << std::endl;
					if (gl.getHistory().size() > 0)
						std::cout << "Press U to undo a move." << std::endl;
					if (gl.getRedoStack().size() > 0)
						std::cout << "Press R to undo a move." << std::endl;
					std::cout << "Press SPACE or 0 followed by ENTER to choose the selected piece." << std::endl;
					std::cout << "Press Q followed by ENTER to abandon game." << std::endl;
					std::getline(std::cin, tmp);
					// Next piece
					if (tmp == "")
					{
						gl.nextPiece();
					}
					// Next piece
					else if (tmp == "q" || tmp == "Q")
					{
						break;
					}
					// Previous piece
					else if (tmp == "+" || tmp == "#")
					{
						gl.prevPiece();
					}
					// Undo
					else if (tmp == "u" || tmp == "U")
					{
						if (!player1 || !player2)
							gl.undo();
						gl.undo();
						continue;
					}
					// Redo
					else if (tmp == "r" || tmp == "R")
					{
						gl.redo();
						continue;
					}
					// Select piece
					else if (tmp == " " || tmp == "0")
					{
						gl.selectPiece();
						// Cycle through available moves until a move is selected
						while (true)
						{
							printBoard(gl);

							tmp = "";
							std::cout << "Press ENTER for next available move." << std::endl;
							std::cout << "Press + or # followed by ENTER for previous available move." << std::endl;
							std::cout << "Press SPACE or 0 followed by ENTER to choose the selected move." << std::endl;
							std::cout << "Press C followed by ENTER to cancel selection." << std::endl;
							std::getline(std::cin, tmp);

							// Next move
							if (tmp == "")
							{
								gl.nextMove();
							}
							// Previous move
							else if (tmp == "+" || tmp == "#")
							{
								gl.prevMove();
							}
							// Move selected
							else if (tmp == " " || tmp == "0")
							{
								int moveOutcome = gl.executeMove();
								if (moveOutcome == -1)
									continue;
								else if (moveOutcome > 0)
									winner = moveOutcome;
								break;
							}
							// Cancel piece selection
							else if (tmp == "c" && tmp != "C")
							{
								gl.nextPiece();
								gl.prevPiece();
								break;
							}
							// Any other button pressed
							else
								continue;
						}
						if (winner > 0)
						{
							replay = gl.getHistory();
							printBoard(gl);
							std::cout << "Player " << winner << " won!" << std::endl;
							std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
							break;
						}
					}
				}
			}
		}
		// Toggle player 1 between AI and player
		else if (tmp == "2")
		{
			player1 = !player1;
		}
		// Toggle player 2 between AI and player
		else if (tmp == "3")
		{
			player2 = !player2;
		}
		// Replay
		else if (tmp == "4" && replay.size() > 0)
		{
			GameLogic rp = GameLogic();
			while (true)
			{
				printBoard(rp);
				if (replay.size() == 0)
				{
					replay = gl.getHistory();
					std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
					break;
				}
				std::cout << "Press enter for next move." << std::endl;
				std::cout << "Enter q to go back to menu." << std::endl;
				std::string tmp = "";
				std::getline(std::cin, tmp);
				if (tmp == "")
				{
					rp.executeMove(replay.front());
					replay.pop_front();
				}
				else if (tmp == "q" || tmp == "Q")
				{
					replay = gl.getHistory();
					std::cout << std::endl << std::endl << std::endl << std::endl << std::endl;
					break;
				}
			}
		}
		// Exit
		else if (tmp == "exit" || tmp == "EXIT")
		{
			return 0;
		}
	}
	return 0;
}

