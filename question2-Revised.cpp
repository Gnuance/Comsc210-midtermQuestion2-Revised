/*  Midterm 1: Question 2
    Requirements:
        1. Simulate a line at a coffee shop. Your simulation should run for 20 time periods (minutes) and display the current line at the coffee shop.
        2. When the store opens (i.e. in first time period), add 5 customers to the line right away.
        3. In subsequent time periods, the probability of:
            - A customer being helped at the beginning of the line and ordering their coffee is 40%
            - A new customer joining the end of the line is 60%
            - The customer at the end of the line deciding they don't want to wait and leaving is 20%
            - Any particular customer can decide they don't want to wait and leave the line: 10%
            - A VIP (very important person) customer with a Coffee House Gold Card gets to skip the line and go straight to the counter and order: 10%

        4. Use random names from this list for your customer names: names.txt
        5. For each minute of your simulation, output the resulting line after all operations for that time period are complete.
        6. In any particular simulation time period, there could be multiple operations happening at once,
            depending on how the probabilities work out for that time period.
*/

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList
{
private:
    struct Node
    {
        string name;
        Node *prev;
        Node *next;
        Node(string val, Node *p = nullptr, Node *n = nullptr)
        {
            name = val;
            prev = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;

public:
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    string getHeadName()
    {
        return head->name;
    }

    string getTailName()
    {
        return tail->name;
    }

    string getIndexName(int index) {
        Node* current = head;
        for (size_t i = 0; i < index && current; i++)
        {
            current->next;
        }
        if (current)
        {
            return current->name;
        }  
        return "";
    }

    // Returns size of list
    int getSize()
    {
        unsigned int count = 0;
        Node *temp = head;
        while (temp)
        {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void insert_after(string value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(string value)
    {
        if (!head)
            return;

        Node *temp = head;

        while (temp && temp->name != value)
            temp = temp->next;

        if (!temp)
            return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos)
    {
        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1)
        {
            pop_front();
            return;
        }

        Node *temp = head;

        for (int i = 1; i < pos; i++)
        {
            if (!temp)
            {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp)
        {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next)
        {
            pop_back();
            return;
        }

        Node *tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(string v)
    {
        Node *newNode = new Node(v);
        if (!tail)
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(string v)
    {
        Node *newNode = new Node(v);
        if (!head)
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front()
    {

        if (!head)
        {
            cout << "List is empty." << endl;
            return;
        }

        Node *temp = head;

        if (head->next)
        {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back()
    {
        if (!tail)
        {
            cout << "List is empty." << endl;
            return;
        }
        Node *temp = tail;

        if (tail->prev)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print()
    {
        int count = 0;
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            if (count > 0)
                cout << ", ";
            cout << current->name;
            current = current->next;
            count++;
        }
        cout << endl;
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            cout << current->name << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void printVertical()
    {
        int count = 0;
        Node *current = head;
        if (!current)
        {
            cout << "List is empty." << endl;
            return;
        }
        while (current)
        {
            if (count > 0)
                cout << endl;
            cout << "\t" << current->name;
            current = current->next;
            count++;
        }
        cout << endl;
    }
};

bool FrontCustomerHelped();
bool NewCustomerJoinsLine();
bool CustomerEndOfLineLeaves();
bool AnyCustomerLeaves();
bool VipStraightToFront();
unsigned long RandCustomerInt();

int main()
{
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
    vector<string> names = {};
    string fileLine = "";
    DoublyLinkedList coffeeLine;
    string name = "";
    int nameIndex = 0;

    // Add names to vector
    ifstream inputFile("names.txt");
    if (!inputFile)
    {
        cerr << "Unable to open file." << endl;
        return 1;
    }

    while (getline(inputFile, fileLine))
    {
        names.push_back(fileLine);
    }
    inputFile.close();
    // Names are now in vector

    // Start line
    cout << "Store opens:" << endl;
    for (int i = 0; i < 5; i++)
    {
        name = names.at(RandCustomerInt());
        coffeeLine.push_back(name);
        cout << "\t" << name << " joins the line" << endl;
    }

    cout << "Resulting list: ";
    coffeeLine.print();

    // For time step 2 and beyond
    for (int i = 2; i <= 20; i++)
    {
        cout << endl << "Time step #" << i << endl;
        if (FrontCustomerHelped())
        {
            cout << "\t" << coffeeLine.getHeadName() << " is served" << endl;
            coffeeLine.pop_front();
        }
        if (NewCustomerJoinsLine())
        {
            name = names.at(RandCustomerInt());
            cout << "\t" << name << " joined the line" << endl;
            coffeeLine.push_back(name);
        }
        if (CustomerEndOfLineLeaves())
        {
            cout << "\t" << coffeeLine.getTailName() << " (at the rear) left the line" << endl;
            coffeeLine.pop_back();
        }
        // This is the loop to check if any particular customer wants to leave.
        for (int j = 1; j < coffeeLine.getSize(); j++)
        {
            if (AnyCustomerLeaves())
            {
                cout << "\t" << coffeeLine.getIndexName(j) << " left the line" << endl;
                coffeeLine.delete_pos(j);
            }
        }
        if (VipStraightToFront())
        {
            name = names.at(RandCustomerInt());
            cout << "\t" << name << " (VIP) joins the front of the line" << endl;
            coffeeLine.push_front(name);
        }
        cout << "Resulting line: " << endl;
        coffeeLine.printVertical();
    }

    return 0;
}

bool FrontCustomerHelped()
{
    return ((rand() % 100) + 1) <= 40;
}
bool NewCustomerJoinsLine()
{
    return ((rand() % 100) + 1) <= 60;
}
bool CustomerEndOfLineLeaves()
{
    return ((rand() % 100) + 1) <= 20;
}
bool AnyCustomerLeaves()
{
    return ((rand() % 100) + 1) <= 10;
}
bool VipStraightToFront()
{
    return ((rand() % 100) + 1) <= 10;
}
unsigned long RandCustomerInt()
{
    return (rand() % 99) + 1;
}