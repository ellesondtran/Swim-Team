//Elleson Tran
//Roberts
//Swim Team Program
//Program to help them maintain a report of swimmer’s names, events, and times.
//FINAL


#include<iostream>
#include<string>
#include<fstream>
#include<vector>

using namespace std;

const int NUM_TEAM_MEMBERS=10;
const int WID=10;

struct Swimmer{
  string lastName;
  string firstName;
  string event;
  double minutes;
};

bool loadTeamFromFile(vector<Swimmer> &team)
{
    ifstream infile("swimteam.txt");
    if(infile.fail())
    {
        cout<<"Error opening file."<<endl;
        return false;
    }
    else
    {
        int i=0;
        while(infile>>team[i].lastName)
        {
            infile>>team[i].firstName;
            infile>>team[i].event;
            infile>>team[i].minutes;
            i++;
        }
        infile.close();
        return true;
    }
}

//prints the players and what their time is in the users chosen event
void reportOnEvent(vector<Swimmer> team, string eventChosen){
  cout<<endl<<"Team Members Competing in "<<eventChosen<<":";
  cout<<endl<<"   Last      First    Minutes";
  cout<<endl<<" --------  --------  --------";

  for(int x = 0; x < team.size(); x++){//goes through each player in the team
    if(team[x].event == eventChosen){//if one of the players has the chosen event
      cout<<endl;//starts a line
      cout<<"  "<<team[x].lastName;

      for(int i = 0; i < (11 - team[x].lastName.length()); i++){
        cout<<" ";
      }
      cout<<team[x].firstName;

       for(int i = 0; i < (12 - team[x].firstName.length()); i++){
        cout<<" ";
      }
      cout<<team[x].minutes;
      //adds everything ^^ onto this one line
    }
  }
  cout<<endl<<endl; //just a spacer
}

//function that finds the fastest player within the chosen event
Swimmer findFastest(vector<Swimmer> team, string eventChosen){
  Swimmer fastestSwimmer;//what we are returning

  vector<int> playersInEvent;
  //for loop to add all the players into a vector in THIS event
  //purpose: to only search through the highest time within this vector
  for(int x = 0; x < team.size(); x++){//goes through each player
    if(team[x].event == eventChosen){//if one of the players has the chosen event
     playersInEvent.push_back(x);//adds each player to this new vector to compare which is the fastest
    }
  }

  double currentSwimmer = team[playersInEvent[0]].minutes;//the first player in the team thats in the event's time to compare
  //loop that searches through the people in the event to compare whos the fastest
  for(int x = 0; x < playersInEvent.size(); x++){
    if(currentSwimmer >= team[playersInEvent[x]].minutes){//if the next person has a better time, change the current fastest to the current player
      currentSwimmer = team[playersInEvent[x]].minutes;//changes the current fastest to the current player
      //adds all the info of the current fastest to the struct
      fastestSwimmer.lastName = team[playersInEvent[x]].lastName;
      fastestSwimmer.firstName = team[playersInEvent[x]].firstName;
      fastestSwimmer.event = team[playersInEvent[x]].event;
      fastestSwimmer.minutes = team[playersInEvent[x]].minutes;
    }
  }
          
  return fastestSwimmer;
}

//function that outputs who should swim in the chosen event
void whoShouldSwim(vector<Swimmer> team){
  bool eventFound = false;
  string eventChosen;
  cout<<endl<<"Enter event to find current fastest swimmer:";
  cin>>eventChosen;


  //a loop that finds the chosen event in the total events
  for(int x = 0; x < team.size(); x++){//goes through each player
    if(eventChosen == team[x].event){//if the chosen event is in the total events it returns true
      eventFound = true;
    }
  }

  if(eventFound == true){//if the event is found
    Swimmer fastest = findFastest(team, eventChosen); //makes a struct of the fastest player
    cout<<fastest.firstName<<" "<<fastest.lastName<<" "<<fastest.minutes<<endl;
  }

  if(eventFound == false){//if the event is not found
    cout<<"No such event exists 404"<<endl;
  }
}

void updateTime(vector<Swimmer> team){
  bool playerChosen = false;
  string updateSwimmer;
  cout<<endl<<"Enter last name of swimmer to update:";
  cin>>updateSwimmer;

  double newTime;
  cout<<endl<<"Input new time:";
  cin>>newTime;


  //a loop that finds the chosen player in the list of players
  for(int x = 0; x  < team.size(); x ++){//goes through each player
    if(updateSwimmer == team[x ].lastName){//if the chosen player is in the list of players it returns true
      playerChosen = true;
    }
  }


  //if the chosen player is found in the list of players
  if(playerChosen == true){//if the player is found
    for(int x = 0; x  < team.size(); x ++){
      if(updateSwimmer == team[x ].lastName){
        team[x].minutes = newTime;//updates the time
        cout<<"Update complete."<<endl;
      }
    }
  }
  
  if(playerChosen == false){//if the player is not found
    cout<<"404-Swimmer not found.";
  }
  
}


int main()
{


    vector<Swimmer> team(NUM_TEAM_MEMBERS);
    if(loadTeamFromFile(team))
    {
        int choice;
        string eventChosen;
        do{ 
            cout<<endl;
            cout<<"1 - See Roster and Best Times"<<endl;
            cout<<"2 - Find Who Should Compete in an Event"<<endl;
            cout<<"3 - Update Best Time for Swimmer"<<endl;
            cout<<"4 - Quit"<<endl;
            cin>>choice;
            
           if(choice == 1){
             cout<<endl<<"What event? ";
             cin>>eventChosen;
             reportOnEvent(team, eventChosen);

           }

           if(choice == 2){
            whoShouldSwim(team);

           }

           if(choice == 3){
            updateTime(team);
            

           }
            
        }while(choice!=4);
        
        
        
    }
    return 0;
}