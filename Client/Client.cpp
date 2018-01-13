// Raspberry Pi
// Soure: http://www.cplusplus.com/forum/unices/76180/

// To compile: g++ -o Client Client.cpp -std=c++11
// That last part makes to_string work

#include<iostream>
#include<arpa/inet.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<string>
#include<stdlib.h>
using namespace std;

// Private
int sockfd;
struct sockaddr_in serv;

void setupSendSocket();
void send(string& msg);

int main() {
 setupSendSocket();

 /*cout << "\nEnter message to send:\n";
 string msg;
 cin >> msg;
 send(msg);*/

 int centerX[] = {562, 73, 147};
 int centerY[] = {412, 2, 90};
 int width[] = {365, 190, 42};
 int height[] = {52, 202, 73};
 int area[] = {1095, 1159, 2006};

 int numContours = sizeof(area)/sizeof(area[0]);
 string msg = "";
 for (int i = 0; i < numContours; i++) {
  
  msg  += to_string(centerX[i]) + "," 
	+ to_string(centerY[i]) + "," 
	+ to_string(width[i]) + "," 
	+ to_string(height[i]) + "," 
	+ to_string(area[i]);
  if (i < numContours - 1) { // Not the last contour
   msg += ";";
  }
  
 }
 send(msg);
}

void send(string& msg) {
 sendto(sockfd, msg.c_str(), msg.size(), 0, (struct sockaddr*) &serv, sizeof(serv));
}

void setupSendSocket() {
 sockfd = socket(AF_INET,SOCK_DGRAM,0);
 
 serv.sin_family = AF_INET;
 serv.sin_port = htons(53000);
 serv.sin_addr.s_addr = inet_addr("127.0.0.1");
}