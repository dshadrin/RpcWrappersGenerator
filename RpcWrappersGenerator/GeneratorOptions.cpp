/*
* Copyright (C) 2014-2017 Rhonda Software.
* All rights reserved.
*/

//////////////////////////////////////////////////////////////////////////

#include "GeneratorOptions.h"
#include "RpcApiInterface.h"
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <cassert>

//////////////////////////////////////////////////////////////////////////
namespace po = boost::program_options;

namespace
{
    // list of default constants
    const fs::path defaultOutputFoldef("./");
    const fs::path defaultConfigTemplate("./config.xml.in");
    const std::string defaultConfigName = "generator-config.xml";
    const std::string defaultApiCfile = "api.c";
    const std::string defaultTargets = "all";
    const std::string defaultCC = "gcc";
    const bool defaultUseAbsolutePaths = false;

    po::options_description desc{ "Options" };
}

//////////////////////////////////////////////////////////////////////////
GOptions::GOptions()
    : mode(EGeneratorMode::help)
    , outFolder(defaultOutputFoldef)
    , configTemplate(defaultConfigTemplate)
    , configName(defaultConfigName)
    , apiCfile(defaultApiCfile)
    , targets(defaultTargets)
    , cc(defaultCC)
    , absolutePaths(defaultUseAbsolutePaths)
{

}

//////////////////////////////////////////////////////////////////////////
void to_cout(const std::vector<std::string> &v)
{
    std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>{std::cout, "\n"});
}

GOptions::EGeneratorMode GOptions::ParseOptions(int ac, const char** av)
{
    desc.add_options()
        ("help,h", "Display this information.")
        ("targets,t", po::value<std::string>(), ("Comma separated list of targets(\"CPP,C,SVR\" etc.) (default = \"" + defaultTargets + "\").").c_str())
        ("configure,c", po::value<std::vector<fs::path>>()->multitoken(), "Space separated list of INI files. INI files provided by Camera SDK or Platform project with path (absolute or related from current folder).")
        ("outxml", po::value<std::string>(), ("Output configuration file name(w / o path) for generating phase(default = \"" + defaultConfigName + "\").").c_str())
        ("outc", po::value<std::string>(), ("Output configuration file name (w/o path) for code analyzer (default = \"" + defaultApiCfile + "\").").c_str())
        ("inxml", po::value<fs::path>(), ("Input template configuration file with path (default = \"" + defaultConfigTemplate.generic_string() + "\").").c_str())
        ("outdir", po::value<fs::path>(), ("Absolute/relative path to output files (default = \"" + defaultOutputFoldef.generic_string() + "\").").c_str())
        ("fullpath", "Generate absolute paths in output files.")
        ("complete", "Full cycle of generating: configure, castxml, generating.")
        ("cc", po::value<std::string>(), ("Compiler name for using from castxml (default = \"" + defaultCC + "\").").c_str());

    po::options_description desc_hidden{ "Hidden options" };
    desc_hidden.add_options()
        ("configname", po::value<std::string>()->zero_tokens());

    po::positional_options_description pos_desc;
    pos_desc.add("configname", 1);

    po::options_description cmdline_options;
    cmdline_options.add(desc).add(desc_hidden);

    po::command_line_parser parser{ ac, av };
    parser.options(cmdline_options).positional(pos_desc).allow_unregistered().style(po::command_line_style::default_style | po::command_line_style::allow_slash_for_short);
    po::parsed_options parsed_options = parser.run();

    po::variables_map vm;
    try
    {
        po::store(parsed_options, vm);
        po::notify(vm);
    }
    catch (const po::error& e)
    {
        STG_EXCEPTION_ERROR(GMSG << e.what());
    }

    if (vm.count("help"))
    {
        mode = EGeneratorMode::help;
    }
    else
    {
        if (vm.count("complete"))
        {
            mode = EGeneratorMode::complete;
        }

        if (vm.count("configname"))
        {
            if (mode != EGeneratorMode::complete)
            {
                configName = vm["configname"].as<std::string>();
                mode = EGeneratorMode::generate;
            }
        }

        if (vm.count("configure"))
        {
            if (mode != EGeneratorMode::generate)
            {
                iniList = vm["configure"].as<std::vector<fs::path>>();
                if (mode != EGeneratorMode::complete)
                {
                    mode = EGeneratorMode::configure;
                }
            }
        }

        if (vm.count("targets"))
        {
            if (mode == EGeneratorMode::generate || mode == EGeneratorMode::complete)
            {
                targets = vm["targets"].as<std::string>();
            }
        }

        if (vm.count("outxml"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                configName = vm["outxml"].as<std::string>();
            }
        }

        if (vm.count("outc"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                apiCfile = vm["outc"].as<std::string>();
            }
        }

        if (vm.count("inxml"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                configTemplate = vm["inxml"].as<fs::path>();
            }
        }

        if (vm.count("outdir"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                outFolder = vm["outdir"].as<fs::path>();
            }
        }

        if (vm.count("fullpath"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                absolutePaths = true;
            }
        }

        if (vm.count("cc"))
        {
            if (mode == EGeneratorMode::configure || mode == EGeneratorMode::complete)
            {
                cc = vm["cc"].as<std::string>();
            }
        }
    }

    if ((mode == EGeneratorMode::configure || mode == EGeneratorMode::complete) && iniList.empty())
    {
        STG_EXCEPTION_ERROR("No INI files are defined.");
    }

    VerifyParameters();

    return mode;
}

