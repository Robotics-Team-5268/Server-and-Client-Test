// RoboRIO
// Source: http://www.cplusplus.com/forum/unices/76180/

// Message order: CenterX, CenterY, Width, Height, Area
// Format: Variables separated by commas, contours separated by semicolons
// Ex: 1X,1Y,1W,1H,1A;2X,2Y,2W,2H,2A;3X,3Y...
// If you want to add more variables, add them to the end (after area)

#include<iostream>
#include<sstream>
#include<vector>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

// Private
int sockfd;
char buffer[256]; // Don't access this outside of receive

void setupReceiveSocket();
string receive();
vector<string> split(string str, string delimiter);
int strToInt(string str);

int main() {
  setupReceiveSocket();

  while (true) {
    string msg = receive();
    cout << "\n Message received: " << msg << endl;

    vector<int> centerX, centerY, width, height, area;

    vector<string> contours = split(msg, ";");
    for (int i = 0; i < contours.size(); i++) {
      cout << "Contour: " << contours[i] << endl;

      // centerX, centerY, etc, for the current contour
      vector<string> properties = split(contours[i], ",");

      for (int j = 0; j < properties.size(); j++) {
        cout << "  Property: " << properties[j] << endl;
// TODO: convert the properrties to ints and store in their respective vectors
      }

      centerX.push_back(strToInt(properties[0]));
      centerY.push_back(strToInt(properties[1]));
      width.push_back(strToInt(properties[2]));
      height.push_back(strToInt(properties[3]));
      area.push_back(strToInt(properties[4]));
    }

    for (int k = 0; k < area.size(); k++) {
      cout << "   Area: " << area[k] << endl;
    }
  }
}

vector<string> split(string str, string delimiter) {
    vector<string>result;
    while (str.size()) {
        int index = str.find(delimiter);
        if (index != string::npos) {
            result.push_back(str.substr(0, index));
            str = str.substr(index + delimiter.size());
        } else {
            result.push_back(str);
            //str = "";
            break;
        }
    }
    return result;
}

int strToInt(string str) {
  stringstream stream(str);
  int num = 0;
  stream >> num;
  return num;
}

string receive() {
 int rc = recv(sockfd, buffer, sizeof(buffer), 0);
 if (rc < 0) cout << "ERROR READING FROM SOCKET" << endl;
 return string(buffer);
}

void setupReceiveSocket() {
 sockfd = socket(AF_INET,SOCK_DGRAM,0);

 struct sockaddr_in serv;
 serv.sin_family = AF_INET;
 serv.sin_port = htons(53000);
 serv.sin_addr.s_addr = inet_addr("127.0.0.1");

 // Drake added this line
 bind(sockfd, (const sockaddr*) &serv, sizeof(serv));

 cout << "\nGoing to receive...\n";
}

