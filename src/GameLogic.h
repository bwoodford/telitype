#ifndef GAMELOGIC_H 
#define GAMELOGIC_H


class GameLogic {
public:
  GameLogic();
  ~GameLogic();
  enum class GameEvent {
    CORRECT,
    INCORRECT,
    REVERT
  };

  static void start(char* file);

};
#endif
