#pragma once
#include <string>
#include "ddserver/Uncopyable.h"
class IPaddr{


    std::string 
};


class RULE:Uncopyable{
public:
    static RULE & GetRULE()
    {
        if(instance.header.empty()) SetHeader("%");
        if(instance.seperator.empty()) SetSep("#");
        return instance;
    }
public:
    static std::string GetHeader() {
        return header;
    }

    static std::string GetSep(){
        return seperator;
    }
private:
    static void SetHeader(std::string header_)
    {
        header=header_;
    }
    static void SetSep(std::string sep_)
    {
        seperator=sep_;
    }
private:
    RULE();
    static RULE instance;
    static std::string header;
    static std::string seperator;
};


class Packet
{
public:
    Packet(std::string header_="%",std::string content_="default content",std::string sep_="$"):
    header(header_),content(content_),seperator(sep_) {  }
    ~Packet(){}
    
    std::string GetHeader() const;
    std::string GetContent() const;
    std::string GetSep() const;

    void SetHeader(const std::string & header_)
    {
        header=header_;
    }
    void SetContent(const std::string & content_)
    {
        content=content_;
    }
    void SetSep(const std::string & sep_)
    {
        seperator=sep_;
    }
private:
    std::string header;
    std::string content;
    std::string seperator;
};

