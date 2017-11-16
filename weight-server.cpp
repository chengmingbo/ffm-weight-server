#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <memory>
#include <cmath>
#include <stdexcept>
#include <vector>
#include <cstdlib>

#include "ffm.h"
#include "httpcpp.h"

using namespace std;
using namespace ffm;

const string MODEL_PATH = "data/training.model";
ffm_model MODEL = ffm_load_model(MODEL_PATH);

void set_node(const string& item, ffm_node& N){
	istringstream iss(item);
	string sf, sj, sv;
	getline(iss, sf, ':');
	getline(iss, sj, ':');
	getline(iss, sv, ':');
	N.f = atoi(sf.c_str());
	N.j = atoi(sj.c_str());
	N.v = atoi(sv.c_str());
}

void pack_sample(const string& data, vector<ffm_node>& fs){
	istringstream iss(data);
	vector<string> items;
	string item;
	while(iss>>item){
		items.push_back(item);
	}
	for(size_t i=1; i<items.size(); ++i){
		ffm_node N;
		set_node(items[i], N);	
		fs.push_back(N);
	}
} 

// client: curl "http://127.0.0.1:8850/b/10/" -d "abcxyz"
class HttpRequestHandlerW : public HttpRequestHandler {
	//private:
    public:
        void post(HttpRequest* const request, const vector<string>& args) {
            cout << "-----------------------------------" << endl;
            cout << "Handler W receives:" << endl;
            cout << "method: " << request->get_method() << endl;
            cout << "path  : " << request->get_path() << endl;
            cout << "body  : " << request->get_body() << endl;
			vector<ffm_node> fs;
			pack_sample(request->get_body(), fs);
			string out;
			ffm_weights(fs.data(), fs.data()+fs.size(), MODEL, out);
			cout<<ffm_predict(fs.data(), fs.data()+fs.size(), MODEL)<<endl;
            reply(request, 200, out);
        }
};

int main(int argc, char **argv) {
#if 1
	//MODEL = ffm_load_model(MODEL_PATH);
	if(argc != 2)
	{
		cout<<"Wrong Parameters, run as: ./weight_server [port]"<<endl;
		exit(1);
	}
	istringstream iss(argv[1]);
	//cout<<"arg 2"<<argv[1]<<endl<<endl;
	int port;
	iss>>port;

    AsyncHttpServer* server = new AsyncHttpServer(port);
	HttpRequestHandlerW* handlerW = new HttpRequestHandlerW();
	server->add_handler("/", handlerW);
	cout<<"Serve on port: "<<port<<endl;
	IOLoop::instance()->start();
#endif
    return 0;
}
