#include "simulation.h"

Type convert(int i){
	switch(i){
	case 1: return Type::Basic; break;
	case 2: return Type::Recipient; break;
	case 3: return Type::Basic; break;
	case 4: return Type::Recipient; break;
	case 5: return Type::Basic; break;
	}

}


//class Product

int Product::get_id(){
	return basic_id;
}

//class BasicElement

int BasicElement::get_id(){
	return id;
}
Type BasicElement::return_type(){
	return type;
}

//class Recipients

std::map<BasicElement*, double > Recipients::getProbabilities(){
	return probabilities;
}

void Recipients::setProbabilities(std::map<BasicElement* , double> map_given ){
	probabilities = map_given;

}

bool Recipients::addRecipient(BasicElement* basic){
	auto size = probabilities.size()+1;
	auto temp = 1/size;
	for(auto iter = probabilities.begin(); iter != probabilities.end(); iter++){

		probabilities[iter->first]=temp;
		//iter->second = temp;
		}
		probabilities.insert( std::pair<BasicElement*, double>(basic, temp));
	return true;
}

bool Recipients::addRecipientwithProbability(BasicElement& basic, double probability)
{
	for(auto iter = probabilities.begin(); iter != probabilities.end(); iter++)
	{
		if( iter->first==basic){
			std::string exception_1 = "This element already exists, insert new one /n";
			throw exception_1 ;//w catch tutaj dać string
		}
		else{
			auto temp=iter -> second ;
			probabilities[iter -> first] = (1 - probability )* temp;
			//iter -> second = (1 - probability )* temp;
		}
	}
	probabilities.insert( std::pair<BasicElement*, double>(basic, probability));
}

bool Recipients::removeRecipient(BasicElement* basic){

	auto temp= probabilities.at(basic);

	for(auto iter = probabilities.begin(); iter != probabilities.end(); iter++){

		probabilities[iter->first]=probabilities[iter->first]/(1-temp);
		if(iter->first==basic)
			probabilities.erase(iter);
		//iter->second=iter->second/(1-temp);
	}
	return true;
}

void Recipients::view_list(){
	for(auto iter = probabilities.begin(); iter != probabilities.end(); iter++){
		std::cout << "Type: "<< *(iter->first)->return_type() <<"\nID:"<<(*(iter->first)).get_id()<<" Probability:"<<iter->second;

	}

}

double Recipients::get_probability(BasicElement* basic){
	return probabilities.at(basic);
}


//class Sender

bool Sender::addRecipient(BasicElement& a_basic,double prob_given){
	if(recipients_list.addRecipientwithProbability(a_basic, prob_given))
		return true;
	return false;

}
bool Sender::deleteRecipient(BasicElement* r_basic ){
	if(recipients_list.removeRecipient(r_basic))
		return true;
	return false;
}
void Sender::show_list(){
	recipients_list.view_list();
}
double Sender::get_probability(BasicElement* basic){
	return recipients_list.get_probability(basic);

}

//class Queue

virtual std::ostringstream Queue::at(){
	std::ostringstream bufor;
	for(int i = 0; i != products_deque.size(); i++){

		bufor << products_deque.at(i).get_id();
	}
	return bufor;
}

QUEUE_TYPE Queue::get_Type(){
	return queue_type;
}

void Queue::push(const Product & product){

	if( queue_type == QUEUE_TYPE::FIFO)
		products_deque.push_back( product );
	else
		products_deque.push_front( product );
}

void Queue::pop(){
	products_deque.pop_front();
}

bool Queue::empty(){
	return products_deque.empty();
}

int Queue::size(){
	return products_deque.size();
}

void Queue::view(){

	for( auto iter = products_deque.begin() ; iter != products_deque.end() ; iter++){
		std::cout<< *iter <<" ";
	}
}

//class Ramp

int Ramp::get_sending_frequency(){
	return sending_frequency;
}

//class Storehouse

void Storehouse::receive_product(const Product & product){
	products_in_storehouse.push_back(product);
}

