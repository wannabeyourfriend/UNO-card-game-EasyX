#include <algorithm>
#include <cstdio>
#include <ctime>
#include "uno_logic.h"

Card::Card(CardColor cardColor, int cardNumber) : cardColor(cardColor), cardNumber(cardNumber) {}

Card::Card(CardType cardType, CardColor cardColor) : cardType(cardType), cardColor(cardColor) {}

Card::Card(CardType cardType) : cardType(cardType) {}

const char *Card::info(bool enableExtraColor) const {
    char *info = new char[20];
    const char *color = cardColor == BLUE ? "BLUE  " : (cardColor == RED ? "RED   " : (cardColor == YELLOW ? "YELLOW" : "GREEN "));
    if (enableExtraColor) {
        if (cardType == WILD) sprintf(info, "| WILD        | %s |   |", color);
        else if (cardType == WILD_DRAW_4) sprintf(info, "| WILD DRAW 4 | %s |   |", color);
        else if (cardType == NUMBER) sprintf(info, "| NUMBER      | %s | %d |", color, cardNumber);
        else if (cardType == SKIP) sprintf(info, "| SKIP        | %s |   |", color);
        else if (cardType == REVERSE) sprintf(info, "| REVERSE     | %s |   |", color);
        else if (cardType == DRAW_2) sprintf(info, "| DRAW 2      | %s |   |", color);
    } else {
        if (cardType == WILD) sprintf(info, "| WILD        |        |   |");
        else if (cardType == WILD_DRAW_4) sprintf(info, "| WILD DRAW 4 |        |   |");
        else if (cardType == NUMBER) sprintf(info, "| NUMBER      | %s | %d |", color, cardNumber);
        else if (cardType == SKIP) sprintf(info, "| SKIP        | %s |   |", color);
        else if (cardType == REVERSE) sprintf(info, "| REVERSE     | %s |   |", color);
        else if (cardType == DRAW_2) sprintf(info, "| DRAW 2      | %s |   |", color);
    }
    return info;
}

CardQueue::CardQueue(int count, Card **cards) {
    if (count == 0) return;
    cardCount = count;
    firstCard = cards[0];
    Card *current = firstCard;
    for (int i = 1; i < count; i++) {
        current->nextCard = cards[i];
        current = current->nextCard;
    }
    current->nextCard = nullptr;
}

bool CardQueue::isEmpty() const {
    return firstCard == nullptr;
}

void CardQueue::addCard(Card *card) {
    cardCount++;
    if (firstCard == nullptr) {
        firstCard = card;
        card->nextCard = nullptr;
    } else {
        Card *current = firstCard;
        while (current->nextCard != nullptr) current = current->nextCard;
        current->nextCard = card;
        card->nextCard = nullptr;
    }
}

Card *CardQueue::takeCard() {
    if (firstCard == nullptr) return nullptr;
    cardCount--;
    Card *remove = firstCard;
    firstCard = remove->nextCard;
    return remove;
}

Card **CardQueue::getCardsArray() const {
    Card **array = new Card *[cardCount];
    Card *current = firstCard;
    for (int i = 0; i < cardCount; i++) {
        array[i] = current;
        current = current->nextCard;
    }
    return array;
}

