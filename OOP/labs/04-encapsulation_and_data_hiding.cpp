#include <string>
#include <iostream>
#include <list>

class YouTubeChannel{
    //1.
    std::string Name;
    std::string OwnerName;
    static int SubscriberCount;  //2

    public:

    std::list<std::string> PublishedVideoTitles;

    YouTubeChannel(std::string name, std::string ownerName){
        Name = name;
        OwnerName = ownerName;
        SubscriberCount = 0;
    }

    void GetInfo(){
        std::cout << "Name: " << Name << std::endl;
        std::cout << "Owner Name: " << OwnerName << std::endl;
        std::cout << "Number of subscribers: " << SubscriberCount << std::endl;
        std::cout << "Videos: " << Name << std::endl;

        for (std::string videoTitle : PublishedVideoTitles){
            std::cout << videoTitle << std::endl;
        }
    }
    //3 a.
    void Suscribe(){
        SubscriberCount++;
    }

    //3 b.
    void Unsuscribe(){
        if (SubscriberCount > 0)
            SubscriberCount--;
    }

    //c. accessors
    std::string getName() const{
        return Name;
    }
    std::string getOwnerName() const{
        return OwnerName;
    }
    int getSubscriberCount() const{
        return SubscriberCount;
    }
    std::list<std::string> getPublishedVideoTitles() const{
        return PublishedVideoTitles;
    }

    //mutators
    void setName(std::string name){
        Name = name;
    }
    void setOwnerName(std::string ownername){
        OwnerName = ownername;
    }
    void setSubscriberCount(int count){
        SubscriberCount = count;
    }
    void setPublishedVideoTitles(std::list<std::string> videoTitles){
        PublishedVideoTitles = videoTitles;
    }

    //d.
    void PublishVideo(std::string videoTitle){
        PublishedVideoTitles.push_back(videoTitle);
    }

};

int YouTubeChannel::SubscriberCount = 0;  //necessary because of static

int main(void){

    YouTubeChannel ytChannel("GaviviTeaches", "Gavivi");
    ytChannel.PublishVideo("Encapsulation");
    ytChannel.Unsuscribe();
    ytChannel.GetInfo();

    for (int i = 0; i < 20; i++){
        ytChannel.Suscribe();
    }

    ytChannel.GetInfo();
    return 0;
}