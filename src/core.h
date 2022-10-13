#pragma once

#include <memory>

namespace gui
{
  template<typename T>
  using Ref = std::shared_ptr<T>;
}// namespace