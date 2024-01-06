#include <iostream>
#include <fstream>
#include <Windows.h>


unsigned int CONVERT_frequency(unsigned int oct, char note);
void SOUND(unsigned int oct, char note, double ms);
void MUSIC(bool debug);

unsigned int CONVERT_frequency(unsigned int oct, char note)
{
	unsigned int frequencies[8][12] =
	{
		{   33,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,   62 },
		{   65,   69,   73,   78,   82,   87,   92,   98,  104,  110,  117,  123 },
		{  131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247 },
		{  262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494 },
		{  524,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988 },
		{ 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976 },
		{ 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951 },
		{ 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902 }
	};

	int sylindex = 0;

	if (note == 'c') sylindex = 0;
	else if (note == 'C') sylindex = 1;
	else if (note == 'd') sylindex = 2;
	else if (note == 'D') sylindex = 3;
	else if (note == 'e') sylindex = 4;
	else if (note == 'f') sylindex = 5;
	else if (note == 'F') sylindex = 6;
	else if (note == 'g') sylindex = 7;
	else if (note == 'G') sylindex = 8;
	else if (note == 'a') sylindex = 9;
	else if (note == 'A') sylindex = 10;
	else if (note == 'b') sylindex = 11;

	return frequencies[oct - 1][sylindex];
}

void SOUND(unsigned int oct, char note, double ms)
{
	Beep(CONVERT_frequency(oct, note), ms);
}


int main()
{
	MUSIC(true);

	return 0;
}

void MUSIC(bool debug)
{
	char SHEET[201][101]{ 0 };
	char SHEET_LINE[101]{ 0 };
	int counter{ 0 };
	int octave{ 0 };
	int delay{ 0 };
	int delay_counter{ 0 };
	bool calc_delay{ false };
	char note{ 0 };
	int lane_size{ 0 };
	int sheet_size{ 0 };
	int inverse{ 0 };
	bool dash{ false };
	char delay_str[100]{ 0 };
	char lanesize_str[100]{ 0 };
	int sheet_offset{ 0 };

	std::ifstream READFILE("Music_sd.txt");

	while (READFILE.getline(SHEET_LINE, 100, '\n'))
	{
		strcpy(&SHEET[counter][0], &SHEET_LINE[0]);
		counter++;
	}
	sheet_size = counter;

	counter = 0;
	while (true)
	{
		if (SHEET[0][counter] == '|')
		{
			strncpy(&delay_str[0], &SHEET[0][0], counter);
			strcpy(&lanesize_str[0], &SHEET[0][counter + 1]);
			break;
		}
		else
		{
			counter++;
		}
	}
	if (SHEET[1][0] == 'R' || SHEET[1][0] == 'L')
	{
		sheet_offset = 5;
	}
	else
	{
		sheet_offset = 2;
	}

	delay = atoi(delay_str);
	lane_size = atoi(lanesize_str);

	for (int y = lane_size; y < sheet_size; y += lane_size)
	{
		for (int x = 0; x < 26; x++)
		{
			calc_delay = false;
			delay_counter = 1;
			dash = false;

			for (int w = 0; w < lane_size; w++)
			{
				if (SHEET[y - w][x + sheet_offset] == '-')
				{
					dash = true;
				}
				else
				{
					dash = false;
					octave = SHEET[y - w][0 + (sheet_offset - 2)] - 48;
					note = SHEET[y - w][x + sheet_offset];
					break;
				}

			}
			if (dash == true)
			{
				if (debug == true)
				{
					std::cout << "Dash on all lanes! Skipping!" << std::endl;
				}
			}
			else
			{
				while (calc_delay == false)
				{
					dash = false;
					for (int w = 0; w < lane_size; w++)
					{
						if (SHEET[y - w][(x + sheet_offset) + delay_counter] == '-')
						{
							dash = true;
						}
						else
						{
							dash = false;
							break;
						}
					}
					if (dash == true)
					{
						delay_counter += 1;
					}
					else
					{
						calc_delay = true;
					}
				}
				if (debug == true)
				{
					std::cout << "Beeping note: " << note << " at octave: " << octave << " for: " << delay * delay_counter << "ms" << std::endl;
				}
				if (delay_counter > 18)
				{
					delay_counter = 5;
				}
				SOUND(octave, note, delay * delay_counter);
			}
		}
	}
}