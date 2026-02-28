/*
    Request is made as an Object
    You -> Client
    Remote / Button -> Invoker Layers
    Command -> TurnOnTV
    Receiver -> TV

    Client -> Invoker -> Command -> Receiver
        Invoker doesn't know about the Receiver, it only knows about the Command interface
        Command object knows about the Receiver and invokes the appropriate action on the Receiver
*/

#include <bits/stdc++.h>
using namespace std;

class CommandInterface{
    public:
        virtual void execute() = 0;
};

class TVReceiver{
    public:
        void turnOn(){
            cout<<"TV is turned ON"<<endl;
        }
        void turnOff(){
            cout<<"TV is turned OFF"<<endl;
        }
};

class TurnOnCommand : public CommandInterface{
    private:
        TVReceiver* tv;
    public:
        TurnOnCommand(TVReceiver* _tv) : tv(_tv) {}
        void execute(){
            tv->turnOn();
        }
};

class TurnOffCommand : public CommandInterface{
    private:
        TVReceiver* tv;
    public:
        TurnOffCommand(TVReceiver* _tv) : tv(_tv) {}
        void execute(){
            tv->turnOff();
        }
};

class CommandInvoker{
    private:
        CommandInterface* command;
    public:
        void setCommand(CommandInterface* _command){
            command = _command;
        }
        void pressButton(){
            command->execute();
        }
};

int main(){
    TVReceiver tv;
    CommandInvoker invoker;

    CommandInterface* turnOnCommand = new TurnOnCommand(&tv);
    CommandInterface* turnOffCommand = new TurnOffCommand(&tv);

    invoker.setCommand(turnOnCommand);
    invoker.pressButton();

    invoker.setCommand(turnOffCommand);
    invoker.pressButton();

    delete turnOnCommand;
    delete turnOffCommand;

    return 0;
}