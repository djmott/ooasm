/** @file
Command line interface
@copyright David Mott (c) 2016. Distributed under the Boost Software License Version 1.0. See LICENSE.md or http://boost.org/LICENSE_1_0.txt for details.
*/

#pragma once


namespace ooasm{
  namespace cli{
    using namespace xtd::parse;

    namespace _{
      STRING(szFormatParam,"--format=");
      STRING(szDwarf, "dwarf");
      STRING(szBinary,"binary")
      STRING(szInputParam, "--in=");
      STRING(szOutParam, "--out=");
      //REGEX(szPath, "(^([a-z]|[A-Z]):(?=\\\\(?![\\0-\\37<>:\"/\\\\|?*])|\\/(?![\\0-\\37<>:\"/\\\\|?*])|$)|^\\\\(?=[\\\\\\/][^\\0-\\37<>:\"/\\\\|?*]+)|^(?=(\\\\|\\/)$)|^\\.(?=(\\\\|\\/)$)|^\\.\\.(?=(\\\\|\\/)$)|^(?=(\\\\|\\/)[^\\0-\\37<>:\"/\\\\|?*]+)|^\\.(?=(\\\\|\\/)[^\\0-\\37<>:\"/\\\\|?*]+)|^\\.\\.(?=(\\\\|\\/)[^\\0-\\37<>:\"/\\\\|?*]+))((\\\\|\\/)[^\\0-\\37<>:\"/\\\\|?*]+|(\\\\|\\/)$)*()$");
      REGEX(szPath, "^(.*/)?(?:$|(.+?)(?:(\\.[^.]*$)|$))");
    }

    struct format_param : rule<format_param, and_<_::szFormatParam, or_<_::szBinary, _::szDwarf>>>{
      using pointer = std::shared_ptr<format_param>;
      template <typename ..._argTs> format_param(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...){}
    };

    struct file_path : rule<file_path, _::szPath>{
      using pointer = std::shared_ptr<file_path>;
      template <typename ..._argTs> file_path(_argTs&&...oArgs) : rule(std::forward<_argTs>(oArgs)...){}
    };

    struct input_param : rule<input_param, and_<_::szInputParam, _::szPath >>{
      using pointer = std::shared_ptr<input_param>;
      template <typename ... _argts> input_param(_argts&&...oArgs) : rule(std::forward<_argts>(oArgs)...){}
    };

    struct output_param : rule<output_param, and_<_::szOutParam, _::szPath>>{
      using pointer = std::shared_ptr<output_param>;
      template <typename ... _argts> output_param(_argts&&...oArgs) : rule(std::forward<_argts>(oArgs)...){}
    };

    struct grammar : rule<grammar, or_<input_param, output_param, format_param>>{
      template <typename ... _argts> grammar(_argts&&...oArgs) : rule(std::forward<_argts>(oArgs)...){}
    };

    using parser = xtd::parser<grammar, true, whitespace<' ', '\t', '\r', '\n'>>;

  }
}