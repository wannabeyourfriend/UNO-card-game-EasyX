#include <algorithm>
#include <cstdio>
#include <ctime>
#include <windows.h>
#include "uno_logic.h"
#include "visualize.h"


//卡牌类Card三种牌型的构造函数
Card::Card(CardColor cardColor, int cardNumber, int card_id) : cardColor(cardColor), cardNumber(cardNumber) , card_id(card_id){}

Card::Card(CardType cardType, CardColor cardColor, int card_id) : cardType(cardType), cardColor(cardColor) , card_id(card_id){}

Card::Card(CardType cardType, int card_id) : cardType(cardType) , card_id(card_id) {}


//卡牌类Card的info函数
const char* Card::info(bool enableExtraColor) const {
    char* info = new char[20];
    const char* color = cardColor == blue ? "blue  " : (cardColor == red ? "red   " : (cardColor == yellow ? "yellow" : "green "));
    if (enableExtraColor) {
        if (cardType == WILD) sprintf(info, "| WILD        | %s |   |", color);
        else if (cardType == WILD_DRAW_4) sprintf(info, "| WILD DRAW 4 | %s |   |", color);
        else if (cardType == NUMBER) sprintf(info, "| NUMBER      | %s | %d |", color, cardNumber);
        else if (cardType == SKIP) sprintf(info, "| SKIP        | %s |   |", color);
        else if (cardType == REVERSE) sprintf(info, "| REVERSE     | %s |   |", color);
        else if (cardType == DRAW_2) sprintf(info, "| DRAW 2      | %s |   |", color);
    }
    else {
        if (cardType == WILD) sprintf(info, "| WILD        |        |   |");
        else if (cardType == WILD_DRAW_4) sprintf(info, "| WILD DRAW 4 |        |   |");
        else if (cardType == NUMBER) sprintf(info, "| NUMBER      | %s | %d |", color, cardNumber);
        else if (cardType == SKIP) sprintf(info, "| SKIP        | %s |   |", color);
        else if (cardType == REVERSE) sprintf(info, "| REVERSE     | %s |   |", color);
        else if (cardType == DRAW_2) sprintf(info, "| DRAW 2      | %s |   |", color);
    }
    return info;
}

CardQueue::CardQueue(int count, Card** cards) {
    if (count == 0) return;
    cardCount = count;
    firstCard = cards[0];
    Card* current = firstCard;
    for (int i = 1; i < count; i++) {
        current->nextCard = cards[i];
        current = current->nextCard;
    }
    current->nextCard = nullptr;
}

bool CardQueue::isEmpty() const {
    return firstCard == nullptr;
}

void CardQueue::addCard(Card* card) {
    cardCount++;
    if (firstCard == nullptr) {
        firstCard = card;
        card->nextCard = nullptr;
    }
    else {
        Card* current = firstCard;
        while (current->nextCard != nullptr) current = current->nextCard;
        current->nextCard = card;
        card->nextCard = nullptr;
    }
}

Card* CardQueue::takeCard() {
    if (firstCard == nullptr) return nullptr;
    cardCount--;
    Card* remove = firstCard;
    firstCard = remove->nextCard;
    return remove;
}

Card** CardQueue::getCardsArray() const {
    Card** array = new Card * [cardCount];
    Card* current = firstCard;
    for (int i = 0; i < cardCount; i++) {
        array[i] = current;
        current = current->nextCard;
    }
    return array;
}

void CardQueue::println() const {
    printf("Queue cards [%d]:\n", cardCount);
    Card* current = firstCard;
    while (current != nullptr) {
        printf("    %s\n", current->info(false));
        if (current->nextCard == nullptr) break;
        current = current->nextCard;
    }
    printf("\n");
}

bool AbstractPlayer::finished() const {
    return cardCount == 0;
}

Card* AbstractPlayer::getCardAt(int index) const {
    Card* current = firstCard;
    for (int i = 0; i < index; i++) {
        if (current == nullptr) return current;
        current = current->nextCard;
    }
    return current;
}

void AbstractPlayer::grabCard(CardQueue& queue, int count) {
    for (int i = 0; i < count && !queue.isEmpty(); i++) {
        if (firstCard == nullptr) {
            firstCard = queue.takeCard();
            firstCard->nextCard = nullptr;
        }
        else {
            Card* current = firstCard;
            while (current->nextCard != nullptr) current = current->nextCard;
            Card* take = queue.takeCard();
            current->nextCard = take;
            take->nextCard = nullptr;
        }
        cardCount++;
    }
}

