#include "menu_functions.h"

char menu_sfml_objects::check_character(int key_number, bool shift_pressed, bool & caps_lock_pressed)
{
	switch (key_number)
	{
	case 0: // a/A
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'A';
		}
		else
			return 'a';
	break;

	case 1: // b/B
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'B';
		}
		else
			return 'b';
		break;

	case 2: // c/ C
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'C';
		}
		else
			return 'c';
		break;

	case 3: // d/D
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'D';
		}
		else
			return 'd';
		break;

	case 4: // e/E
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'E';
		}
		else
			return 'e';
		break;

	case 5: // f/F
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'F';
		}
		else
			return 'f';
		break;

	case 6: // g/G
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'G';
		}
		else
			return 'g';
		break;

	case 7: // h/H
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'H';
		}
		else
			return 'h';
		break;

	case 8: // i/\I
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'I';
		}
		else
			return 'i';
		break;
	case 9: // j/J
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'J';
		}
		else
			return 'j';
		break;

	case 10: // k/K
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'K';
		}
		else
			return 'k';
		break;

	case 11: // l/L
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'L';
		}
		else
			return 'l';
		break;

	case 12: // m/M
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'M';
		}
		else
			return 'm';
		break;

	case 13: // n/N
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'N';
		}
		else
			return 'n';
		break;

	case 14: // o/O
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'O';
		}
		else
			return 'o';
		break;

	case 15: // p/P
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'P';
		}
		else
			return 'p';
		break;

	case 16: // q/Q
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'Q';
		}
		else
			return 'q';
		break;

	case 17: // r/R
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'R';
		}
		else
			return 'r';
		break;

	case 18: // s/S
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'S';
		}
		else
			return 's';
		break;

	case 19: // t/T
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'T';
		}
		else
			return 't';
		break;

	case 20: // u/U
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'U';
		}
		else
			return 'u';
		break;

	case 21: // v/V
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'V';
		}
		else
			return 'v';
		break;

	case 22: // w/W
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'W';
		}
		else
			return 'w';
		break;

		//Pomijamy 23 bo to strza³ka w dó³

	case 24: // y/Y
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'Y';
		}
		else
			return 'y';
		break;

	case 25: // z/Z
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return 'Z';
		}
		else
			return 'z';
		break;

	case 26: // 0/)
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return ')';
		}
		else
			return '0';
		break;

	case 27: // 1/!
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '!';
		}
		else
			return '1';
		break;

	case 28: // 2/@
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '@';
		}
		else
			return '2';
		break;

	case 29: // 3/#
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '#';
		}
		else
			return '3';
		break;

	case 30: // 4/$
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '$';
		}
		else
			return '4';
		break;

	case 31: // 5/%
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '%';
		}
		else
			return '5';
		break;

	case 32: // 6/^
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '^';
		}
		else
			return '6';
		break;

	case 33: // 7/&
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '&';
		}
		else
			return '7';
		break;

	case 34: // 8/*
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '*';
		}
		else
			return '8';
		break;

	case 35: // 9/(
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '(';
		}
		else
			return '9';
		break;

		// shift do ogarniêcia  mo¿liwe ¿e w osobnej funkcji, wartoœæ zwracana to 38

	//case 38: // shift
	//	if (shift_pressed == true || caps_lock_pressed == true)
	//	{
	//		//return '';
	//	}
	//	else
	//		//return '9';
	//	break;

	//case -1: // caps lock tak samo jak z shiftem
	//	if (shift_pressed == true || caps_lock_pressed == true)
	//	{
	//		return '(';
	//	}
	//	else
	//		return '9';
	//	break;

	//case 58: // enter tak samo
	//	if (shift_pressed == true || caps_lock_pressed == true)
	//	{
	//		return '(';
	//	}
	//	else
	//		return '9';
	//	break;

	case 46: // [    {
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '{';
		}
		else
			return '[';
		break;

	case 47: // ]    }
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '}';
		}
		else
			return ']';
		break;

	case 48: // ;    :
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return ':';
		}
		else
			return ';';
		break;

	case 49: // ,   <
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '<';
		}
		else
			return ',';
		break;

	case 50: // .   >
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '>';
		}
		else
			return '.';
		break;

	case 51: // '   "
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '\"';
		}
		else
			return '\'';
		break;
	case 52: // " / "   ?
 		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '?';
		}
		else
			return '//';
		break;
	case 53: // " \ "	|
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '|';
		}
		else
			return '\\';
		break;

	case 54: // `	~
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '~';
		}
		else
			return '`';
		break;

	case 55: // =   +
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '+';
		}
		else
			return '=';
		break;

	case 56: // -   _
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return '_';
		}
		else
			return '-';
		break;

	case 57: // " "
		if (shift_pressed == true || caps_lock_pressed == true)
		{
			return ' ';
		}
		else
			return ' ';
		break;
	default:
		return NULL;
		break;

	}

}
