#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

#include "playingcard.h"
#include "pokerhand.h"

//Poker Comparator program, calculates the winner with given 5 card hands
//Author: Aleksandr Kovalev - 8/17/2017

std::string handAnalyzer (PokerHand playerhand, std::map <PlayingCard::Value, std::string> card_str);
void printHand (PokerHand playerhand, std::map <PlayingCard::Value, std::string> card_str); 
void checkWinner (std::vector <std::string> players, std::map<std::string, PlayingCard::Value> card_val);

int main()
{
	
	std::string val, type;
	std::map<std::string, PlayingCard::Value> card_values;
	std::map<std::string, PlayingCard::Suit> card_suits;
	std::map<PlayingCard::Value, std::string> card_values_str;
	std::vector <PokerHand> players;
	std::vector <std::string> players_rank;
	
	std::cout << "---Poker Hand Comparator---\n\n";
	std::cout << "Enter your cards in this format -> 'K H' " << std::endl;
	
	//map for user inputs
	card_values["2"] = PlayingCard::TWO; card_values["3"] = PlayingCard::THREE; card_values["4"] = PlayingCard::FOUR; 
	card_values["5"] = PlayingCard::FIVE; card_values["6"] = PlayingCard::SIX; card_values["7"] = PlayingCard::SEVEN;
	card_values["8"] = PlayingCard::EIGHT; card_values["9"] = PlayingCard::NINE; card_values["10"] = PlayingCard::TEN;
	card_values["J"] = PlayingCard::JACK; card_values["Q"] = PlayingCard::QUEEN; card_values["K"] = PlayingCard::KING;
	card_values["A"] = PlayingCard::ACE;
	
	card_suits["H"] = PlayingCard::HEART;
	card_suits["S"] = PlayingCard::SPADE;
	card_suits["D"] = PlayingCard::DIAMOND;
	card_suits["C"] = PlayingCard::CLUB;
	//map input ends
	
	//map to string output
	card_values_str[PlayingCard::TWO] = "2"; card_values_str[PlayingCard::THREE] = "3"; PlayingCard::THREE; card_values_str[PlayingCard::FOUR] = "4";
	card_values_str[PlayingCard::FIVE] = "5"; card_values_str[PlayingCard::SIX] = "6"; PlayingCard::THREE; card_values_str[PlayingCard::SEVEN] = "7";
	card_values_str[PlayingCard::EIGHT] = "8"; card_values_str[PlayingCard::NINE] = "9"; PlayingCard::THREE; card_values_str[PlayingCard::TEN] = "10";
	card_values_str[PlayingCard::JACK] = "J"; card_values_str[PlayingCard::QUEEN] = "Q"; PlayingCard::THREE; card_values_str[PlayingCard::KING] = "K";
	card_values_str[PlayingCard::ACE] = "A";
	//map output end
	
	int num_of_players = 1;
		
		for(int i = 0; i <= num_of_players; i++){ // loop for player card input
			
			std::cout << "Player " << i+1 << "." << std::endl;
			
			std::cin >> val;		
			std::cin >> type;
		
  			PlayingCard *C1 = new PlayingCard(card_suits[type], card_values[val]);
  	
  			std::cin >> val;		
			std::cin >> type;                                                                 
  	                                  
  			PlayingCard *C2 = new PlayingCard(card_suits[type], card_values[val]);
  	
  			std::cin >> val;		
			std::cin >> type;                                                                 
  			                                  
  			PlayingCard *C3 = new PlayingCard(card_suits[type], card_values[val]);
  	
  			std::cin >> val;		
			std::cin >> type;                                                                 
  	                                  
  			PlayingCard *C4 = new PlayingCard(card_suits[type], card_values[val]);
  	
  			std::cin >> val;		
			std::cin >> type;                                                                 
  	                                  
  			PlayingCard *C5 = new PlayingCard(card_suits[type], card_values[val]);
  			
  			players.push_back(PokerHand(*C1, *C2, *C3, *C4, *C5));
  			players_rank.push_back("UNRANKED");
  			
  			std::cout << "Your hand values are: " ;
  			printHand (players[i], card_values_str);
  			
  			players_rank[i] = handAnalyzer(players[i], card_values_str);
  			std::cout << "Hand Rank: " << players_rank[i] << std::endl;
		
	}	
		
	checkWinner(players_rank, card_values);
  		
	return 0;
	
}