void AbstractPlayer::playCard(CardQueue& queue, int index) {
    if (firstCard == nullptr) return;
    Card* previous = nullptr;
    Card* played = firstCard;
    for (int i = 0; i < index; i++) {
        if (played->nextCard == nullptr) break;
        previous = played;
        played = played->nextCard;
    }
    if (previous != nullptr) previous->nextCard = played->nextCard;
    else firstCard = firstCard->nextCard;
    cardCount--;
    queue.addCard(played);
}

bool AbstractPlayer::validateCard(Card* lastCard, int index) const {
    if (lastCard == nullptr) {
        if (index >= cardCount) return false;
        return true;
    }
    Card* card = getCardAt(index);
    switch (card->cardType) {
    case NUMBER:
        return card->cardColor == lastCard->cardColor || (lastCard->cardType == NUMBER && card->cardNumber == lastCard->cardNumber);
    case SKIP:
    case REVERSE:
    case DRAW_2:
        return card->cardColor == lastCard->cardColor;
    case WILD:
    case WILD_DRAW_4:
        return true;
    }
    return false;
}

Card** AbstractPlayer::getCardsArray() const {
    Card** array = new Card * [cardCount];
    Card* current = firstCard;
    for (int i = 0; i < cardCount; i++) {
        array[i] = current;
        current = current->nextCard;
    }
    return array;
}

void AbstractPlayer::println() const {
    printf("Player cards [%d]:\n", cardCount);
    Card* current = firstCard;
    while (current != nullptr) {
        printf("    %s\n", current->info(false));
        if (current->nextCard == nullptr) break;
        current = current->nextCard;
    }
    printf("\n");
}

void AbstractPlayer::printValid(Card* lastCard) const {
    printf("Your remaining card count: %d\n", cardCount);
    bool cardResult[108] = { false };
    for (int i = 0; i < cardCount; i++) cardResult[i] = validateCard(lastCard, i);
    printf("Your cards:\n");
    for (int i = 0; i < cardCount; i++) {
        printf("    %s%d - %s %s\n", i >= 100 ? "" : (i >= 10 ? " " : "  "), i, getCardAt(i)->info(false), cardResult[i] ? "  valid" : "invalid"); 
        Sleep(100);
    }
    printf("\n");

    // Card** temp = (Card**)malloc(cardCount * sizeof(Card*));

    Card* temp[120];
    bool result[120];
     for (int i = 0; i < cardCount; i++){
         temp[i] = getCardAt(i);
         result[i] = cardResult[i];
     }
    // printf("%d\n", 80);
     show_hand_cards(temp, result, cardCount);
     //printf("%d\n", 90);
    // printf("%d\n", 100);
}

int AiPlayer::selectCard(Card* lastCard) {
    for (int i = 0; i < cardCount; i++) if (validateCard(lastCard, i)) return i;
    return -1;
}

//这段AI出牌的逻辑可以重写
CardColor AiPlayer::selectColor() {
    int sum[4] = { 0, 0, 0, 0 };
    for (int i = 0; i < cardCount; i++) sum[getCardAt(i)->cardColor]++;
    int maxSum = sum[0];
    int result = 0;
    for (int i = 1; i < 3; i++)
        if (sum[i] > maxSum) {
            maxSum = sum[i];
            result = i;
        }
    return static_cast<CardColor>(result);
}

int Player::selectCard(Card* lastCard) {
    printf("Please select the card you want to play.\n");
    //int card = select_card_visualize();//利用UI函数来选择卡牌
    int card = 0;
    card = select_card_screen();
    //scanf_s("%d", &card);//输入选择的卡牌,
    printf("entered: %d\n", card);
    return card; /*>= cardCount ? cardCount - 1 : card < 0 ? -1 : card;*/
}

CardColor Player::selectColor() {
    printf("Please enter the color you want to choose.\n");
    printf("    0 - red\n");
    printf("    1 - green\n");
    printf("    2 - blue\n");
    printf("    3 - yellow\n");
    //int color = select_color_visualize();//当UI函数，打出WILD牌或WILD_DRAW_4牌时，需要选择颜色
    int color = 0;
    color = select_color_visualize();
    /*do { scanf_s("%d", &color); } while (color < 0 || color > 3);*/
    return static_cast<CardColor>(color);
}

Application::Application(int playerCount) {
    aiPlayerCount = playerCount > 8 ? 7 : playerCount - 1;
    player = new Player();
    aiPlayers = new AiPlayer * [aiPlayerCount];
    for (int i = 0; i < aiPlayerCount; i++) aiPlayers[i] = new AiPlayer();

    allPlayers = new AbstractPlayer * [aiPlayerCount + 1];
    allPlayers[0] = player;
    for (int i = 0; i < aiPlayerCount; i++) allPlayers[i + 1] = aiPlayers[i];

    Card** cards = defaultCards();
    shuffle(defaultCardCount(), cards);
    queue = CardQueue(defaultCardCount(), cards);
}

