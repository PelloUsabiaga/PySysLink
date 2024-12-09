#ifndef SRC_PY_SYS_LINK_BASE_PORT_LINK
#define SRC_PY_SYS_LINK_BASE_PORT_LINK

#include "ISimulationBlock.h"
#include "PortsAndSignalValues/InputPort.h"
#include "PortsAndSignalValues/OutputPort.h"
#include <algorithm>
#include <map>
#include "ConfigurationValue.h"

namespace PySysLinkBase
{
    class PortLink
    {
    public:
        PortLink(std::shared_ptr<OutputPort> origin, std::shared_ptr<InputPort> sink) : origin(origin), sink(sink) {}

        std::shared_ptr<OutputPort> origin;
        std::shared_ptr<InputPort> sink;

        static PortLink ParseFromConfig(std::map<std::string, ConfigurationValue> linkConfiguration, const std::vector<std::unique_ptr<ISimulationBlock>>& blocks)
        {
            std::string sourceBlockId = ConfigurationValueManager::TryGetConfigurationValue<std::string>("SourceBlockId", linkConfiguration);
            int sourcePortIdx = ConfigurationValueManager::TryGetConfigurationValue<int>("SourcePortIdx", linkConfiguration);
            std::string destinationBlockId = ConfigurationValueManager::TryGetConfigurationValue<std::string>("DestinationBlockId", linkConfiguration);
            int destinationPortIdx = ConfigurationValueManager::TryGetConfigurationValue<int>("DestinationPortIdx", linkConfiguration);

            ISimulationBlock& sourceBlock = ISimulationBlock::FindBlockById(sourceBlockId, blocks);
            ISimulationBlock& destinationBlock = ISimulationBlock::FindBlockById(destinationBlockId, blocks);

            return PortLink(sourceBlock.GetOutputPorts()[sourcePortIdx], destinationBlock.GetInputPorts()[destinationPortIdx]);
        }
    };
}

#endif /* SRC_PY_SYS_LINK_BASE_PORT_LINK */