std::vector< Product > Storehouse::get_products(){
	return products_in_storehouse;
}

//class Worker

void Worker::receive_product( const Product & new_product){
	queue -> push ( new_product);
}

int Worker::get_processing_time(){
	return processing_time;
}

void Worker::doProduct(){
	std::cout<<"Product is getting ready to be sent"<<std::endl;
}

auto Worker::get_queue_type(){
	queue->get_Type();
}

Queue Worker::get_Queue(){
	return queue;
}

//class Network

//Worker part

std::vector<Worker> Network::getWorkers(){
	return Workers;
}

bool Network::addWorker(Worker & new_worker){
	if( Workers.push_back( new_worker ))
		return true;
	else
		return false;
}

bool Network::removeWorker( ElementID id){
	for( auto iter = Workers.begin(); iter != Workers.end(); iter++)
		if( (*iter).BasicElement::get_id() == id){
				Workers.erase( iter );
				return true;
			}
		else{	std::ostringstream temp;
				temp << "There is no worker with ID:"<< id <<std::endl;
				std::string exception_2 = temp.str();
				throw exception_2;
			}
	return false;
}

//Ramp part

std::vector<Ramp> Network::getRamps(){
	return Ramps;
}

bool Network::addRamp(Ramp & new_ramp){
	if( Ramps.push_back( new_ramp ))
		return true;
	return false;
}

bool Network::removeRamp( ElementID id){
	for( auto iter = Ramps.begin(); iter != Ramps.end(); iter++)
			if( (*iter).BasicElement::get_id() == id)
				{
					Ramps.erase( iter );
					return true;
				}
			else{
					std::ostringstream temp;
					temp << "There is no ramp with ID:"<< id << std::endl;
					std::string exception_3 = temp.str();
					throw exception_3;

				}
	return false;

}

//Storehouse part

std::vector<Storehouse> Network::getStorehouses(){
	return Storehouses;
}

bool Network::addStorehouse(Storehouse & new_storehouse){
	if( Storehouses.push_back( new_storehouse ))
		return true;
	else
		return false;
}

bool Network::removeStorehouse( ElementID id){
	for( auto iter = Storehouses.begin(); iter != Storehouses.end(); iter++)
				if( (*iter).BasicElement::get_id() == id)
					{
						Storehouses.erase( iter );
						return true;
					}
				else{
						std::ostringstream temp;
						temp << "There is no storehouse with ID:"<< id << std::endl;
						std::string exception_4 = temp.str();
						throw exception_4;
					}
	return false;
}
bool Network::check_integrity(){

	for( int i = 0 ; i < Workers.size() ;i++){
		for( auto iter_workers = (Workers.at(i)).recipients_list.probabilities.begin(); iter_workers != (Workers.at(i)).recipients_list.probabilities.end() ; iter_workers++)
		{
			if((iter_workers->first)->type == Type::Storehouse)
				{
					for( int j = 0 ; j < Ramps.size() ; j++){
						for( auto iter_ramps = (Ramps.at(i)).recipients_list.probabilities.begin(); iter_ramps != (Ramps.at(i)).recipients_list.probabilities.end(); iter_ramps++){

							if((iter_ramps->first)->type == Type::Storehouse)
							{ 		std::ostringstream temp;
									temp << "The network is not integral because product from ramp ID:"<< (iter_ramps->first)->id<< "can't go straightaway to the storehouse"<<std::endl;
									std::string exception_5 = temp.str();
									throw exception_5;

								return false;
							}
							else
								return true;

						}

					}
				}
			else{
					std::ostringstream temp;
					temp << "The network is not integral because Worker ID:"<< (iter_workers->first)->id << "has no recipient of type Storehouse"<< std::endl;
					std::string exception_6 = temp.str();
					throw exception_6;


			}
		}
	}

}

//class Interval_Report one generują o stanie symulacji do struktury osobna

