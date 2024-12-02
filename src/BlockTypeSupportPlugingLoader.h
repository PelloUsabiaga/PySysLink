#ifndef SRC_PY_SYS_LINK_BASE_BLOCK_TYPE_SUPPORT_PLUGING_LOADER
#define SRC_PY_SYS_LINK_BASE_BLOCK_TYPE_SUPPORT_PLUGING_LOADER

#include <map>
#include <memory>
#include <string>
#include <dlfcn.h> // For Linux/macOS dynamic linking. Use `windows.h` for Windows.

#include "IBlockFactory.h"

namespace PySysLinkBase {

class BlockTypeSupportPlugingLoader {
public:
    std::map<std::string, std::unique_ptr<IBlockFactory>> LoadPlugins(const std::string& pluginDirectory);

private:
    std::vector<std::string> FindSharedLibraries(const std::string& pluginDirectory);
    bool StringEndsWith(const std::string& str, const std::string& suffix);
};

} // namespace PySysLinkBase

#endif /* SRC_PY_SYS_LINK_BASE_BLOCK_TYPE_SUPPORT_PLUGING_LOADER */