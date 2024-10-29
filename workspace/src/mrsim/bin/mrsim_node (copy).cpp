#include <ros/ros.h>  
 
#include <sys/time.h>
#include <thread>
#include <chrono>
#include <cmath>

#include "types.h"
#include "world.h"
#include "robot.h"
#include "lidar.h"
#include "utils.h"
#include <jsoncpp/json/json.h> 

// Funzione per leggere il file di configurazione JSON
Json::Value readJson(string in_path) {
    cout << "Configuration file path:" << in_path << endl;
    Json::Value root; // Oggetto per tenere il contenuto del file JSON parsato
    Json::CharReaderBuilder readerBuilder; // Lettore per il file JSON

    ifstream file(in_path, ifstream::binary); // Apertura del file in modalità binaria
    cout << in_path << endl;
    string errs; // Stringa per memorizzare eventuali errori di parsing

    if (!file.is_open()) {
        cerr << "Could not open the file: " << in_path << endl;
        return Json::Value();
    }
    // Parsing del file JSON
    bool parsingSuccessful = Json::parseFromStream(readerBuilder, file, &root, &errs);
    if (!parsingSuccessful) {
        cout << "Failed to parse JSON file: " << errs << endl;
        return Json::Value();
    }

    file.close();
    return root;
}


int main(int argc, char** argv) {

      // Controlla se è stato passato un argomento per il file config
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <config_file_name>" << endl;
        return 1;
    }

      ros::init(argc, argv, "mrsim_node");
  ros::NodeHandle nh("/");


// Specifica manualmente il percorso della directory dei config e delle mappe
    string config_directory = "/home/lattinone/Desktop/RP_project_2024/config/";
    string config_path = config_directory + argv[1];

    // Carica il file di configurazione
    Json::Value root = readJson(config_path);  // Assicurati che `readJson` sia definito
    string map = root["map"].asString();
    cout << "Map -> " << map << endl;

    // Costruisci il percorso per l'immagine della mappa
    string image_path = "/home/lattinone/Desktop/RP_project_2024/map/" + map;

    // Crea una nuova istanza di World e il puntatore condiviso
    World world(42); 
    WorldPointer world_pointer(&world, [](World*){ });  // Funzione lambda

    // Carica l'immagine della mappa
    world.loadFromImage(image_path);
  
  //simulation parameters
  float delay = 0.58;
  ros::Rate loop_rate(10);

  cout << "Running primary node" << endl;

  while (ros::ok()) {

    //world.draw();
    int k = cv::waitKey(1);
    if (k == 27) break;

    ros::spinOnce();
    world.timeTick(delay);
    this_thread::sleep_for(chrono::milliseconds(10)); // sleep for x milliseconds

  }

  cv::destroyAllWindows();
  return 0;
} 
