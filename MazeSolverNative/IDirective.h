#pragma once


#include <any>
#include <string>
#include <functional>



class IDirective
{
public:
    IDirective() {}
    virtual ~IDirective() {}
    virtual bool Execute() = 0;
    virtual void SetData(const std::any& inp) = 0;
    virtual void GetData(std::any& out) = 0;
    virtual void SetName(const std::string& name) = 0;
    virtual std::string GetName() = 0;

    // To be implemented as a seperateImplWrapper
    virtual void SetPreExecuteCommand(IDirective*& preExCmd) = 0;
    virtual void SetPostExecuteCommand(IDirective*& postExCmd) = 0;

    // Setting Preamble and Finale 
    virtual void SetPreamble(std::function<void(void)>& preammble) = 0;
    virtual void SetFinale(std::function<void(void)>& finale) = 0;

    virtual bool PreExecuteCommand() = 0;
    virtual bool PostExecuteCommand() = 0;

    // Set of methods that define the behaviour when the sequence is 
    // started  and when ended. The override should be made for those commands
    // which is the sequence start
    virtual bool PreExecuteSequence() = 0;
    virtual bool PostExecuteSequence() = 0;

};

