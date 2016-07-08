#include "CmdlineParams.hxx"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdexcept>

static std::string getCmdOption(char ** begin, char ** end,
		const std::string & option) {
	char ** itr = std::find(begin, end, option);
	if (itr != end && ++itr != end) {
		return *itr;
	}
	return "";
}

static bool cmdOptionExists(char** begin, char** end,
		const std::string& option) {
	return std::find(begin, end, option) != end;
}

void CmdlineParams::printHelp() const {
	std::cerr << "usage is:" << std::endl << binary
			<< " -a app_file -o output_folder -n num_micro_workload -d depth -w width"
			<< std::endl;
}

bool CmdlineParams::getHelp() const {
	return help;
}

std::string CmdlineParams::getOutputFolder() const {
	return outputFolder;
}

std::string CmdlineParams::getAppXml() const {
	return appXml;
}

size_t CmdlineParams::getNumWorkload() const {
	return numWorkload;
}

size_t CmdlineParams::getWidth() const {
	return width;
}

size_t CmdlineParams::getDepth() const {
	return depth;
}

CmdlineParams::CmdlineParams(int argc, char **argv) {
	binary = argv[0];

	// Check if user asked for help
	if (cmdOptionExists(argv, argv + argc, "-h")) {
		help = true;
	} else {
		help = false;
	}

	// Get output folder
	outputFolder = getCmdOption(argv, argv + argc, "-o");
	if (outputFolder.empty()) {
		printHelp();
		exit(-1);
	}
	struct stat info;
	if (stat(outputFolder.c_str(), &info) != 0) {
		std::cerr << "cannot access output folder " << outputFolder
				<< std::endl;
		exit(-1);
	} else if (!(info.st_mode & S_IFDIR)) {
		std::cerr << "output folder " << outputFolder
				<< " is not a folder but a file" << std::endl;
		exit(-1);
	}

	// Get application file
	appXml = getCmdOption(argv, argv + argc, "-a");
	if (appXml.empty()) {
		printHelp();
		exit(-1);
	}
	if (!appXml.empty() && !std::ifstream(appXml)) {
		std::cerr << "application file " << appXml << " doesn't exist"
				<< std::endl;
		exit(-1);
	}

	// Get number of micro workload to generate
	std::string numWorkloadString = getCmdOption(argv, argv + argc, "-n");
	if (numWorkloadString.empty()) {
		printHelp();
		exit(-1);
	}
	numWorkload = std::stoi(numWorkloadString);

	// Get width
	std::string widthString = getCmdOption(argv, argv + argc, "-w");
	if (widthString.empty()) {
		printHelp();
		exit(-1);
	}
	width = std::stoi(widthString);

	// Get depth
	std::string depthString = getCmdOption(argv, argv + argc, "-d");
	if (depthString.empty()) {
		printHelp();
		exit(-1);
	}
	depth = std::stoi(depthString);
}
