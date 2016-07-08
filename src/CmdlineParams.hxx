/*
 * dcSimuParams.hxx
 *
 *  Created on: Sep 10, 2015
 *      Author: manu
 */

#ifndef MAIN_NOC_PPA_CMAIN_DCSIMUPARAMS_HXX_
#define MAIN_NOC_PPA_CMAIN_DCSIMUPARAMS_HXX_

#include <string>

class CmdlineParams {
public:
	std::string getOutputFolder() const;
	std::string getAppXml() const;
	size_t getNumWorkload() const;
	size_t getWidth() const;
	size_t getDepth() const;
	CmdlineParams(int argc, char** argv);
	void printHelp() const;
	bool getHelp() const;

private:
	std::string outputFolder;
	std::string appXml;
	bool help;
	size_t numWorkload;
	size_t width;
	size_t depth;
	char* binary;
};



#endif /* MAIN_NOC_PPA_CMAIN_DCSIMUPARAMS_HXX_ */