bool Interval_Report::should_generate_raport(int round_number){
	if( round_number <= 0){
		std::ostringstream temp;
		temp << "The round_number cannot be less than 0, or equal to 0"<<std::endl;
		std::string exception_8 = temp.str();
		throw exception_8;
	}
	auto temp2 = round_number % time_interval;
	if( temp2 == 0)
		return true;
	else
		return false;
}

void Interval_Report::Interval_Report_Generate(int time_interval, Network network, int turn_number){
	if( time_interval <= 0 ){
		std::ostringstream temp;
				temp << "The time_interval cannot be less than 0, or equal to 0"<<std::endl;
				std::string exception_11 = temp.str();
				throw exception_11;
	}
	else if( turn_number % time_interval ==0 ){
		std::fstream interval_report;
		interval_report.open("interval_report.txt", std::ios::out);
		if( interval_report.good() ){
			std::string head = "Interval Report\nWORKERS\n";
			interval_report.write(& head[0], head.length());
			std::ostringstream bufor;
			auto workers = network.getWorkers();
			for(auto iter = workers.begin(); iter != workers.end(); iter++){
				bufor << "Worker # "<< (*iter).get_id() <<"\n Queue: ";
				auto ready = bufor.str();
				interval_report.write(& ready[0], ready.length());
				auto temp_queue = (*iter).get_Queue();
				bufor = temp_queue.at();
				ready = bufor.str();
				interval_report.write(& ready[0], ready.length());
				bufor.clear();
				ready.clear();

			}

			auto storehouses = network.getStorehouses();
			for( auto iter = storehouses.begin() ; iter != storehouses.end() ; iter++){
				bufor <<" STOREHOUSES\n" << " Storehouse #" << (*iter).get_id() << "\nQueue: ";
				auto temp_products = (*iter).get_products();
				for( auto iter_2 = temp_products.begin() ; iter_2 != temp_products.end() ; iter_2++){
					bufor << "# "<< iter_2->get_id() <<", ";
				}
				auto ready = bufor.str();
				interval_report.write(& ready[0], ready.length());
				bufor.clear();
				ready.clear();
			}https://stackoverflow.com/questions/5757721/use-getline-and-while-loop-to-split-a-string
			interval_report.close();
		}
	}

}
//class Structure_Report

bool Structure_Report::should_generate_raport( bool answer){

	return answer;
}

void Structure_Report::Structure_Report_Generate(Network network){
	std::fstream structure_report;
	structure_report.open("structure_report.txt",std::ios::out);
	if( structure_report.good()){


		std::string head = "Structure Report\nRamps:\n";
		structure_report.write(& head[0], head.length());
		std::ostringstream bufor;
		auto ramps = network.getRamps();
		for( auto iter = ramps.begin(); iter != ramps.end() ; iter++){


			bufor << "RAMPS" << std::endl;
			bufor << "Ramp #" << (*iter).get_id() << std::endl << "Delivery interval: " << (*iter).get_sending_frequency() << std::endl <<"Receivers: \n";
			Recipients recp = (*iter).get_list();
			auto map = recp.getProbabilities();
			for ( auto iter_2 = map.begin(); iter_2 != map.end(); iter_2++){
				bufor <<"worker #"<<(iter_2->first)->get_id() <<iter_2->second<<std::endl;
			}
			auto ready = bufor.str();
			structure_report.write(& ready[0], ready.length());
			bufor.clear();
			ready.clear();

		}
		auto workers = network.getWorkers();
		for( auto iter = workers.begin(); iter != workers.end() ; iter++){

			bufor << "WORKERS" << std::endl;
			bufor << "Worker #" << (*iter).get_id() << std::endl << "Processing time: " << (*iter).get_processing_time() << std::endl <<"\nQueue Type: "<< (*iter).get_queue_type()<< "\nReceivers: \n";
			Recipients recp = (*iter).get_list();
			auto map = recp.getProbabilities();
			for ( auto iter_2 = map.begin(); iter_2 != map.end(); iter_2++){
					bufor << ( iter_2 -> first)-> return_type()<<" # "<< ( iter_2 -> first)-> get_id() << "probability: "<< (iter_2->second) << std::endl;
					}
			auto ready = bufor.str();
			structure_report.write(& ready[0], ready.length());
			bufor.clear();
			ready.clear();

			}
		auto storehouses = network.getStorehouses();
		for( auto iter = storehouses.begin(); iter != storehouses.end(); iter++){

			bufor << "STOREHOUSES" << std::endl;
			bufor << "Storehouse #" << iter->get_id();
			auto ready = bufor.str();
			structure_report.write(& ready[0], ready.length());
						bufor.clear();
						ready.clear();

		}

		structure_report.close();
	}
	else{
		std::string exception_9 = "File opening failed\n";
		throw exception_9;
	}

}