void CardQueue::println() const {
    printf("Queue cards [%d]:\n", cardCount);
    Card *current = firstCard;
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

Card *AbstractPlayer::getCardAt(int index) const {
    Card *current = firstCard;
    for (int i = 0; i < index; i++) {
        if (current == nullptr) return current;
        current = current->nextCard;
    }
    return current;
}

void AbstractPlayer::grabCard(CardQueue &queue, int count) {
    for (int i = 0; i < count && !queue.isEmpty(); i++) {
        if (firstCard == nullptr) {
            firstCard = queue.takeCard();
            firstCard->nextCard = nullptr;
        } else {
            Card *current = firstCard;
            while (current->nextCard != nullptr) current = current->nextCard;
            Card *take = queue.takeCard();
            current->nextCard = take;
            take->nextCard = nullptr;
        }
        cardCount++;
    }
}

void AbstractPlayer::playCard(CardQueue &queue, int index) {
    if (firstCard == nullptr) return;
    Card *previous = nullptr;
    Card *played = firstCard;
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

bool AbstractPlayer::validateCard(Card *lastCard, int index) const {
    if (index == -1){
        return true;
    }
    if (lastCard == nullptr) {
        if (index >= cardCount) return false;
        return true;
    }
    Card *card = getCardAt(index);
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

Card **AbstractPlayer::getCardsArray() const {
    Card **array = new Card *[cardCount];
    Card *current = firstCard;
    for (int i = 0; i < cardCount; i++) {
        array[i] = current;
        current = current->nextCard;
    }
    return array;
}

void AbstractPlayer::println() const {
    printf("Player cards [%d]:\n", cardCount);
    Card *current = firstCard;
    while (current != nullptr) {
        printf("    %s\n", current->info(false));
        if (current->nextCard == nullptr) break;
        current = current->nextCard;
    }
    printf("\n");
}

void AbstractPlayer::printValid(Card *lastCard) const {
    printf("Your remaining card count: %d\n", cardCount);
    bool cardResult[108];
    for (int i = 0; i < cardCount; i++) cardResult[i] = validateCard(lastCard, i);
    printf("Your cards:\n");
    for (int i = 0; i < cardCount; i++) printf("    %s%d - %s %s\n", i >= 100 ? "" : (i >= 10 ? " " : "  "), i, getCardAt(i)->info(false), cardResult[i] ? "  valid" : "invalid");
    printf("\n");
}

// int AiPlayer::selectCard(Card *lastCard) {
//     for (int i = 0; i < cardCount; i++) if (validateCard(lastCard, i)) return i;
//     return -1;
// }

int AiPlayer::selectCard(Card *lastCard) {
    // 优先出特定牌：DRAW_2, SKIP, REVERSE
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (validateCard(lastCard, i) && (card->cardType == DRAW_2 || card->cardType == SKIP || card->cardType == REVERSE)) {
            return i;
        }
    }

    // 统计每种颜色的牌数量
    int colorCounts[4] = {0};
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (card->cardType == NUMBER) {
            colorCounts[card->cardColor]++;
        }
    }

    // 找到数量最多的颜色
    int maxColor = 0;
    for (int i = 1; i < 4; i++) {
        if (colorCounts[i] > colorCounts[maxColor]) {
            maxColor = i;
        }
    }

    // 优先出数量最多颜色的数字牌
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (validateCard(lastCard, i) && card->cardType == NUMBER && card->cardColor == maxColor) {
            return i;
        }
    }

    // 如果没有数量最多颜色的数字牌，则出其他颜色的数字牌
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (validateCard(lastCard, i) && card->cardType == NUMBER) {
            return i;
        }
    }

    // 最后出WILD或WILD_DRAW_4
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (validateCard(lastCard, i) && (card->cardType == WILD || card->cardType == WILD_DRAW_4)) {
            return i;
        }
    }

    return -1; // 无牌可出
}


// CardColor AiPlayer::selectColor() {
//     int sum[4];
//     for (int i = 0; i < cardCount; i++) sum[getCardAt(i)->cardColor]++;
//     int maxSum = sum[0];
//     int result = 0;
//     for (int i = 1; i < 3; i++)
//         if (sum[i] > maxSum) {
//             maxSum = sum[i];
//             result = i;
//         }
//     return static_cast<CardColor>(result);
// }

CardColor AiPlayer::selectColor() {
    // 选择手中最多的颜色
    int colorCounts[4] = {0};
    for (int i = 0; i < cardCount; i++) {
        Card *card = getCardAt(i);
        if (card->cardType != WILD && card->cardType != WILD_DRAW_4) {
            colorCounts[card->cardColor]++;
        }
    }

    int maxColor = 0;
    for (int i = 1; i < 4; i++) {
        if (colorCounts[i] > colorCounts[maxColor]) {
            maxColor = i;
        }
    }

    return static_cast<CardColor>(maxColor);
}

// int Player::selectCard(Card *lastCard) {
//     printf("Please enter the card index you want to play.\n");
//     int card=0;
//     scanf("%d", &card);
//     printf("endered: %d\n", card);
//     return card;
// }

int Player::selectCard(Card *lastCard) {
    int card;
    while (true) {
        printf("Please enter the card index you want to play.\n");
        scanf("%d", &card);
        if (validateCard(lastCard, card)) {
            break;
        } else {
            printf("Invalid card selection. Please choose a valid card.\n");
        }
    }
    printf("Entered: %d\n", card);
    return card;
}


CardColor Player::selectColor() {
    printf("Please enter the color you want to choose.\n");
    printf("    0 - BLUE\n");
    printf("    1 - RED\n");
    printf("    2 - YELLOW\n");
    printf("    3 - GREEN\n");
    int color;
    do { scanf("%d", &color); } while (color < 0 || color > 3);
    return static_cast<CardColor>(color);
}