std::string handAnalyzer (PokerHand playerhand, std::map <PlayingCard::Value, std::string> card_str){
	
	//ranking checks are in order, the highest is checked first. If hand passes a check it is returned at the highest rank possible.
	std::string rank = "";
	
	//flush check
	bool flush = true;
	PlayingCard temp = playerhand.hand[0];
	for(std::vector<PlayingCard>::iterator it = playerhand.hand.begin(); it != playerhand.hand.end(); it++){
		if(temp.suit != it->suit)
			flush = false;
	}
	
	if(flush){
		
		rank = "FLUSH, ";
		
		if( (int)playerhand.hand[0].value == 8 && (int)playerhand.hand[1].value == 9
			&& (int)playerhand.hand[2].value == 10 && (int)playerhand.hand[3].value == 11
			&& (int)playerhand.hand[4].value == 12 ){
				rank = "ROYAL_FLUSH, ";
				rank += card_str[playerhand.hand[4].value];
				return rank;
			}
			
		
		if( (int)playerhand.hand[0].value  == ((int)playerhand.hand[4].value - 4) 
			&& (int)playerhand.hand[1].value  == ((int)playerhand.hand[3].value - 2)
			&& (int)playerhand.hand[1].value  == ((int)playerhand.hand[2].value - 1))
			rank = "STRAIGHT_FLUSH, ";
		
		//rare low ace straight check - A 2 3 4 5	
		if( (int)playerhand.hand[0].value  == 0 && (int)playerhand.hand[1].value  == 1
			&& (int)playerhand.hand[2].value  == 2 && (int)playerhand.hand[3].value == 3
			&& (int)playerhand.hand[4].value == 12){
				rank = "STRAIGHT_FLUSH, ";
				rank += card_str[playerhand.hand[3].value];
				return rank;
			}
			
		
				
		rank += card_str[playerhand.hand[4].value];
		return rank;
	}
	//flush check end

	
	//four of a kind check
	if(	(playerhand.hand[2].value == playerhand.hand[1].value && playerhand.hand[2].value == playerhand.hand[3].value)
			&& ((playerhand.hand[2].value == playerhand.hand[0].value && playerhand.hand[2].value != playerhand.hand[4].value)
				|| (playerhand.hand[2].value == playerhand.hand[4].value && playerhand.hand[2].value != playerhand.hand[0].value)) ){
					
					rank = "FOUR_OF_A_KIND, ";
					//rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[4].value];
					
					//determines high card that is not in pairs		
					if ( card_str[playerhand.hand[0].value] == card_str[playerhand.hand[3].value])
						rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[4].value];
					else
						rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[0].value];
						
					return rank;
				}
				
	//Full house check  pair on left
	if((playerhand.hand[2].value == playerhand.hand[4].value && playerhand.hand[2].value != playerhand.hand[1].value)
		&& playerhand.hand[0].value == playerhand.hand[1].value){
			
			rank = "FULL_HOUSE, ";
			rank += card_str[playerhand.hand[4].value];
			return rank;
			
		}
		
	//Full house check  pair on right
	if((playerhand.hand[2].value == playerhand.hand[0].value && playerhand.hand[2].value != playerhand.hand[3].value)
		&& playerhand.hand[3].value == playerhand.hand[4].value){
			
			rank = "FULL_HOUSE, ";
			rank += card_str[playerhand.hand[4].value];
			return rank;
			
		}	
	
	//Straight check
	if( (int)playerhand.hand[0].value  == ((int)playerhand.hand[4].value - 4) 
			&& (int)playerhand.hand[1].value  == ((int)playerhand.hand[3].value - 2)
			&& (int)playerhand.hand[1].value  == ((int)playerhand.hand[2].value - 1)){
		
		rank = "STRAIGHT, ";
		rank += card_str[playerhand.hand[4].value];
		return rank;
		
	}
	
	//rare low ace straight check - A 2 3 4 5
	if( (int)playerhand.hand[0].value  == 0 && (int)playerhand.hand[1].value  == 1
			&& (int)playerhand.hand[2].value  == 2 && (int)playerhand.hand[3].value == 3
			&& (int)playerhand.hand[4].value == 12){
		
		rank = "STRAIGHT, ";
		rank += card_str[playerhand.hand[3].value];
		return rank;
		
	}
	
	
	//Three of a kind in the middle
	if((playerhand.hand[2].value == playerhand.hand[3].value && playerhand.hand[2].value == playerhand.hand[1].value) 
		&& playerhand.hand[0].value != playerhand.hand[1].value && playerhand.hand[4].value != playerhand.hand[3].value){
		
		rank = "THREE_OF_A_KIND, ";
		rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[4].value];
		return rank;
		
	}
	
	
	//Three of a kind check on right side of hand
	if((playerhand.hand[2].value == playerhand.hand[4].value && playerhand.hand[2].value != playerhand.hand[1].value)
		&& playerhand.hand[0].value != playerhand.hand[1].value){
		
		rank = "THREE_OF_A_KIND, ";
		rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[4].value];
		return rank;
		
	}
	
	//Three of a kind check on left side of hand
	if((playerhand.hand[2].value == playerhand.hand[0].value && playerhand.hand[2].value != playerhand.hand[3].value)
		&& playerhand.hand[3].value != playerhand.hand[4].value){
		
		rank = "THREE_OF_A_KIND, ";
		rank += card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[4].value];
		return rank;
		
	}
	
	//two pair check
	if(	(playerhand.hand[1].value == playerhand.hand[0].value || playerhand.hand[1].value == playerhand.hand[2].value) 
		&& (playerhand.hand[3].value == playerhand.hand[2].value || playerhand.hand[3].value == playerhand.hand[4].value)
		&& (playerhand.hand[3].value != playerhand.hand[1].value)){
		
		rank = "TWO_PAIR, ";
		
		//the higher pair is first
		if ( card_str[playerhand.hand[1].value] > card_str[playerhand.hand[3].value])
			rank += card_str[playerhand.hand[1].value] + ", " + card_str[playerhand.hand[3].value];
		else
			rank += card_str[playerhand.hand[3].value] + ", " + card_str[playerhand.hand[1].value];
		
		//determines high card that is not in pairs			
		if( (card_str[playerhand.hand[1].value] != card_str[playerhand.hand[0].value]) 
				&& (card_str[playerhand.hand[3].value] != card_str[playerhand.hand[0].value])
				&& (card_str[playerhand.hand[0].value] < card_str[playerhand.hand[1].value]))
					rank +=  ", " + card_str[playerhand.hand[0].value];
			
		else if( (card_str[playerhand.hand[1].value] != card_str[playerhand.hand[2].value]) 
				&& (card_str[playerhand.hand[3].value] != card_str[playerhand.hand[2].value])
				&& (card_str[playerhand.hand[2].value] > card_str[playerhand.hand[1].value])
				&& (card_str[playerhand.hand[2].value] < card_str[playerhand.hand[3].value]))
					rank +=  ", " + card_str[playerhand.hand[2].value];
		else 
				rank +=  ", " + card_str[playerhand.hand[4].value];
		
		return rank;
		
	}
	
	//pair check
	if(	(playerhand.hand[1].value == playerhand.hand[0].value || playerhand.hand[1].value == playerhand.hand[2].value)
		|| (playerhand.hand[3].value == playerhand.hand[2].value || playerhand.hand[3].value == playerhand.hand[4].value)
		){
		
		rank = "ONE_PAIR, ";
		
		//determines high card that is not in pair
		if(playerhand.hand[1].value == playerhand.hand[0].value)
			rank += card_str[playerhand.hand[1].value] + ", " + card_str[playerhand.hand[2].value]
					+ ", " + card_str[playerhand.hand[3].value] + ", " + card_str[playerhand.hand[4].value];
		else if(playerhand.hand[1].value == playerhand.hand[2].value)
			rank += card_str[playerhand.hand[1].value]  + ", " + card_str[playerhand.hand[0].value]
					+ ", " + card_str[playerhand.hand[3].value] + ", " + card_str[playerhand.hand[4].value];
		else if(playerhand.hand[3].value == playerhand.hand[2].value)
			rank += card_str[playerhand.hand[3].value] + ", " + card_str[playerhand.hand[0].value]
					+ ", " + card_str[playerhand.hand[1].value] + ", " + card_str[playerhand.hand[4].value];
		else
			rank += card_str[playerhand.hand[3].value] + ", " + card_str[playerhand.hand[0].value]
					+ ", " + card_str[playerhand.hand[1].value] + ", " + card_str[playerhand.hand[2].value];
					
		return rank;
		
	}
	
	//if none of the above just return the hand sorted 
	rank = card_str[playerhand.hand[0].value] + ", " + card_str[playerhand.hand[1].value] + ", "
		+ card_str[playerhand.hand[2].value] + ", " + card_str[playerhand.hand[3].value] + ", "
		+ card_str[playerhand.hand[4].value] ;
	
	return rank;
	
}