//class Turns_Report

bool Turns_Report::should_generate_raport(int round_number){
	if( turns.empty()){
		std::ostringstream temp;
		temp <<"The list of turns is empty. Insert the numbers of turns that you want to generate report."<<std::endl;
		std::string exception_10 = temp.str() ;
		throw exception_10;
		return false;
		}

	for( auto iter = turns.begin(); iter != turns.end() ; iter++){
		if( (*iter) == round_number)
			return true;
		else
			return false;
	}
	return false;

}

void Turns_Report::Turns_Report_Generate(std::set<int> turns, Network network){
	std::fstream turns_report;
	turns_report.open("turns_report.txt", std::ios::out);
	if(turns_report.good()){
		std::ostringstream bufor;

		for( auto iter = turns.begin() ; iter != turns.end() ; iter++){
			if( (*iter) == /*coś*/){
				bufor << " TURN # "<< (*iter) << std::endl;
				auto workers = network.getWorkers();
					for(auto iter = workers.begin(); iter != workers.end(); iter++){

						bufor << "Worker # "<< (*iter).get_id() <<"\n Queue: ";
							auto ready = bufor.str();
							turns_report.write(& ready[0], ready.length());
							auto temp_queue = (*iter).get_Queue();
							bufor = temp_queue.at();
							ready = bufor.str();
							turns_report.write(& ready[0], ready.length());
							bufor.clear();
							ready.clear();

						}

				auto storehouses = network.getStorehouses();
					for( auto iter = storehouses.begin() ; iter != storehouses.end() ; iter++){
							bufor <<" STOREHOUSES\n" << " Storehouse #" << (*iter).get_id() << "\nQueue: ";
							auto temp_products = (*iter).get_products();
							for( auto iter_2 = temp_products.begin() ; iter_2 != temp_products.end() ; iter_2++){
									bufor << "# "<< iter_2->get_id() <<", ";
								}
							auto ready = bufor.str();
							turns_report.write(& ready[0], ready.length());
							bufor.clear();
							ready.clear();
							}

			}
		}
		turns_report.close();
	}
	else
	{
		std::string exception_10 = "File opening failed\n";
		throw exception_10;
	}


}

void LoadData( std::fstream file){
	file.open("data.txt");
	std::string data;
	if(!file.good())
	{
			std::string exception_12 = "File opening failed\n";
			throw exception_12;
		}
			while( getline(file, data)){
				data.


	}


}

void showMenu(){
	std::cout<<"Welcome in NetworkSimulator. Choose the option: "<< std::endl;

			std::cout<<"1) Create new network."<<"2) Modify created network"<<endl;
			std::cout<<"3) Simulate           "<<"4) Load data"<<endl;
			cout<<"5) Exit"<<endl;
}