Application::Application(int playerCount) {
    aiPlayerCount = playerCount > 8 ? 7 : playerCount - 1;
    player = new Player();
    aiPlayers = new AiPlayer *[aiPlayerCount];
    for (int i = 0; i < aiPlayerCount; i++) aiPlayers[i] = new AiPlayer();

    allPlayers = new AbstractPlayer *[aiPlayerCount + 1];
    allPlayers[0] = player;
    for (int i = 0; i < aiPlayerCount; i++) allPlayers[i + 1] = aiPlayers[i];

    Card **cards = defaultCards();
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
            printf("Game over!");
            break;
        }

        bool skip = false;
        int selected = allPlayers[currentPlayer]->selectCard(lastCard);
        if (selected < 0) {
            allPlayers[currentPlayer]->grabCard(queue, 1);
            // Modification starts here
            printf("Player %d draws a card.\n", currentPlayer);
            // Modification ends here
        } else {
            Card *selectedCard = allPlayers[currentPlayer]->getCardAt(selected);
            allPlayers[currentPlayer]->playCard(queue, selected);
            lastCard = selectedCard;
            // Modification starts here
            printf("Player %d plays: %s\n", currentPlayer, selectedCard->info(true));
            // Modification ends here

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

Card **Application::defaultCards() {
    Card **cards = new Card *[108];
    cards[0] = new Card(CardColor::BLUE, 0);
    cards[1] = new Card(CardColor::RED, 0);
    cards[2] = new Card(CardColor::YELLOW, 0);
    cards[3] = new Card(CardColor::GREEN, 0);

    for (int i = 0; i < 9; i++) {
        cards[4 + i * 8] = new Card(CardColor::BLUE, i + 1);
        cards[5 + i * 8] = new Card(CardColor::BLUE, i + 1);
        cards[6 + i * 8] = new Card(CardColor::RED, i + 1);
        cards[7 + i * 8] = new Card(CardColor::RED, i + 1);
        cards[8 + i * 8] = new Card(CardColor::YELLOW, i + 1);
        cards[9 + i * 8] = new Card(CardColor::YELLOW, i + 1);
        cards[10 + i * 8] = new Card(CardColor::GREEN, i + 1);
        cards[11 + i * 8] = new Card(CardColor::GREEN, i + 1);
    }

    for (int i = 0; i < 2; i++) {
        cards[76 + i] = new Card(CardType::SKIP, CardColor::BLUE);
        cards[78 + i] = new Card(CardType::SKIP, CardColor::RED);
        cards[80 + i] = new Card(CardType::SKIP, CardColor::YELLOW);
        cards[82 + i] = new Card(CardType::SKIP, CardColor::GREEN);

        cards[84 + i] = new Card(CardType::REVERSE, CardColor::BLUE);
        cards[86 + i] = new Card(CardType::REVERSE, CardColor::RED);
        cards[88 + i] = new Card(CardType::REVERSE, CardColor::YELLOW);
        cards[90 + i] = new Card(CardType::REVERSE, CardColor::GREEN);

        cards[92 + i] = new Card(CardType::DRAW_2, CardColor::BLUE);
        cards[94 + i] = new Card(CardType::DRAW_2, CardColor::RED);
        cards[96 + i] = new Card(CardType::DRAW_2, CardColor::YELLOW);
        cards[98 + i] = new Card(CardType::DRAW_2, CardColor::GREEN);
    }

    for (int i = 0; i < 4; i++) {
        cards[100 + i] = new Card(CardType::WILD);
        cards[104 + i] = new Card(CardType::WILD_DRAW_4);
    }

    return cards;
}

void Application::shuffle(int count, Card **cards) {
    srand(time(nullptr));
    for (int i = 0; i < count - 1; i++) {
        int change = (rand() % (count - i)) + i;
        if (i != change) std::swap(cards[i], cards[change]);
    }
}

void Application::printGameInfo() const {
    printf("------------------------------------------------------------\n");
    for (int i = 0; i < aiPlayerCount; i++) {
        if (aiPlayers[i]->finished()) printf("Player %d has won!\n", i + 1);
        else printf("Player %d remaining card count: %d\n", i + 1, aiPlayers[i]->cardCount);
    }
    printf("\n");
    player->printValid(lastCard);
    if (lastCard != nullptr) printf("Last:     %s\n", lastCard->info(true));
}