 ///
 /// @file    Task.hpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2020-10-16 17:38:13
 ///
 
#ifndef __WD_TASK_HPP__
#define  __WD_TASK_HPP__

#include <functional>

namespace wd
{
using Task = std::function<void()>;

}//end of namespace wd


#endif
