#pragma once

#include <iostream>
#include <type_traits>
#include <string>
#include <memory>
#include <mutex>
#include <functional>
#include "ICommand.h"

namespace MazeSolver {
	template<typename GenericCommandImplWrapper, typename InputDataType, typename OutputDataType>
	class GenericCommand : public ICommand< InputDataType, OutputDataType>
	{
	private:
		std::string m_CommandName;
		IDirective* m_PreExecuteCmd = nullptr, * m_PostExecuteCmd = nullptr;
		std::function<void(void)> m_Preamble, m_Finale;
	public:
		GenericCommand() {}
		virtual ~GenericCommand() {}
		using GenericCommandImplementor = typename GenericCommandImplWrapper::GenericCommandImplementer;
		using command_input_data_type = typename GenericCommandImplWrapper::command_input_data_type;
		using command_output_data_type = typename GenericCommandImplWrapper::command_output_data_type;
		virtual void SetInput(const InputDataType& data) override
		{
			static_cast<GenericCommandImplementor*>(this)->ActuallySetCommandInputData(data);
		}
		virtual std::optional<OutputDataType> GetOutput() override
		{
			return static_cast<GenericCommandImplementor*>(this)->ActuallyGetCommandOutputData();
		}
		virtual bool Execute() override
		{
			bool status = true;
			if (m_PreExecuteCmd)
				status = status && m_PreExecuteCmd->Execute();
			status = status && static_cast<GenericCommandImplementor*>(this)->ActuallyPreExecuteCommand();
			if (m_Preamble)
				m_Preamble();
			status = status && static_cast<GenericCommandImplementor*>(this)->ActuallyExecute();
			if (m_Finale)
				m_Finale();
			status = status && static_cast<GenericCommandImplementor*>(this)->ActuallyPostExecuteCommand();

			if (m_PostExecuteCmd)
				status = status && m_PostExecuteCmd->Execute();

			return status;
		}

		virtual void SetName(const std::string& name) override
		{
			m_CommandName = name;
		}
		virtual std::string GetName() override
		{
			return m_CommandName;
		}

		virtual void SetPreExecuteCommand(IDirective*& preExCmd) override { m_PreExecuteCmd = preExCmd; }
		virtual void SetPostExecuteCommand(IDirective*& postExCmd) override { m_PostExecuteCmd = postExCmd; }
		virtual void SetPreamble(std::function<void(void)>& preammble) override { m_Preamble = preammble; }
		virtual void SetFinale(std::function<void(void)>& finale) override { m_Finale = finale; }
		virtual bool PreExecuteSequence() override
		{
			return static_cast<GenericCommandImplementor*>(this)->ActuallyPreExecuteSequence();
		}
		virtual bool PostExecuteSequence() override
		{
			return static_cast<GenericCommandImplementor*>(this)->ActuallyPostExecuteSequence();
		}

		virtual bool PreExecuteCommand() override
		{
			return static_cast<GenericCommandImplementor*>(this)->ActuallyPreExecuteCommand();
		}
		virtual bool PostExecuteCommand() override
		{
			return static_cast<GenericCommandImplementor*>(this)->ActuallyPostExecuteCommand();
		}
	};
	template <typename InputDataType, typename OutputDataType, typename ExecutorType>
	class GenericCommandImplWrapper
	{
	public:

		using command_input_data_type = InputDataType;
		using command_output_data_type = OutputDataType;
		using command_executor_type = ExecutorType;
		class GenericCommandImplementer :
			public GenericCommand<GenericCommandImplWrapper, InputDataType,
			OutputDataType>
		{
		private:

			command_executor_type* m_CommandExecutor;
			inline static std::unique_ptr<GenericCommandImplementer> m_GenericCommandImplementerInstance;
			GenericCommandImplementer(const std::string& commandName, command_executor_type& executor) :
				m_CommandExecutor(&executor)
			{
				this->SetName(commandName);
			}

			GenericCommandImplementer(const std::string& commandName, command_executor_type& executor,
				std::function<void(void)>& preamble, std::function<void(void)>& finale) :
				m_CommandExecutor(&executor)
			{
				this->SetName(commandName);
				this->SetPreamble(preamble);
				this->SetFinale(finale);
			}
			void SetCommandExecutor(command_executor_type& executor)
			{
				m_CommandExecutor = &executor;
			}

		public:
			static GenericCommandImplementer*
				GetInstance(const std::string& commandName, command_executor_type& executor)
			{
				static std::once_flag onceFlag;
				std::call_once(onceFlag, [&]() {
					m_GenericCommandImplementerInstance.reset(new GenericCommandImplementer(commandName, executor));
					std::cout << "Command : " << commandName << " created!" << std::endl;
					});

				return m_GenericCommandImplementerInstance.get();
			}
			virtual ~GenericCommandImplementer() = default;

			bool ActuallyPreExecuteSequence()
			{
				return m_CommandExecutor->PreExecuteSequence();
			}

			bool ActuallyPostExecuteSequence()
			{
				return m_CommandExecutor->PostExecuteSequence();
			}

			bool  ActuallyPreExecuteCommand()
			{
				return m_CommandExecutor->PreExecuteCommand();
			}

			bool  ActuallyPostExecuteCommand()
			{
				return m_CommandExecutor->PostExecuteCommand();
			}

			bool ActuallyExecute()
			{
				auto output = m_CommandExecutor->RunExecute();
				return output;
			}

			void ActuallySetCommandInputData(const command_input_data_type& data)
			{
				m_CommandExecutor->SetInput(data);
			}

			std::optional<command_output_data_type> ActuallyGetCommandOutputData()
			{
				return (m_CommandExecutor->GetOutput());
			}
		};
	};
}