void Application::gameLoop() {
    player->grabCard(queue, 7);
    for (int i = 0; i < aiPlayerCount; i++) aiPlayers[i]->grabCard(queue, 7);

    while (true) {
        if (currentPlayer == 0) printGameInfo();

        bool end = true;
        for (int i = 0; i < aiPlayerCount; i++)
            if (!aiPlayers[i]->finished()) {
                end = false;
                break;
            }
        if (end) {
            printf("Game over!");//游戏结束,这里可以用一个UL界面来显示游戏结果
            break;
        }

        bool skip = false;
        int selected = allPlayers[currentPlayer]->selectCard(lastCard);
        if (selected < 0) {
            allPlayers[currentPlayer]->grabCard(queue, 1);
        }
        else {
            Card* selectedCard = allPlayers[currentPlayer]->getCardAt(selected);
            allPlayers[currentPlayer]->playCard(queue, selected);
            lastCard = selectedCard;

            if (currentPlayer == 0 && player->finished()) {
                printf("You won!");
                break;
            }

            switch (selectedCard->cardType) {
            case NUMBER:
                break;
            case SKIP:
                skip = true;
                break;
            case REVERSE:
                reversed = !reversed;
                break;
            case DRAW_2:
                allPlayers[nextPlayer(false)]->grabCard(queue, 2);
                break;
            case WILD:
                lastCard->cardColor = allPlayers[currentPlayer]->selectColor();
                break;
            case WILD_DRAW_4:
                lastCard->cardColor = allPlayers[currentPlayer]->selectColor();
                allPlayers[nextPlayer(false)]->grabCard(queue, 4);
                break;
            }
        }
        currentPlayer = nextPlayer(skip);
    }
}

int Application::nextPlayer(bool skip) const {
    int move = skip ? 2 : 1;
    int current = currentPlayer;
    while (move > 0) {
        current += (reversed ? -1 : 1);
        if (current < 0) current += (aiPlayerCount + 1);
        current %= (aiPlayerCount + 1);
        if (!allPlayers[current]->finished()) move--;
    }
    return current;
}

int Application::defaultCardCount() {
    return 108;
}

Card** Application::defaultCards() {
    Card** cards = new Card * [108];
    int i, j, k;
    //初始化数字卡牌
    for (i = 0; i < 4; i++) {//4种颜色
        for (j = 0; j < 10; j++) {//10张数字牌
            for (k = 0; k < 2; k++) {//每一种都有两个
                cards[i * 20 + j * 2 + k] = new Card(CardColor(i), j, i * 20 + j * 2 + k);
            }
        }
    }
    //初始化技能牌SKIP/REVERSE/DRAW_2
    for (i = 0; i < 4; i++) { // 最外层的逻辑，循环四种颜色
        for (j = 0; j < 3; j++) { // 三种卡牌技能
            for (k = 0; k < 2; k++) { // 每张牌有两张
                cards[80 + i * 6 + j * 2 + k] = new Card(CardType(j + 1), CardColor(i), 80 + i * 6 + j * 2 + k);
            }
        }
    }
    //初始化WILD/WILD_DRAW_4,每个都有两张
    for (int i = 0; i < 2; i++) {
        cards[104 + i] = new Card(CardType::WILD, 104+ i);
        cards[106 + i] = new Card(CardType::WILD_DRAW_4, 106 + i);
    }


    return cards;
}

void Application::shuffle(int count, Card** cards) {
    srand(time(nullptr));
    for (int i = 0; i < count - 1; i++) {
        int change = (rand() % (count - i)) + i;
        if (i != change) std::swap(cards[i], cards[change]);
    }
}

void Application::printGameInfo() const {
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < aiPlayerCount; i++) {
        if (aiPlayers[i]->finished()) printf("Player %d has won!\n", i + 1);//可以UI显示游戏结果
        else {
            printf("Player %d remaining card count: %d\n", i + 1, aiPlayers[i]->cardCount);//可以UI显示剩余卡牌数量
            show_players(aiPlayerCount);
        }
    }
    printf("\n");
    player->printValid(lastCard);
    if (lastCard != nullptr) {
        printf("Last:     %s\n", lastCard->info(true));//这里用UI显示上一手牌
        show_last_card(lastCard);
    }
}