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
        InputDataType input;
        try {
            input = std::any_cast<InputDataType>(inp);
            SetInput(input);
        }
        catch (const std::bad_any_cast& ){}
    }
    virtual void SetInput(const InputDataType&) = 0;
    virtual void GetData(std::any& out) override
    {   
        out = GetOutput().value();
    }
    virtual std::optional<OutputDataType> GetOutput() = 0;
};

template <typename>
struct isCommand : public std::false_type {};

template <typename T, typename U>
struct isCommand<ICommand<T, U>> : std::true_type {};




