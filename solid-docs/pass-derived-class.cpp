#include <bits/stdc++.h>
using namespace std;

struct user {
    string email;
    string phone;
    string user;
};

class Send{
public:
    virtual void send(const user& u, const string& content) = 0;
};

class emailService : public Send {
public:    
    void send(const user& u, const string& content) {
        cout << "[SMTP] Sending invoice to " << u.email << "...\n";
    }
};

class messageService : public Send {
public:    
    void send(const user& u, const string& content) {
        cout << "[LOG] Sending message to " << u.phone << ": " << content << "\n";
    }
};

class notificationService {
private:
    emailService emailSvc;
    messageService messageSvc;
public:
    // Always send interface. (Send) Instead of (emailService) , (messageSvc)
   void sendNotification(Send& Send, const user& u, const string& content) {
        Send.send(u, content);
    }
};

int main(){
    notificationService notif;
    emailService emailSvc;
    messageService messageSvc;
    user u{"naveen@example.com", "1234567890", "Alice"};
    notif.sendNotification(emailSvc, u, "Welcome to our service! Email sent.");
    notif.sendNotification(messageSvc, u, "Welcome to our service! Message sent.");
    return 0;
}
 