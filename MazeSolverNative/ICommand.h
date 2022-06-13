#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <any>
#include <optional>
#include <functional>

#include "IDirective.h"



template <typename InputDataType, typename OutputDataType>
class ICommand : public IDirective
{
    
public:
    ICommand() {}
    virtual ~ICommand() {}
    virtual void SetData(const std::any& inp) override
    {
        //std::cout << "Setting data from previous command" << std::endl;
        InputDataType input;
        try {
            input = std::any_cast<InputDataType>(inp);
            SetInput(input);
        }
        catch (const std::bad_any_cast& )
        {   
        }

    }
    virtual void SetInput(const InputDataType&) = 0;

    virtual void GetData(std::any& out) override
    {
        // GetOutput() is std::optional<OutputDataType> and so to extract value, .value() is to be used
        // Check the following example
        /*try {
            [[maybe_unused]] int n = opt.value();
        }
        catch (const std::bad_optional_access& e) {
            std::cout << e.what() << '\n';
        }*/
        out = GetOutput().value();
    }
    virtual std::optional<OutputDataType> GetOutput() = 0;

    /*virtual std::string GetKey()
    {
        std::string key = std::string(m_InputTypeInfo.name()) + std::string(m_OutputTypeInfo.name());
        return key;
    }*/
    //virtual bool Execute() = 0;
};

template <typename>
struct isCommand : public std::false_type {};

template <typename T, typename U>
struct isCommand<ICommand<T, U>> : std::true_type {};




