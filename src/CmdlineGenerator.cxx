#include "commons/microworkload/MicroWorkloadGenerator.hxx"
#include "CmdlineParams.hxx"
#include "commons/parser/dcAmaltheaParser.h"
#include <iostream>
#include <sstream>

int main(int argc, char **argv) {

	// Parse arguments
	CmdlineParams params(argc, argv);

	// Use the parser to create an AmApplication object
	string appPath = params.getAppXml();
	dcAmaltheaParser amaltheaParser;
	AmApplication* amApplication = new AmApplication();
	amaltheaParser.ParseAmaltheaFile(appPath, amApplication);

	// Convert the AmApplication to a dcApplication
	dcApplication application;
	dcTaskGraph* taskGraph = application.createGraph("dcTaskGraph");
	application.CreateGraphEntities(taskGraph, amApplication, true);

	// Generate micro workloads
	dcMwGenerator gen;
	vector<dcTaskGraph*> workloads = gen.MwGenerate(taskGraph, amApplication,
			params.getWidth(), params.getDepth(), params.getNumWorkload());

	// For each generated micro workload, dump it in a dot file
	int i = 0;
	for (std::vector<dcTaskGraph*>::iterator it = workloads.begin();
			it != workloads.end(); ++it) {
		vector<dcTask*> tasks = application.GetAllTasks(*it);
		std::cout << "workload generated" << " has " << tasks.size() << " tasks"
				<< std::endl;
		std::ostringstream mwName;
		mwName << params.getOutputFolder() << "/micro-workload-" << i << ".dot";
		dcApplication::dumpTaskGraphFile(mwName.str(), tasks);
		i++;
	}

	return 0;
}

