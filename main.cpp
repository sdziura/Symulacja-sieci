#include "simulation.h"


int main(){
		showMenu();
		int option;
		cin>> option;

		switch(option){
			case 1:
				createNetwork();
				break;

			case 2:
				break;

			case 3:
				cout<<"Insert the number of turns: \n";

				int turns;
				cin>> turns;

				simulate( NETWORK1, turns);
				break;
			case 4:
				LoadData();
				break;
			case 5:
				cout<<"Thank You for using this application!"<<endl;
				exit(0);
				break;
	}
}