//////////////////////////////////////////////////////////////////////////
void GOptions::VerifyParameters()
{
    switch (mode)
    {
    case EGeneratorMode::help:
        break;
    case EGeneratorMode::generate:
        CheckConfigureFileExists();
        break;
    case EGeneratorMode::complete:
    case EGeneratorMode::configure:
        CheckConfigureTemplateExists();
        CheckINIfilesExists();
        break;
    default:
        STG_EXCEPTION_ERROR("unexpected mode");
    }
}

//////////////////////////////////////////////////////////////////////////
void GOptions::CheckConfigureFileExists()
{
    fs::path cfg(configName);
    if (!fs::exists(cfg))
    {
        cfg = outFolder / cfg;
        if (fs::exists(cfg))
        {
            configName = cfg.string();
            boost::algorithm::replace_all(configName, "\\", "/");
        }
        else
        {
            STG_EXCEPTION_ERROR(GMSG << "Configure file \"" << configName << "\" was not found");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
void GOptions::CheckConfigureTemplateExists()
{
    if (fs::exists(configTemplate))
    {
        if (!configTemplate.is_absolute())
        {
            configTemplate = fs::absolute(configTemplate);
        }
    }
    else
    {
        STG_EXCEPTION_ERROR(GMSG << "Configure template file \"" << configTemplate << "\" was not found");
    }
}

//////////////////////////////////////////////////////////////////////////
void GOptions::CheckINIfilesExists()
{
    for (fs::path& ini : iniList)
    {
        if (fs::exists(ini))
        {
            if (!ini.is_absolute())
            {
                ini = fs::absolute(ini);
            }
        }
        else
        {
            STG_EXCEPTION_ERROR(GMSG << "INI file \"" << ini << "\" was not found");
        }
    }
}

//////////////////////////////////////////////////////////////////////////
void GOptions::PrintUsage()
{
    std::cout <<
        "Usage: ipcgen [<configuration-file-name>] [OPTIONS]\n";
    std::cout << desc << std::endl;
    std::cout <<
        "  <configuration-file-name> XML file contains configuration data.\n"
        "                            this file is output from configure phase (option --outxml).\n"
        "\n"
        "There is defined 4 work modes.\n"
        "1. Help mode:\n"
        "  ipcgen --help\n"
        "    Display help screen.\n\n"
        "2. Configure mode:\n"
        "  ipcgen --configure <INI-file> [[INI-file]...] [--outxml <config-xml>] [--outc <api-c>] [--inxml <config-in>] [--outdir <path>] [--fullpath true | false]\n"
        "    Generate configure files.\n\n"
        "3. Generating wrappers mode:\n"
        "  ipcgen [<configuration-file-name>] [--targets <list>]\n"
        "    Generating wrappers for targets platform.\n\n"
        "4. Execute all stages generating.\n"
        "  ipcgen --complete [OPTIONS]\n"
        "   Execute all stages: configure, castxml, generating.\n\n";
}

