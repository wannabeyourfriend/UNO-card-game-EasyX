#ifndef UNO_LOGIC_H
#define UNO_LOGIC_H

enum CardType {
    NUMBER = 0,
    SKIP = 1,
    REVERSE = 2,
    DRAW_2 = 3,
    WILD = 4,
    WILD_DRAW_4 = 5
};

enum CardColor {
    red = 0,
    green = 1,
    blue = 2,
    yellow  = 3
};

//卡牌对象
struct Card {
    //卡牌的牌面信息
    CardType cardType = NUMBER;
    CardColor cardColor = blue ;
    int cardNumber = 0;

    //卡牌的编号，用于到UI卡牌图像的显示映射关系
    int card_id = 0;

    //自引，指向下一张卡牌
    Card* nextCard = nullptr;

    explicit Card(CardColor cardColor, int cardNumber, int card_id);

    explicit Card(CardType cardType, CardColor cardColor, int card_id);

    explicit Card(CardType cardType, int card_id);

    //是否需要另外的颜色选择
    const char* info(bool enableExtraColor) const;
};

struct CardQueue {
    int cardCount = 0;
    Card* firstCard = nullptr;

    explicit CardQueue(int count, Card** cards);

    bool isEmpty() const;

    void addCard(Card* card);

    Card* takeCard();

    Card** getCardsArray() const;//利用数组指针返回所有卡牌

    void println() const;
};

struct AbstractPlayer {
    int cardCount = 0;
    Card* firstCard = nullptr;

    virtual int selectCard(Card* lastCard) = 0;

    virtual CardColor selectColor() = 0;

    bool finished() const;

    Card* getCardAt(int index) const;

    void grabCard(CardQueue& queue, int count);

    void playCard(CardQueue& queue, int index);

    bool validateCard(Card* lastCard, int index) const;

    Card** getCardsArray() const;//利用数组指针返回所有卡牌

    void println() const;

    void printValid(Card* lastCard) const;
};

struct AiPlayer : AbstractPlayer {
    int selectCard(Card* lastCard) override;

    CardColor selectColor() override;
};

struct Player : AbstractPlayer {
    int selectCard(Card* lastCard) override;

    CardColor selectColor() override;
};

struct Application {
    int aiPlayerCount;
    Player* player;
    AiPlayer** aiPlayers;
    CardQueue queue = CardQueue(0, nullptr);

    int currentPlayer = 0;
    AbstractPlayer** allPlayers;
    Card* lastCard = nullptr;
    bool reversed = false;

    explicit Application(int playerCount);

    void gameLoop();

    int nextPlayer(bool skip) const;

    int defaultCardCount();

    Card** defaultCards();

    void shuffle(int count, Card** cards);

    void printGameInfo() const;
};

#endif // UNO_LOGIC_H

