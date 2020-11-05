#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

struct Node
{
    Node* next;
    string cardRank;
    string cardType;
};

class LinkedList
{
private:
    int length;
    int totalValue;
    Node *head, *tail;

    int sumCardValue(int value) const{
        if(value <= 10)
            return value;
        else if(value < 14)
            return 10;
        else{
            if(this->totalValue + 11 <= 21) return 11;
            else return 1;
        }
    };
public:
    LinkedList(){
        this->length = 0;
        this->totalValue = 0;
        this->head = nullptr;
        this->tail = nullptr;
    }

    void add(int value, string type, string rank)
    {
        Node *tmp = new Node();
        tmp->cardType = type;
        tmp->cardRank = rank;

        if(head == nullptr)
        {
            head = tmp;
            tail = tmp;
        }
        else
        {
            tail->next = tmp;
            tail = tail->next;
        }

        this->totalValue += sumCardValue(value);
        this->length++;
    }

    int getTotal() const{
        return this->totalValue;
    };

    void print(){
        Node* temp = this->head;
        for(int i = 0; i < length; i++){
            cout << temp->cardType << " " << temp->cardRank << endl;
            temp = temp->next;
        }
        cout << "Total: " << totalValue << endl;
        delete temp;
    }

    void printCensored(){
        Node* temp = this->head->next;

        cout << "???" << endl;
        for(int i = 0; i < length-1; i++){
            cout << temp->cardType << " " << temp->cardRank << endl;
            temp = temp->next;
        }

        delete temp;
    }

    void clear(){

        head = nullptr;
        tail = nullptr;
        totalValue = 0;
        length = 0;
    }
};

class Table{
private:

    LinkedList *playerCards = new LinkedList();
    LinkedList *dealerCards = new LinkedList();

    static int getRandom(int minValue, int maxValue){
        return (rand()%(maxValue - minValue + 1) + minValue);
    }

    static string defCardType(int type){
        switch (type) {
            case 0:
                return "Sinek";
            case 1:
                return "Karo";
            case 2:
                return "Maca";
            case 3:
                return "Kupa";
            default:
                return "error";
        }
    }

    static string defCardRank(int value){
        if(value <= 10)
            return to_string(value);
        else{
            switch (value) {
                case 11:
                    return "J";
                case 12:
                    return "Q";
                case 13:
                    return "K";
                case 14:
                    return "A";
                default:
                    return "error";
            }
        }
    }


    void hitDealer(){
        cout << "-- DEALER'S TURN --\n";

        bool wannaStand = false;
        while(!wannaStand){
            print();
            if(dealerCards->getTotal() < playerCards->getTotal() && dealerCards->getTotal() < 17 && playerCards->getTotal() <= 21){
                hit(dealerCards);
            }
            else wannaStand = true;
        }
    }

    void hitOrStand(){
        bool wannaStand = false;
        char hitOrStand;
        do{
            printCensored();
            cout << "Hit(h) or Stand(s):";
            cin >> hitOrStand;
            cout << "\n";
            if(hitOrStand == 'h') hit(playerCards);
            else wannaStand = true;
        }while(!wannaStand && playerCards->getTotal() <= 21);
        printCensored();
    }

    static void hit(LinkedList *cards) {
        int randValue = getRandom(2, 14);
        string randType = defCardType(getRandom(0, 3));
        string randRank = defCardRank(randValue);
        cards->add(randValue, randType, randRank);
    }

    void revealWinner(){
        if(playerCards->getTotal() > 21) cout << "\n*** YOU LOST! ***\n";
        else if(playerCards->getTotal() < dealerCards->getTotal() && dealerCards->getTotal() <= 21) cout << "\n*** YOU LOST! ***\n";
        else if(playerCards->getTotal() == dealerCards->getTotal()) cout << "\n*** DRAW! ***\n";
        else cout << "\n*** YOU WON! ***\n";
    }

    void printCensored(){
        cout << "Dealer's Hand:\n";
        dealerCards->printCensored();
        cout << "\nYour Hand:\n";
        playerCards->print();
        cout << "\n";
    }

    void print(){
        cout << "Dealer's Hand:\n";
        dealerCards->print();
        cout << "\nYour Hand:\n";
        playerCards->print();
        cout << "\n";
    }

    void clearTable(){
        playerCards->clear();
        dealerCards->clear();
    }
public:
    void startGame(){
            hit(dealerCards);
            hit(playerCards);
            hit(dealerCards);
            hit(playerCards);

            hitOrStand();
            hitDealer();
            revealWinner();
    }
};

int main() {
    srand(time(nullptr));

    bool wannaPlayAgain = true;
    char yesOrNo;

    do {
        Table table;
        table.startGame();

        cout << "Wanna play again? y/n: ";
        cin >> yesOrNo;
        if(yesOrNo == 'n') wannaPlayAgain = false;

    }while(wannaPlayAgain);

    return 0;
}