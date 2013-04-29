#include <otawa/otawa.h>
#include <otawa/cfg/features.h>
#include <otawa/display/CFGDrawer.h>
#include <otawa/display/Graph.h>
#include <otawa/cfg/CFG.h>
#include <otawa/display/CFGOutput.h>
#include <otawa/util/FlowFactLoader.h>

#include "Core/AutomataProduct.h"
#include "Core/AutomataBB.h"
#include "Core/FFXLoader.h"

int main(int argc, char **argv) {

	cout << "\nCas nominal\n";



	// Parse FFX, crée les Automates associés. => parsing stubbé par la création d'automates directement.

	// Rencontre d'un call avec comme paramètres : fonction f1, adresse addressCallF1
	// Etat Initial
	State initCallF1State =  State("C_nf1");
	// Etats terminaux
	std::vector<State> endCallF1States;
	endCallF1States.push_back(initCallF1State);
	// Transition
	std::vector<Transition> listCallF1Transitions;
	uint32_t test1 = 5644;
	listCallF1Transitions.push_back(Transition(test1, 0, Transition::transType(0), initCallF1State, State("C_f1")));

	AutomataBB autoCallF1 = AutomataBB("callF1",listCallF1Transitions, initCallF1State, endCallF1States);

	autoCallF1.display();
	// Rencontre d'une fonction avec comme paramètres : nom f1, adresse AddressF1
	// Etat Initial
	State initF1State =  State("F_nf1");
	// Etats terminaux
	std::vector<State> endF1States;
	endF1States.push_back(initF1State);
	// Transition
	std::vector<Transition> listF1Transitions;
	uint32_t test2 = 4687;
	listF1Transitions.push_back(Transition(0, 4687, Transition::transType(2), initF1State, State("F_f1")));

	AutomataBB autoF1 = AutomataBB("F1",listF1Transitions, initF1State, endF1States);

	AutomataProduct aP_Nominal = AutomataProduct(autoCallF1, autoF1);


	aP_Nominal.display();

	std::cout << aP_Nominal.getCurrentState().getLabel();


	std::vector<Automata> autoListe;






	try {
		//Définition d'une liste de propriété
		otawa::PropList props;
		otawa::Processor::VERBOSE(props) = true;
		//Définition du workspace,
		//Chargement du fichier en parametre de la fonction load
		otawa::WorkSpace *ws = otawa::MANAGER.load(argv[1], props);
		//Chargement de tous les outils pour la construction du CFG, non Inliné.
		//Utiliser otawa::VIRTUALIZED_CFG_FEATURE en amont.
		ws->require(otawa::VIRTUALIZED_CFG_FEATURE, props);
		ws->require(otawa::COLLECTED_CFG_FEATURE, props);
		//Récupération de la collection de CFGs
		const otawa::CFGCollection *coll = otawa::INVOLVED_CFGS(ws);
		//Accès aux différents CFG (un seul si on a mis en place virtualized)
		for(int i = 0; i < coll->count(); i++)
			std::cout << "CFG " << coll->get(i) << "\n";


		otawa::display::CFGOutput out;
		otawa::display::CFGOutput::KIND(props) = otawa::display::OUTPUT_DOT;
		out.process(ws, props);


		FFXLoader ffxl(argv[2], ws);

		ffxl.displayAllAutomatas();
		for (unsigned int i=0; i<ffxl.getAutomatas().size(); i++ )
			ffxl.getAutomatas()[i].viewAutomata();


	}
	catch(otawa::Exception& e) {
		//Erreur lors de la fonction load
		std::cerr << "ERROR: " << e.message() << elm::io::endl;
	}




}

