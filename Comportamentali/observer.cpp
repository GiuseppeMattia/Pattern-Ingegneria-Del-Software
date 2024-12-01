#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    Si vuole creare un' applicazione che implementi una chat di gruppo
    usando il pattern dell'Osservatore (Observer)
*/

/*
    Observer
*/

class User{
    public:
        virtual string getName() const = 0;
        virtual void update(const string& s, const User* u) const = 0;
        virtual void send(const string& s) const = 0;
};

/*
    Osservatore concreto
*/

class ChatUser: public User{
    private:
        string name;
    public:
        ChatUser(string s): name(s) {}

        string getName() const override{
            return name;
        }

        void update(const string& s, const User* u) const override{
            cout<<"L'utente "<<name<<" ha ricevuto un messaggio dall'utente "<<u->getName()<<": "<<s<<endl;
        }

        void send(const string& s) const override{
            cout<<"L'utente "<<name<<" ha inviato un messaggio: "<<s<<endl;
        }
};


/*
    Soggetto
*/

class Group{
    public:
        virtual void addUser(User* u) = 0;
        virtual void removeUser(User* u) = 0;
        virtual void notify(const string& s, const User* u) const = 0;
};

/*
    Soggetto concreto
*/

class GroupChat: public Group{
    private:
        vector<User*> chat;
    public:
        void addUser(User* u) override{
            chat.push_back(u);
        }

        void removeUser(User* u) override{
            for(auto it = chat.begin(); it != chat.end(); it++)
                if(*it == u){
                    chat.erase(it);
                    cout<<"Rimosso l'utente "<<u->getName()<<endl;
                    return;
                }
            cout<<"Utente "<<u->getName()<<" non presente nel gruppo"<<endl;
        }

        void notify(const string& s, const User* us) const override{
            us->send(s);

            for(User* u: chat)
                if(u != us)
                    u->update(s, us);
        }
};

int main(){
    GroupChat* groupChat = new GroupChat();

    ChatUser* user1 = new ChatUser("Tonino");
    ChatUser* user2 = new ChatUser("Duviggi");
    ChatUser* user3 = new ChatUser("Franco");
    ChatUser* phantomUser = new ChatUser("Cenzino");

    groupChat->addUser(user1);
    groupChat->addUser(user2);
    groupChat->addUser(user3);

    groupChat->notify("Buongiorno", user1);
    groupChat->notify("Buongiorno a te", user3);

    groupChat->removeUser(user2);
    groupChat->removeUser(phantomUser);

    delete phantomUser;
    delete user3;
    delete user2;
    delete user1;
    delete groupChat;
    return 0;
}