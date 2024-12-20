#include "ISimulationBlock.h"
#include <algorithm>

namespace PySysLinkBase
{
    ISimulationBlock::ISimulationBlock(std::map<std::string, ConfigurationValue> blockConfiguration, std::shared_ptr<IBlockEventsHandler> blockEventsHandler)
    {
        this->name = ConfigurationValueManager::TryGetConfigurationValue<std::string>("Name", blockConfiguration);
        this->id = ConfigurationValueManager::TryGetConfigurationValue<std::string>("Id", blockConfiguration);

        this->blockEventsHandler = blockEventsHandler;
    }

    const std::string ISimulationBlock::GetId() const
    {
        return this->id;
    }
    const std::string ISimulationBlock::GetName() const
    {
        return this->name;
    }

    ISimulationBlock& ISimulationBlock::FindBlockById(std::string id, const std::vector<std::unique_ptr<ISimulationBlock>>& blocksToFind)
    {
        auto it = std::find_if(blocksToFind.begin(), blocksToFind.end(), [&id](const std::unique_ptr<ISimulationBlock>& block) {return block->GetId() == id;});

        if (it != blocksToFind.end())
        {
            int index = std::distance(blocksToFind.begin(), it);
            return *blocksToFind[index];
        }
        else
        {
            throw std::out_of_range("Block with id: " + id + " not found in provided set.");
        }
    }

    std::shared_ptr<ISimulationBlock> ISimulationBlock::FindBlockById(std::string id, const std::vector<std::shared_ptr<ISimulationBlock>>& blocksToFind)
    {
        auto it = std::find_if(blocksToFind.begin(), blocksToFind.end(), [&id](const std::shared_ptr<ISimulationBlock>& block) {return block->GetId() == id;});

        if (it != blocksToFind.end())
        {
            int index = std::distance(blocksToFind.begin(), it);
            return blocksToFind[index];
        }
        else
        {
            throw std::out_of_range("Block with id: " + id + " not found in provided set.");
        }
    }

    bool ISimulationBlock::IsBlockFreeSource() const
    {
        if (this->GetOutputPorts().size() == 0)
        {
            return false;
        }
        
        std::vector<std::shared_ptr<InputPort>> inputPorts = this->GetInputPorts();
        bool areAllInputsNotDirectFeedthrough = true;
        for (int j = 0; j < inputPorts.size(); j++)
        {
            areAllInputsNotDirectFeedthrough &= !inputPorts[j]->HasDirectFeedtrough();
        }
        if (areAllInputsNotDirectFeedthrough)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool ISimulationBlock::IsInputDirectBlockChainEnd(int inputIndex) const
    {
        if (this->GetOutputPorts().size() == 0 || !this->GetInputPorts()[inputIndex]->HasDirectFeedtrough())
        {
            return true;
        }
        else
        {
            return false;
        }
    } 

    void ISimulationBlock::NotifyEvent(std::shared_ptr<PySysLinkBase::BlockEvent> blockEvent) const
    {
        this->blockEventsHandler->BlockEventCallback(blockEvent);
    }


} // namespace PySysLinkBase