void printHand (PokerHand playerhand, std::map <PlayingCard::Value, std::string> card_str){
	
	
		for(std::vector<PlayingCard>::iterator it = playerhand.hand.begin(); it != playerhand.hand.end(); it++)
			std::cout << card_str[it->value] << " " ;
			
		
		std::cout << std::endl;
		
}

void checkWinner (std::vector <std::string> players, std::map<std::string, PlayingCard::Value> card_val){
	
	std::vector <int> players_score(players.size(), 0);
	
	//scores the ranked hand
	for(int i = 0; i < players.size(); i++){
	
		if(players[i].find("ROYAL_FLUSH,") != -1)
			players_score[i] = 10;
		
		else if(players[i].find("STRAIGHT_FLUSH,") != -1)
			players_score[i] = 9;
			
		else if(players[i].find("FOUR_OF_A_KIND,") != -1)
			players_score[i] = 8;
			
		else if(players[i].find("FULL_HOUSE,") != -1)
			players_score[i] = 7;
			
		else if(players[i].find("FLUSH,") != -1)
			players_score[i] = 6;
			
		else if(players[i].find("STRAIGHT,") != -1)
			players_score[i] = 5;
			
		else if(players[i].find("THREE_OF_A_KIND,") != -1)
			players_score[i] = 4;
			
		else if(players[i].find("TWO_PAIR,") != -1)
			players_score[i] = 3;
		
		else if(players[i].find("ONE_PAIR,") != -1)
			players_score[i] = 2;
		else 
			players_score[i] = 1; // just high card
								
	}
	
	int max = 0;
	int pos = 0;
	
	for(int j = 0; j < players_score.size(); j++){
		
		if(players_score[j] > max){
			max = players_score[j];
			pos	= j;
		}	

	}
	
	//tie braking if players have same rank
	if(1 < std::count (players_score.begin(), players_score.end(), max)){
		
		//Royal flush
		if(max == 10){
			std::cout << "DRAW!" << std::endl;
			return;
		}
		
		//flushes, straight, full house, high card
		if(max == 9 || max == 7 || max == 6 || max == 5 || max == 1 ){
			
			for(int k = 0; k < players_score.size(); k++){
				if(players_score[k] == max){
					
					std::string highCard(1, players[k].at(players[k].length()-1));
					players_score[k] = players_score[k] + (int)card_val[highCard];
				}	
			}
			
			max = 0;
			pos = 0;
	
			for(int j = 0; j < players_score.size(); j++){
		
				if(players_score[j] > max){
					max = players_score[j];
					pos	= j;
				}	
			}			
		}
		
		//everyother tie
		if(max == 8 || max == 4 || max == 3 || max == 2){
			
			for(int z = 0 ; z < players_score.size(); z++){
				
				int space_pos;
				if(players_score[z] == max){
			
					space_pos = players[z].find_first_of(' ');
					
					std::string highCard(1, players[z].at(space_pos + 1));
					players_score[z] = players_score[z] + (int)card_val[highCard];
					
				}
				
			
			}
			
			max = 0;
			pos = 0;
	
			for(int x = 0; x < players_score.size(); x++){
		
				if(players_score[x] > max){
					max = players_score[x];
					pos	= x;
				}	
			}
			
			if(1 < std::count (players_score.begin(), players_score.end(), max)){
				
			
				if(players[pos].find("TWO_PAIR") != -1){
				
					for(int z = 0 ; z < players_score.size(); z++){
				
					int space_pos;
					if(players_score[z] == max){
			
						space_pos = players[z].find_first_of(' ');
						std::string highCard(1, players[z].at(space_pos + 4));
						players_score[z] = players_score[z] + (int)card_val[highCard];
					
					}
				
			
				}
			
					max = 0;
					pos = 0;
	
					for(int x = 0; x < players_score.size(); x++){
		
						if(players_score[x] > max){
							max = players_score[x];
							pos	= x;
						}	
					}
				
				if(1 == std::count (players_score.begin(), players_score.end(), max)){
						std::cout << "Player: " << pos+1 << " Wins! " << std::endl;
						return;					
					}
				
			}
			
				
			for(int k = 0; k < players_score.size(); k++){
				if(players_score[k] == max){
					
					std::string highCard(1, players[k].at(players[k].length()-1));
					players_score[k] = players_score[k] + (int)card_val[highCard];
				}	
			}
			
			max = 0;
			pos = 0;
	
			for(int j = 0; j < players_score.size(); j++){
		
				if(players_score[j] > max){
					max = players_score[j];
					pos	= j;
				}	
			}			
				
			}		

		}
		
	}
	
	if(1 < std::count (players_score.begin(), players_score.end(), max))
		std::cout << "Draw! " << std::endl;
	else
		std::cout << "Player: " << pos+1 << " Wins! " << std::endl;
	
}
