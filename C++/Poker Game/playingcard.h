#ifndef POKERCARD_H
#define POKERCARD_H

class PlayingCard {

public:
  bool operator<(PlayingCard card) {
    return this->value < card.value;
  }
  
  enum Suit {
    HEART, SPADE, DIAMOND, CLUB
  };
  enum Value {
    TWO, THREE, FOUR, FIVE, SIX,
    SEVEN, EIGHT, NINE, TEN, JACK,
    QUEEN, KING, ACE
  };

  Suit suit;
  Value value;

  PlayingCard(Suit suit, Value value)
  {
      this->suit = suit;
      this->value = value;
  }
  
};

#endif