void createNetwork(){
	std::vector<Ramp> ramps;
	std::vector<Worker> workers;
	std::vector<Storehouse> storehouses;
	cout <<"Input the number of workers:\n";
				cin  << workers;
				for(int i; i < workers; i++){
					cout<<"Insert ID of"<<i<<"worker: \n";
					int id;
					cin<< id;
					cout<<"Insert processing time of"<<i<<"worker: \n";
					int pr_time;
					cin<< pr_time;
					cout<<"Insert the type of QUEUE of"<<i<<"worker: \n";
					string queue;
					cin<< queue;
					cout<<"Recipients will be added later, because at first you need to create them!\n";
					std::map<BasicElement*, double > list;

					if(queue == QUEUE_TYPE::FIFO)
						workers.push_back( Worker(id, Type::Worker, pr_time, QUEUE_TYPE::FIFO, list ));
					else
						workers.push_back( Worker(id, Type::Worker, pr_time, QUEUE_TYPE::LIFO, list ));
					cout<<" Worker created!"<<endl;


				}

				cout <<"Input the number of storehouses:\n";
				cin  << storehouses;
				for(int i; i < storehouses; i++){
					cout<<"Insert ID of"<<i<<"storehouse: \n";
					int id;
					cin<< id;
					cout<< "At the begin Storehouse is always empty!\n";
					std::vector< Product > pr_list;
					storehouses.push_back( Storehouse(id, Type::Storehouse, pr_list) );
					cout<<" Storehouse created!"<<endl;

				}

				cout <<"Input the number of ramps:\n";
				cin  << ramps;
				for(int i; i < ramps; i++){
					cout<<"Insert ID of"<<i<<"ramp: \n";
					int id;
					cin<< id;
					cout<<"Insert sending frequency of"<<i<<"ramp: \n";
					int send_freq;
					cin<< send_freq;
					cout<<"Recipients will be added later, because at first you need to create them!\n";
					ramps.push_back( Ramp(id, Type::Ramp, send_freq ));
					cout<<"Ramp created!"<<endl;
				}

				cout<<"Now its time to add recipients."<<endl;

				for( auto iter = workers.begin(); iter!= workers.end(); iter++){
					int count = 0;

					cout<<"Worker #"<<(*iter).get_id()<<endl;
					cout<<"Choose the type:"<<endl;
					cout<<"1) Worker    2) Storehouse"<<endl;

					int type;
					cin>> type;
					if( type == 1){

						cout<<"Insert the probability of choosing: "<<endl;
						double probability;
						cin>> probability;
						cout<<"Insert the ID: \n";
						int id;
						cin>> id;
						for(auto iter2 = workers.begin(); iter2!= workers.end(); iter2++){

							if(id == workers[count].get_id())
								cout<<"The same worker cannot be sender and receiver in the same time!\n";

							else if( id == (*iter2).get_id() )
							{
								(*iter).addRecipient( *iter2, probability);
								cout<<"Recipient added!\n";
								break;
							}
						}

					}

					else if( type == 2){

						cout<<"Insert the probability of choosing: "<<endl;
						double probability;
						cin>> probability;
						cout<<"Insert the ID: \n";
						int id;
						cin>> id;
						for(auto iter2 = storehouses.begin(); iter2!= storehouses.end(); iter2++){

							 if( id == (*iter2).get_id() )
							{
								(*iter).addRecipient( *iter2, probability);
								cout<<"Recipient added!\n";
								break;
							}
						}
					}
					else if( type != 1 && type != 2 )
						cout<<"Check if your choice was 1 or 2"<<endl;

					count++;
					}

				for( auto iter = ramps.begin(); iter!= ramps.end(); iter++){


						cout<<"Ramp #"<<(*iter).get_id()<<endl;
						cout<<"Product cannot reach the storehouse straight away so you can add only workers."<<endl;


						cout<<"Insert the probability of choosing: "<<endl;

						double probability;
						cin>> probability;

						cout<<"Insert the ID: \n";

						int id;
						cin>> id;

						for(auto iter2 = workers.begin(); iter2!= workers.end(); iter2++){

								if( id == (*iter2).get_id() )
								{
									(*iter).addRecipient( *iter2, probability);
									cout<<"Recipient added!\n";
									break;
								}
						}


			}
					Network NETWORK1(workers, storehouses, ramps);
					cout<<"Your network was created!"<<endl;
}

//



//mockowanie co to std function ogarnij se
