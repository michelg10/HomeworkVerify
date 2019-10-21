#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <set>
#include "openhelper.hpp"
#include "cores.hpp"
#include "gpphelper.hpp"
#include "handclap.hpp"
#include "highonlife.hpp"
#include "acsound.hpp"
#include "soundkill.hpp"
#include "irrlib.hpp"
#include "soundsetup.hpp"
#include "convtool.hpp"
using namespace std;
typedef long long ll;
typedef long double ld;
struct hw {
    string id;
    ll score;
    string name;
    string date;
};
string safespace(string s) {
    stringstream ss;
    for (ll i=0;i<s.length();i++)
        s[i]==' ' ? ss<<"\\"<<" " : ss<<s[i];
    string rturn;
    getline(ss,rturn);
    return rturn;
}
bool readf(vector<string>&s,string path) {
    s.clear();
    ifstream in(path);
    if (in.good()) {
        while (!in.eof()) {
            string tmp;
            getline(in,tmp);
            s.push_back(tmp);
        }
    } else {
        return 0;
    }
    return 1;
}
string username = getlogin(),db;
string hv="1";
void install(bool comple) {
    cout<<"Installing neccessary components... ";
    if (comple) {
        system(("mkdir "+safespace(db)).c_str());
        system(("mkdir "+safespace(db+"tmp/")).c_str());
    }
    //Install cores(39824),gpphelper(48608),openhelper(129632)y,handclap(1818048),highonlife(1160862),acsound(94848),soundkill(31840),libirrklang.dylib(1975552),soundsetup(114720),convtool(109344)
    const unsigned char* tmp=cores();
    ofstream installer(db+"cores",ios::binary);
    for (ll i=0;i<39824;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"cores")).c_str());
    
    installer.open(db+"gpphelper",ios::binary);
    tmp = gpphelper();
    for (ll i=0;i<48608;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"gpphelper")).c_str());
    
    installer.open(db+"openhelper",ios::binary);
    tmp = openhelper();
    for (ll i=0;i<129632;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"openhelper")).c_str());
    
    installer.open(db+"U2PQX4CHY3SOJ31E.wav",ios::binary);
    tmp=handclap();
    for (ll i=0;i<1818048;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"D63SR3HEXSB6JX1N.wav",ios::binary);
    tmp=highonlife();
    for (ll i=0;i<1160862;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"acsound",ios::binary);
    tmp = acsound();
    for (ll i=0;i<94848;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"acsound")).c_str());
    
    installer.open(db+"soundkill",ios::binary);
    tmp = soundkill();
    for (ll i=0;i<31840;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"soundkill")).c_str());
    
    installer.open(db+"soundsetup",ios::binary);
    tmp=soundsetup();
    for (ll i=0;i<114720;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"soundsetup")).c_str());
    
    installer.open(db+"libirrklang.dylib",ios::binary);
    tmp=irrlib();
    for (ll i=0;i<1975552;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"convtool",ios::binary);
    tmp=convtool();
    for (ll i=0;i<109344;i++) installer<<tmp[i];
    installer.close();
    system(("chmod 755 "+safespace(db+"convtool")).c_str());
    cout<<"done"<<endl;
}
string date() {
    time_t tmptime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string tmp = ctime(&tmptime);
    tmp.erase(tmp.size()-1,1);
    return tmp;
}
bool fcopy(string from,string to) {
    ifstream in(from);
    ofstream out(to);
    string s;
    if (in.good()&&out.good()) {
        out<<in.rdbuf();
    } else {
        in.close();
        out.close();
        return 1;
    }
    in.close();
    out.close();
    return 0;
}
string key = "FB384BE6E7009275";
string iv = "755CA3572C3FAC78";
string salt = "8C55A67258E39056";
string cmdenc = "openssl enc -aes-256-cbc -K "+key+" -iv "+iv+" -S "+salt;
ll srtmode,mltcore,rten,compcore,cor=0,incor=0,helperver;
bool cmp(hw const &a, hw const &b) {
    if (srtmode==1) return a.name<b.name;
    else if (srtmode==2) return a.name>b.name;
    else if (srtmode==3) return a.score<b.score;
    else if (srtmode==4) return a.score>b.score;
    else if (srtmode==5||srtmode==6) {
        struct tm tm1,tm2;
        strptime(a.date.c_str(),"%a %b %d %T %Y",&tm1);
        strptime(b.date.c_str(),"%a %b %d %T %Y",&tm2);
        time_t t1,t2;
        t1=mktime(&tm1);
        t2=mktime(&tm2);
        if (difftime(t1,t2)>0) {
            if (srtmode==5) return false;
            else return true;
        } else
            if (srtmode==6) return true;
            else return false;
    }
    return 0;
}
vector<hw>data;
struct egg {
    string ach, trig, msg;
};
vector<egg>easter;
ll sound = 0;
map<string,ll*>intcont;
map<string,vector<string>>structref;
struct soundlog {
    string fname,sname;
};
ll autosave;
bool secret[100];
vector<soundlog>audio;
vector<ll>selaud;
void savedata() {
    ofstream out(db+"contents.dwt");
    out<<"VERS"<<endl<<"1.3"<<endl<<"ACH"<<endl;
    for (ll i=0;i<easter.size();i++) out<<secret[i];
    out<<endl<<"AUTOSAVE"<<endl<<autosave<<endl<<"SOUND"<<endl<<sound<<endl<<"CORRECT"<<endl<<cor<<endl<<"INCORRECT"<<endl<<incor<<endl<<"SORT"<<endl<<srtmode<<endl<<"MULTICORE"<<endl<<mltcore<<endl<<"RETENTION"<<endl<<rten<<endl<<"HELPERVER"<<endl<<helperver<<endl<<"STARTSTRUCT"<<endl<<"Hwf"<<endl<<"FNAME"<<endl<<"SCORE"<<endl<<"NAME"<<endl<<"DATE"<<endl<<"ENDSTRUCT"<<endl<<"STARTSTRUCT"<<endl<<"Song"<<endl<<"FNAME"<<endl<<"SNAME"<<endl<<"ENDSTRUCT"<<endl<<"STARTSTRUCT"<<endl<<"selaud"<<endl<<"AUDID"<<endl<<"ENDSTRUCT"<<endl<<"START"<<endl<<"Song"<<endl;
    for (ll i=0;i<audio.size();i++) out<<audio[i].fname<<endl<<audio[i].sname<<endl;
    out<<"END"<<endl<<"Song"<<endl<<"START"<<endl<<"Hwf";
    for (ll i=0;i<data.size();i++) out<<endl<<data[i].id<<endl<<data[i].score<<endl<<data[i].name<<endl<<data[i].date;
    out<<endl<<"END"<<endl<<"Hwf"<<endl<<"START"<<endl<<"selaud";
    for (ll i=0;i<selaud.size();i++) out<<endl<<selaud[i];
    out<<endl<<"END"<<endl<<"selaud";
}
void nml(string &s) {
    if (s!="") {
        for (ll i=0;i<s.size()-1;i++) {
            if (s[i]=='\\'&&s[i+1]==' ') {
                s.erase(i,2);
                s.insert(i," ");
            }
        }
        if (s[s.size()-1]==' ') s.erase(s.size()-1);
    }
}
int main() {
    intcont["SOUND"]=&sound;
    intcont["CORRECT"]=&cor;
    intcont["INCORRECT"]=&incor;
    intcont["SORT"]=&srtmode;
    intcont["MULTICORE"]=&mltcore;
    intcont["RETENTION"]=&rten;
    intcont["AUTOSAVE"]=&autosave;
    intcont["HELPERVER"]=&helperver;
    ll const helpertar=1;
    //Defaults
    rten=6;
    mltcore=1;
    srtmode=1;
    incor=cor=0;
    sound=0;
    autosave=1;
    audio.push_back({"U2PQX4CHY3SOJ31E","Handclap"});
    audio.push_back({"D63SR3HEXSB6JX1N","High on Life"});
    selaud.push_back(0);
    selaud.push_back(1);
    if (true) /*Easter eggs!*/ {
        easter.push_back({"The Player's Poem","player","Roses are red, \nViolets are blue.\nI said I loved you,\nYou thought that was true.\nWell guess what player?\nYou just got played too."});
        easter.push_back({"?ldroW","hello world","!dlroW olleH"});
        easter.push_back({"Secrets...","easter egg","Secrets have been hidden..."});
        easter.push_back({"Demons","horn","Try not to get me wet"});
        easter.push_back({"ME!","credits","HOMEWORK SYSTEM MADE BY MICHEL!"});
        easter.push_back({"Ding!","tiger","Buy the Tiger Microwave and the Ding Radio Emitter!"});
        easter.push_back({"Always On!","eric","That man must be turned off"});
        easter.push_back({"You ded!","msyan","For Ms.Yan..."});
        easter.push_back({"Respects","f","You've paid your respects."});
        easter.push_back({"You kiss your mother with that mouth?","fack","If you see kay, why oh you?"});
        easter.push_back({"My name!","michel","That's me!"});
        easter.push_back({"Language of the future...","c++","That's the language!"});
        easter.push_back({"MINE! MINE!","lucy","Do your homework... and come talk to me. Tell me that I sent you"});
        easter.push_back({"Cat Spring","cucumber","Cats like them... I think"});
        easter.push_back({"Best subject","math","Awesome Math!"});
        easter.push_back({"Slap his thigh!","lightning","Lightning and the thunder..."});
        easter.push_back({"I'll do you every day.","homework","Oh yeah..."});
        easter.push_back({"Goose math!","3.16","Pi IS 3.16!"});
        easter.push_back({"Escaping red blood cells!","Bleed","Rudolph's running nose..."});
        easter.push_back({"The mythical creature","unicorn","So horny..."});
        easter.push_back({"Greatest club of all time","c++ programming","Yee!"});
    }
    //openssl enc -aes-256-cbc -K FB384BE6E7009275 -iv 755CA3572C3FAC78 -S 8C55A67258E39056
    system("clear");
    map<ll,char>randname;
    for (ll i=48;i<=57;i++) {
        randname[i-48]=i;
    }
    for (ll i=65;i<=90;i++) {
        randname[i-55]=i;
    }
    srand(time(0));
    ifstream dbtest("/Users/"+username);
    if (!dbtest.good()) {
        dbtest.close();
        bool isdev=true;
        while (true) {
            if (isdev) {
                cout<<"Automatic directory detection failed. Trying dev legitmichel777..."<<endl;
                username="legitmichel777";
                isdev=false;
            } else {
                cout<<"Automatic directory detection failed. Please enter your username."<<endl;
                getline(cin,username);
            }
            dbtest.open("/Users/"+username);
            if (dbtest.good()) {dbtest.close();break;}
            dbtest.close();
            while (true) {
                cout<<"Error! Please make sure you entered the right user and is on a supported system(macOS). Please enter your username again."<<endl;
                getline(cin,username);
                dbtest.open("/Users/"+username);
                if (dbtest.good()) {dbtest.close();break;}
                dbtest.close();
            }
            break;
        }
    }
    dbtest.close();
    db = "/Users/"+username+"/Library/Containers/com.mclm7.homework/";
    dbtest.open(db+"contents.man");
    bool freshins=false;
    if (!dbtest.good()) {
        freshins=true;
        install(1);
        ofstream mancreate(db+"contents.man");
        mancreate.close();
    }
    dbtest.close();
    //1.3 ONLY
    /* **************************************************** */
    ifstream convtest(db+"contents.man");
    if (convtest.good()) {
        convtest.close();
        convtest.open(db+"contents.dwt");
        if (convtest.good()) {
            convtest.close();
        } else {
            convtest.close();
            cout<<"v1.3 of Homework introduces a new storage format, DWT. DWT allows for seamless compatibility between versions of Homework. We'll now convert your old MAN file to DWT!"<<endl;
            system(safespace(db+"convtool").c_str());
            cout<<"Please reopen Homework."<<endl;
            return 0;
        }
        
    } else convtest.close();
    /* **************************************************** */
    //1.3 ONLY
    ifstream in(db+"contents.dwt");
    bool impissue=false;
    ofstream rmsil(db+"tmp/sl.silent");
    rmsil<<"SILENCE!";
    rmsil.close();
    system(("rm -r "+db+"tmp/*").c_str());
    for (ll i=0;i<easter.size();i++) secret[i]=0;
    if (in.good()&&!freshins) {
        vector<string>contentsf;
        while (!in.eof()) {
            string s;
            getline(in,s);
            contentsf.push_back(s);
        }
        for (ll i=0;i<contentsf.size();i++) {
            string finkey=contentsf[i];
            if (finkey=="START") {
                bool startgood=false;
                string stname=contentsf[++i];
                for (ll j=i;j<contentsf.size()-1;j++) {
                    if (contentsf[j]=="END"&&contentsf[j+1]==stname) {
                        startgood=true;
                        break;
                    } else if (contentsf[j]=="START") break;
                    else if (contentsf[j]=="END") break;
                }
                if (startgood) {
                    ll cur=0;
                    ll ttl = structref[stname].size();
                    if (ttl) {
                        if (stname=="Hwf") {
                            hw curwt=(hw){"",0,"",""};
                            //ID,NAME,SCORE,DATE
                            while (contentsf[++i]!="END") {
                                if (cur==ttl) {
                                    data.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="FNAME") curwt.id=contentsf[i];
                                else if (structref[stname][cur]=="SCORE") curwt.score=atoll(contentsf[i].c_str());
                                else if (structref[stname][cur]=="NAME") curwt.name=contentsf[i];
                                else if (structref[stname][cur]=="DATE") curwt.date=contentsf[i];
                                cur++;
                            }
                            if (cur==ttl) data.push_back(curwt);
                        } else if (stname=="Song") {
                            audio.clear();
                            soundlog curwt=(soundlog){"",""};
                            //fname, sname
                            while (contentsf[++i]!="END") {
                                if (cur==ttl) {
                                    audio.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="FNAME") curwt.fname=contentsf[i];
                                else if (structref[stname][cur]=="SNAME") curwt.sname=contentsf[i];
                                cur++;
                            }
                            if (cur==ttl) audio.push_back(curwt);
                        } else if (stname=="selaud") {
                            selaud.clear();
                            ll curwt;
                            while (contentsf[++i]!="END") {
                                if (cur==ttl) {
                                    selaud.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="AUDID") curwt=atoll(contentsf[i].c_str());
                                cur++;
                            }
                            if (cur==ttl) selaud.push_back(curwt);
                        } else while (contentsf[++i]!="END");
                    }
                } else impissue=true;
            } else if (finkey=="STARTSTRUCT") {
                bool structgood=false;
                for (ll j=i+1;j<contentsf.size();j++) {
                    if (contentsf[j]=="ENDSTRUCT") {
                        structgood=true; //Ending found
                        break;
                    } else if (contentsf[j]=="STARTSTRUCT") break; //No ending
                }
                if (structgood) {
                    string stuname=contentsf[++i];
                    while (contentsf[++i]!="ENDSTRUCT") {
                        structref[stuname].push_back(contentsf[i]);
                    }
                } else impissue=true;
            } else if (intcont[finkey]!=NULL) {
                *intcont[finkey]=atoll(contentsf[++i].c_str());
            }
        }
    }
    in.close();
    ofstream out(db+"db.txt");
    out<<db;
    out.close();
    if (helperver!=helpertar) {
        install(0);
        helperver=helpertar;
    }
    system((safespace(db+"cores")).c_str());
    in.open(db+"cores.txt");
    if (in.good()) {
        string corefin;
        in>>corefin;
        if (to_string(atoll(corefin.c_str()))==corefin) compcore=atoll(corefin.c_str());
        else cout<<"System information gathering failed."<<endl;
    } else cout<<"System information gathering failed."<<endl;
    for (ll i=0;i<data.size();i++) {
        ifstream bundltest(db+data[i].id);
        if (!bundltest.good()) {
            data.erase(data.begin()+i);
            i--;
        }
    }
    ll timethres = 0;
    if (rten!=6) {
        if (rten==1) timethres=7;
        if (rten==2) timethres=14;
        if (rten==3) timethres=30;
        if (rten==4) timethres=60;
        if (rten==5) timethres=360;
        timethres*=24*60*60;
        for (ll i=0;i<data.size();i++) {
            struct tm convt;
            strptime(data[i].date.c_str(),"%a %b %d %T %Y",&convt);
            time_t convtt;
            convtt=mktime(&convt);
            if (difftime(chrono::system_clock::to_time_t(chrono::system_clock::now()),convtt)>timethres) {
                data.erase(data.begin()+i);
                i--;
            }
        }
    }
    bool asdisabled=false;
    if (impissue&&autosave) {
        cout<<"Autosave has been disabled."<<endl;
        autosave=0;
        asdisabled=true;
    }
    for (ll i=selaud.size()-1;i>=0;i--) {
        if (selaud[i]>=audio.size()) selaud.erase(selaud.begin()+i);
        i--;
    }
    while (true) {
        string target;
        bool vq = false;
        if (impissue) {
            cout<<"!!!Contents file corrupted. Press [F] to force quit. This will prevent further corruption of the file"<<endl<<"You will lose all unsaved data. ";
            if (asdisabled&&!autosave) {
                cout<<"Autosave has been disabled."<<endl;
            } else cout<<endl;
        }
        cout<<"Welcome to LM7's Homework(v1.3). Please select an action."<<endl<<"[1]New assignment"<<endl<<"[2]Achievements"<<endl<<"[3]Settings"<<endl<<"[4]Quit"<<endl;
        sort(data.begin(),data.end(),cmp);
        bool incompl=false;
        for (ll i=0;i<data.size();i++) {
            if (data[i].score<100) {
                incompl=true;
            }
        }
        ll outcnt = 5;
        vector<ll>hwpoint;
        if (incompl) {
            cout<<"--------"<<endl<<"Incomplete Assignments:"<<endl;
            for (ll i=0;i<data.size();i++) {
                if (data[i].score<100) {
                    cout<<"["<<outcnt++<<"]"<<data[i].name<<":"<<data[i].score<<endl;
                    hwpoint.push_back(i);
                }
            }
        }
        incompl = false;
        for (ll i=0;i<data.size();i++) {
            if (data[i].score==100) {
                incompl=true;
            }
        }
        if (incompl) {
            cout<<"--------"<<endl<<"Completed assignments:"<<endl;
            for (ll i=0;i<data.size();i++) {
                if (data[i].score==100) {
                    cout<<"["<<outcnt++<<"]"<<data[i].name<<endl;
                    hwpoint.push_back(i);
                }
            }
        }
        string homeans;
        getline(cin,homeans);
        system("clear");
        if (homeans=="1") {
            cout<<"Enter the path of the package."<<endl;
            string pkgpth;
            getline(cin,pkgpth);
            nml(pkgpth);
            ifstream pkgverf(pkgpth);
            if (pkgverf.good()) {
                bool idfile=false;
                if (pkgpth.size()>=6) {
                    if (pkgpth.substr(pkgpth.size()-6,6)==".hwpkg") {
                        idfile=true;
                        //COPY OVER TO TMP
                        string newname="";
                        for (ll i=0;i<16;i++) {
                            newname+=randname[rand()%36];
                        }
                        fcopy(pkgpth, db+"tmp/"+newname);
                        //UNZIP
                        system(("unzip -o -qq "+safespace(db+"tmp/"+newname)+" -d "+safespace(db+"tmp/"+newname+'u')).c_str());
                        //Read contents file
                        vector<string>pkgcontent;
                        ifstream pkgcont(db+"tmp/"+newname+"u/contents.man");
                        if (pkgcont.good()) {
                            while (!pkgcont.eof()) {
                                string pkgconttmp;
                                getline(pkgcont,pkgconttmp);
                                pkgcontent.push_back(pkgconttmp);
                            }
                            pkgcont.close();
                            for (ll i=0;i<pkgcontent.size();i++) {
                                string newnm="";
                                ifstream pkgptverf(db+"tmp/"+newname+"u/"+pkgcontent[i]);
                                if (pkgptverf.good()) {
                                    string newnm="";
                                    for (ll i=0;i<16;i++) newnm+=randname[rand()%36];
                                    fcopy(db+"tmp/"+newname+"u/"+pkgcontent[i],db+newnm);
                                    string pkgpeeknm;
                                    //PEEK AT PACKAGE TO LOOK AT NAME
                                    string denccmd = "openssl aes-256-cbc -d -K "+key+" -iv "+iv+" -S "+salt+" -in "+safespace(db+newnm)+" -out "+safespace(db+"tmp/"+newnm);
                                    system(denccmd.c_str());
                                    //OPEN EM
                                    system(("unzip -o -qq "+safespace(db+"tmp/"+newnm)+" -d "+safespace(db+"tmp/"+newnm+'e')).c_str());
                                    ifstream hwfnmrd(db+"tmp/"+newnm+"e/title.txt");
                                    string hwfnm;
                                    getline(hwfnmrd,hwfnm);
                                    hwfnmrd.close();
                                    data.push_back({newnm,0,hwfnm,date()});
                                } else cout<<"Missing Homework file!"<<endl;
                            }
                        } else {
                            cout<<"Unexpected error:Missing contents file!"<<endl;
                            pkgcont.close();
                        }
                        system(("rm -r "+safespace(db+"tmp/*")).c_str());
                        if (autosave) savedata();
                        continue;
                    }
                }
                if (pkgpth.size()>=3) {
                    if (pkgpth.substr(pkgpth.size()-3,3)==".hw") {
                        idfile=true;
                    }
                }
                if (!idfile) {
                    cout<<"Unidentified file. Do not tamper with file extensions! Homework will take this as a Homework File."<<endl;
                }
                //Move it
                string newname="";
                for (ll i=0;i<16;i++) {
                    newname+=randname[rand()%36];
                }
                fcopy(pkgpth,db+newname);
                string nm="Undefined";
                data.push_back({newname,0,nm,date()});
                //ID SCORE NAME DATE
                homeans = to_string(data.size()+4);
                target = newname;
                vq=true;
                hwpoint.push_back(data.size()-1);
            } else {
                cout<<"Error reading package."<<endl;
            }
        } else if (homeans=="2") {
            cout<<"Achievements"<<endl<<"--------"<<endl<<"Academic:"<<endl<<"Success!:";
            if (cor>=1) cout<<"Completed "<<cor<<"/1 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/1 correct tries"<<endl;
            cout<<"More!:";
            if (cor>=10) cout<<"Completed "<<cor<<"/10 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/10 correct tries"<<endl;
            cout<<"Unstoppable!:";
            if (cor>=100) cout<<"Completed "<<cor<<"/100 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/100 correct tries"<<endl;
            cout<<"Godlike!:";
            if (cor>=1000) cout<<"Completed "<<cor<<"/1000 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/1000 correct tries"<<endl;
            cout<<"You can try again:";
            if (incor>=1) cout<<incor<<"/1 incorrect tries"<<endl;
            else cout<<incor<<"/1 incorrect tries done"<<endl;
            cout<<"Get up!:";
            if (incor>=10) cout<<incor<<"/10 incorrect tries"<<endl;
            else cout<<incor<<"/10 incorrect tries done"<<endl;
            cout<<"Keep going!:";
            if (incor>=100) cout<<incor<<"/100 incorrect tries"<<endl;
            else cout<<incor<<"/100 incorrect tries done"<<endl;
            cout<<"Nearly there!:";
            if (incor>=1000) cout<<incor<<"/1000 incorrect tries"<<endl;
            else cout<<incor<<"/1000 incorrect tries done"<<endl;
            cout<<"--------"<<endl<<"Secrets:"<<endl;
            for (ll i=0;i<easter.size();i++) {
                cout<<easter[i].ach<<":";
                if (secret[i]) cout<<"Input \""<<easter[i].trig<<"\" into the main menu."<<endl;
                else cout<<"A secret is required"<<endl;
            }
            cout<<"--------"<<endl<<"Press enter to continue..."<<endl;
            cin.get();
            system("clear");
        } else if (homeans=="3") {
            while (true) {
                cout<<"Settings"<<endl<<"[1]Sort:";
                if (srtmode==1) cout<<"Alphabetically, increasing"<<endl;
                else if (srtmode==2) cout<<"Alphabetically, decreasing"<<endl;
                else if (srtmode==3) cout<<"Scores, increasing"<<endl;
                else if (srtmode==4) cout<<"Scores, decreasing"<<endl;
                else if (srtmode==5) cout<<"Date, increasing"<<endl;
                else if (srtmode==6) cout<<"Date, decreasing"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[2]Keep assignments for:";
                if (rten==1) cout<<"1 week"<<endl;
                else if (rten==2) cout<<"2 weeks"<<endl;
                else if (rten==3) cout<<"1 month"<<endl;
                else if (rten==4) cout<<"2 months"<<endl;
                else if (rten==5) cout<<"6 months"<<endl;
                else if (rten==6) cout<<"Forever"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[3]Multicore:";
                if (mltcore>1) cout<<mltcore<<" cores"<<endl;
                else if (mltcore) cout<<mltcore<<" core"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[4]Sound:";
                if (sound) {
                    if (selaud.size()==0) cout<<"No song selected"<<endl;
                    else if (audio.size()==selaud.size()) cout<<"All"<<endl;
                    else {
                        cout<<audio[selaud[0]].sname;
                        if (selaud.size()==2) cout<<" and "<<selaud.size()-1<<" other...";
                        else if (selaud.size()>=2) cout<<" and "<<selaud.size()-1<<" others...";
                        cout<<endl;
                    }
                }
                else cout<<"Disabled"<<endl;
                cout<<"[5]Autosave:";
                if (autosave) cout<<"Enabled"<<endl;
                else {
                    if (asdisabled) cout<<"Disabled due to import issue"<<endl;
                    else cout<<"Disabled"<<endl;
                }
                cout<<"[6]Exit Settings"<<endl;
                string setans;
                getline(cin,setans);
                if (setans=="1") {
                    cout<<"Select sort mode:"<<endl<<"[1]Alphabetically, increasing"<<endl<<"[2]Alphabetically, decreasing"<<endl<<"[3]Scores, increasing"<<endl<<"[4]Scores, decreasing"<<endl<<"[5]Date, increasing"<<endl<<"[6]Date, decreasing"<<endl;
                    string srtans;
                    getline(cin,srtans);
                    if (atoll(srtans.c_str())>=1&&atoll(srtans.c_str())<=6) {
                        srtmode=atoll(srtans.c_str());
                    }
                    if (autosave) savedata();
                } else if (setans=="2") {
                    cout<<"About keep assignments:Assignments older than the set time will be automatically deleted."<<endl<<"Select your preferred time."<<endl<<"[1]1 week"<<endl<<"[2]2 weeks"<<endl<<"[3]1 month"<<endl<<"[4]2 months"<<endl<<"[5]6 months"<<endl<<"[6]Forever"<<endl;
                    string settmp;
                    getline(cin,settmp);
                    if (to_string(atoll(settmp.c_str()))==settmp) {
                        ll timetmp = atoll(settmp.c_str());
                        if (timetmp>0&&timetmp<7) {
                            rten=timetmp;
                            if (rten==1) cout<<"Assignment time successfully set to 1 week."<<endl;
                            else if (rten==2) cout<<"Assignment time successfully set to 2 weeks."<<endl;
                            else if (rten==3) cout<<"Assignment time successfully set to 1 month."<<endl;
                            else if (rten==4) cout<<"Assignment time successfully set to 2 months."<<endl;
                            else if (rten==5) cout<<"Assignment time successfully set to 6 months."<<endl;
                            else if (rten==6) cout<<"Assignment time successfully set to forever."<<endl;
                        }
                    }
                    if (autosave) savedata();
                } else if (setans=="3") {
                    cout<<"About multicore:Your processor may be capable of running multiple tasks at once. Using multicore settings will evaluate homework using more cores. "<<endl<<"Input the amount of cores."<<endl;
                    if (compcore==0) cout<<"Suggestion is unavailble.."<<endl;
                    else if (compcore<=3) cout<<"Using one core is recommended."<<endl;
                    else cout<<"Using "<<compcore-2<<" cores is recommended."<<endl;
                    string settmp;
                    getline(cin,settmp);
                    if (to_string(atoll(settmp.c_str()))==settmp) {
                        ll coretmp = atoll(settmp.c_str());
                        if (coretmp>0) {
                            mltcore=coretmp;
                            if (mltcore==1) cout<<"Multicore successfully set to 1 core."<<endl;
                            else cout<<"Multicore successfully set to "<<mltcore<<" cores."<<endl;
                        }
                    }
                    if (autosave) savedata();
                } else if (setans=="4") {
                    bool dirlib=false;
                    bool soundlib=false;
                    ifstream libftest("/usr/local/lib");
                    if (libftest.good()) {
                        dirlib=true;
                    }
                    libftest.close();
                    if (dirlib) {
                        libftest.open("/usr/local/lib/libirrklang.dylib");
                        if (libftest.good()) {
                            soundlib=true;
                        }
                    }
                    if (dirlib&&soundlib) {
                        while (true) {
                            if (sound) {
                                while (true) {
                                    cout<<"Current selectiion:";
                                    if (selaud.size()==audio.size()) cout<<"All";
                                    else if (selaud.size()==0) {
                                        cout<<"None";
                                    } else {
                                        cout<<audio[selaud[0]].sname;
                                        for (ll i=1;i<selaud.size();i++) {
                                            cout<<", "<<audio[selaud[i]].sname;
                                        }
                                    }
                                    bool soundcapped=true;
                                    if (audio.size()<35) soundcapped=false;
                                    cout<<endl<<"[1]Disable sound"<<endl;
                                    if (!soundcapped) cout<<"[2]Add new sounds"<<endl;
                                    cout<<"["<<3-soundcapped<<"]Delete sounds"<<endl<<"--------"<<endl<<"["<<4-soundcapped<<"]Select all"<<endl;
                                    map<char, ll>schoice;
                                    for (ll i=0;i<audio.size();i++) {
                                        if (i+5-soundcapped<=9) {
                                            cout<<"["<<i+5-soundcapped<<"]"<<audio[i].sname<<endl;
                                            schoice[i+5-soundcapped+'0']=i+1;
                                        } else {
                                            schoice['A'+i-5-soundcapped]=i+1;
                                            cout<<"["<<(char)('A'+i-5-soundcapped)<<"]"<<audio[i].sname<<endl;
                                        }
                                    }
                                    cout<<"Select songs to play after a correct submission..."<<endl;
                                    string songchoice;
                                    getline(cin,songchoice);
                                    bool fc[audio.size()];
                                    bool choosesounds=true;
                                    for (ll i=0;i<audio.size();i++) fc[i]=0;
                                    for (ll i=0;i<songchoice.length();i++) {
                                        if (songchoice[i]==4-soundcapped+'0') for (ll j=0;j<audio.size();j++) fc[j]=1;
                                        else if (schoice[songchoice[i]]!=0) fc[schoice[songchoice[i]]-1]=1;
                                        else if (songchoice[i]=='2') {
                                            choosesounds=false;
                                            cout<<"Alert! Song must be in WAV format."<<endl<<"Input the path of the song..."<<endl;
                                            string newsoundpth;
                                            getline(cin,newsoundpth);
                                            nml(newsoundpth);
                                            ifstream newsoundtest(newsoundpth);
                                            if (newsoundtest.good()) {
                                                newsoundtest.close();
                                                cout<<"What is the name of the song?"<<endl;
                                                string songn;
                                                getline(cin,songn);
                                                string songf="";
                                                for (ll j=0;j<16;j++) songf+=randname[rand()%36];
                                                fcopy(newsoundpth,db+songf+".wav");
                                                audio.push_back({songf,songn});
                                                cout<<"Song "<<songn<<" imported successfully."<<endl;
                                            } else cout<<"Error reading song!"<<endl;
                                            //add new sounds
                                            break;
                                        } else if (songchoice[i]==3-soundcapped+'0') {
                                            choosesounds=false;
                                            for (ll i=0;i<audio.size();i++) {
                                                cout<<"[";
                                                i<9?cout<<i+1:cout<<(char)('A'+i-9);
                                                cout<<"]"<<audio[i].sname<<endl;
                                            }
                                            cout<<"What song do you want to delete?"<<endl;
                                            string delschoice;
                                            getline(cin,delschoice);
                                            set<ll>delchoice;
                                            for (ll i=0;i<delschoice.length();i++) delchoice.insert(delschoice[i]>='A'?delschoice[i]-'A'+10-1:delschoice[i]-'0'-1);
                                            vector<ll>todel;
                                            for (set<ll>::iterator i=delchoice.begin();i!=delchoice.end();i++) if (*i<audio.size()) todel.push_back(*i); else break;
                                            if (todel.size()) cout<<"Are you sure you want to delete ";
                                            for (ll i=0;i<todel.size()-1;i++) cout<<audio[todel[i]].sname<<", ";
                                            if (todel.size()>1) cout<<"and ";
                                            cout<<audio[todel[todel.size()-1]].sname<<"? This action is irreversible. Input CONFIRM to confirm."<<endl;
                                            string conf;
                                            getline(cin,conf);
                                            if (conf=="CONFIRM") {
                                                for (ll i=todel.size()-1;i>=0;i--) audio.erase(audio.begin()+todel[i]);
                                                sort(selaud.begin(),selaud.end());
                                                for (ll i=selaud.size();i>=0;i++) {
                                                    if (selaud[i]>=audio.size()) selaud.erase(selaud.begin()+i);
                                                    i--;
                                                }
                                            }
                                        } else if (songchoice=="1") {
                                            cout<<"Sound disabled"<<endl;
                                            sound=false;
                                            break;
                                        }
                                    }
                                    if (choosesounds) {
                                        selaud.clear();
                                        for (ll i=0;i<audio.size();i++) if (fc[i]) selaud.push_back(i);
                                        break;
                                    }
                                }
                                break;
                            } else {
                                cout<<"Sound enabled"<<endl;
                                sound=true;
                            }
                        }
                    } else {
                        cout<<"Using sound requires the installation of external libraries. This will require an administrator password. Enter y to proceed."<<endl;
                        string confins;
                        getline(cin,confins);
                        if (confins=="y"||confins=="Y") {
                            ofstream sil(db+"tmp/sil.txt");
                            sil<<"SILENCE";
                            sil.close();
                            system(("rm -r "+db+"tmp/*").c_str());
                            system(("open "+safespace(db+"soundsetup")).c_str());
                            ifstream donetest;
                            while (true) {
                                donetest.open(db+"tmp/installed.txt");
                                if (donetest.good()) break;
                                donetest.close();
                                usleep(1e4);
                            }
                            donetest.close();
                            ifstream instest("/usr/local/lib/libirrklang.dylib");
                            if (instest.good()) {
                                cout<<"Sound enabled"<<endl;
                                sound=true;
                            } else cout<<"Install failed."<<endl;
                            instest.close();
                        }
                    }
                    if (autosave) savedata();
                } else if (setans=="5") {
                    if (autosave) {
                        cout<<"Autosave disabled."<<endl;
                        autosave=false;
                    } else {
                        if (asdisabled) {
                            cout<<"Are you sure about disabling autosave? You may corrupt files. Input CONFIRM to confirm."<<endl;
                            string conf;
                            getline(cin,conf);
                            if (conf=="CONFIRM") {
                                cout<<"Autosave enabled."<<endl;
                                autosave=true;
                                savedata();
                                asdisabled=false;
                            }
                        } else {
                            cout<<"Autosave enabled."<<endl;
                            autosave=true;
                            savedata();
                        }
                    }
                } else if (setans=="6") {
                    system("clear");
                    break;
                }
            }
        } else if (homeans=="4") {
            //Save
            savedata();
            return 0;
        } else if (tolower(homeans[0])=='f'&&homeans.length()==1&&impissue) {
            return 0;
        } else if (atoll(homeans.c_str())>=5&&atoll(homeans.c_str())<outcnt) {
            vq=true;
            target = data[hwpoint[atoll(homeans.c_str())-5]].id;
        } else {
            string vtmp=homeans;
            transform(homeans.begin(),homeans.end(),vtmp.begin(),::tolower);
            bool hitach = false;
            for (ll i=0;i<easter.size();i++) {
                if (homeans==easter[i].trig) {
                    hitach=true;
                    cout<<easter[i].msg<<endl;
                    if (!secret[i]) cout<<"Achievement \""<<easter[i].ach<<"\" complete."<<endl;
                    secret[i]=true;
                    break;
                }
            }
            if (!hitach) {
                if (vtmp=="changelog") {
                    cout<<"What's changed in v1.3:"<<endl<<"Added new file format"<<endl;
                } else if (vtmp=="kill") return 0;
                else if (vtmp=="crypt") {
                    cout<<"Crypto helper"<<endl<<"Enter the path of the file."<<endl;
                    string cryf;
                    getline(cin,cryf);
                    nml(cryf);
                    ifstream crytest(cryf);
                    if (crytest.good()) {
                        crytest.close();
                        cout<<"Enter the output file."<<endl;
                        string cryof;
                        getline(cin,cryof);
                        system((cmdenc+" -in "+safespace(cryf)+" -out "+safespace(cryof)).c_str());
                    } else cout<<"File error!"<<endl;
                } else if (vtmp=="clearf") {
                    cout<<"Clear all program files? This action is irreversible(Input CLEAR in all caps to confirm)"<<endl;
                    string clearall;
                    getline(cin,clearall);
                    if (clearall=="CLEAR") {
                        system(("rm -r "+safespace(db)).c_str());
                        cout<<"Files cleared. Program will now force quit."<<endl;
                        return 0;
                    }
                } else if (vtmp=="id") {
                    cout<<"How many random length 16 IDs?"<<endl;
                    string idin;
                    getline(cin,idin);
                    if (atoll(idin.c_str())>0) {
                        for (ll i=0;i<atoll(idin.c_str());i++) {
                            string idout="";
                            for (ll j=0;j<16;j++) idout+=randname[rand()%36];
                            cout<<idout<<endl;
                        }
                    }
                } else cout<<"Invalid response."<<endl;
            }
        }
        if (vq) {
            system("clear");
            ifstream bundltest(db+target);
            if (!bundltest.good()) {
                cout<<"Error! Homework file missing."<<endl;
                continue;
            }
            //DECRYPT
            string denccmd = "openssl aes-256-cbc -d -K "+key+" -iv "+iv+" -S "+salt+" -in "+safespace(db+target)+" -out "+safespace(db+"tmp/"+target);
            system(denccmd.c_str());
            //OPEN EM
            system(("unzip -o -qq "+safespace(db+"tmp/"+target)+" -d "+safespace(db+"tmp/"+target+'e')).c_str());
            //READ EM
            ifstream qread(db+"tmp/"+target+"e/description.txt");
            vector<string>probdes;
            if (qread.good()) {
                while (!qread.eof()) {
                    string qreadtmp;
                    getline(qread,qreadtmp);
                    probdes.push_back(qreadtmp);
                }
            } else {
                probdes.push_back("File error!");
            }
            qread.close();
            string probname;
            qread.open(db+"tmp/"+target+"e/title.txt");
            getline(qread,probname);
            qread.close();
            if (data[hwpoint[atoll(homeans.c_str())-5]].name=="Undefined") {
                data[hwpoint[atoll(homeans.c_str())-5]].name=probname;
                if (autosave) savedata();
            }
            qread.open(db+"tmp/"+target+"e/in.txt");
            vector<string>probin;
            if (qread.good()) {
                while (!qread.eof()) {
                    string qreadtmp;
                    getline(qread,qreadtmp);
                    probin.push_back(qreadtmp);
                }
            } else {
                probin.push_back("File error!");
            }
            qread.close();
            vector<string>probout;
            qread.open(db+"tmp/"+target+"e/out.txt");
            if (qread.good()) {
                while (!qread.eof()) {
                    string qreadtmp;
                    getline(qread,qreadtmp);
                    probout.push_back(qreadtmp);
                }
            } else {
                probout.push_back("File error!");
            }
            qread.close();
            ll ex = 1;
            vector<vector<string>>inex;
            while (true) {
                qread.open(db+"tmp/"+target+"e/exin"+to_string(ex)+".txt");
                if (qread.good()) {
                    vector<string>exrip;
                    while (!qread.eof()) {
                        string rdtmp;
                        getline(qread,rdtmp);
                        exrip.push_back(rdtmp);
                    }
                    inex.push_back(exrip);
                } else {
                    break;
                }
                ex++;
                qread.close();
            }
            ex = 1;
            vector<vector<string>>outex;
            while (true) {
                qread.open(db+"tmp/"+target+"e/exout"+to_string(ex)+".txt");
                if (qread.good()) {
                    vector<string>exrip;
                    while (!qread.eof()) {
                        string rdtmp;
                        getline(qread,rdtmp);
                        exrip.push_back(rdtmp);
                    }
                    outex.push_back(exrip);
                } else {
                    break;
                }
                ex++;
                qread.close();
            }
            ex--;
            ll dtpt = 1;
            vector<vector<string>>indata;
            while (true) {
                qread.open(db+"tmp/"+target+"e/in"+to_string(dtpt)+".txt");
                if (qread.good()) {
                    vector<string>datarip;
                    while (!qread.eof()) {
                        string rdtmp;
                        getline(qread,rdtmp);
                        datarip.push_back(rdtmp);
                    }
                    indata.push_back(datarip);
                } else {
                    break;
                }
                dtpt++;
                qread.close();
            }
            dtpt = 1;
            vector<vector<string>>outdata;
            while (true) {
                qread.open(db+"tmp/"+target+"e/out"+to_string(dtpt)+".txt");
                if (qread.good()) {
                    vector<string>datarip;
                    while (!qread.eof()) {
                        string rdtmp;
                        getline(qread,rdtmp);
                        datarip.push_back(rdtmp);
                    }
                    outdata.push_back(datarip);
                } else {
                    break;
                }
                dtpt++;
                qread.close();
            }
            dtpt--;
            //DELETE EM
            system(("rm -r "+safespace(db+"tmp/*")).c_str());
            while (true) {
                cout<<endl<<probname<<endl<<"Your current score:"<<data[hwpoint[atoll(homeans.c_str())-5]].score<<endl<<"--------"<<endl<<"Problem description:"<<endl;
                for (ll i=0;i<probdes.size();i++) {
                    cout<<probdes[i]<<endl;
                }
                cout<<"--------"<<endl<<"Input:"<<endl;
                for (ll i=0;i<probin.size();i++) {
                    cout<<probin[i]<<endl;
                }
                cout<<"--------"<<endl<<"Output:"<<endl;
                for (ll i=0;i<probout.size();i++) {
                    cout<<probout[i]<<endl;
                }
                for (ll i=0;i<ex;i++) {
                    cout<<"--------"<<endl<<"Example input "<<i+1<<':'<<endl;
                    for (ll j=0;j<inex[i].size();j++) {
                        cout<<inex[i][j]<<endl;
                    }
                    cout<<"Example output "<<i+1<<':'<<endl;
                    for (ll j=0;j<outex[i].size();j++) {
                        cout<<outex[i][j]<<endl;
                    }
                }
                cout<<"--------"<<endl<<"[1]Submit"<<endl<<"[2]Delete"<<endl;
                bool sccode=false;
                ifstream scodetst(db+target+".cpp");
                if (scodetst.good()) sccode=true;
                scodetst.close();
                if (sccode) {
                    cout<<"[3]View last submitted source code"<<endl;
                    cout<<"[4]Exit"<<endl;
                } else {
                    cout<<"[3]Exit"<<endl;
                }
                string hwsubans;
                getline(cin,hwsubans);
                if (hwsubans=="1") {
                    ofstream silence(db+"tmp/sl.silence");
                    silence<<"Silent!";
                    silence.close();
                    system(("rm -r "+safespace(db+"tmp/*")).c_str());
                    cout<<"Enter code path"<<endl;
                    string cdpth;
                    getline(cin,cdpth);
                    nml(cdpth);
                    ifstream codeverf(cdpth);
                    if (codeverf.good()) {
                        codeverf.close();
                        //Prepare code
//                        vector<string>code;
//                        while (!codeverf.eof()) {
//                            string codeintmp;
//                            getline(codeverf,codeintmp);
//                            code.push_back(codeintmp);
//                        }
//                        prepcode(code);
//                        ofstream out(db+"tmp/preppedcode.cpp");
//                        for (ll i=0;i<code.size();i++) {
//                            out<<code[i]<<endl;
//                        }
                        fcopy(cdpth,db+"tmp/preppedcode.cpp");
                        fcopy(cdpth,db+target+".cpp");
                        //Compile
                        system((safespace(db+"gpphelper")+" "+username).c_str());
                        bool compile=true;
                        ifstream in(db+"tmp/err");
                        if (in.good()) {
                            string wtrtest;
                            getline(in,wtrtest);
                            if (wtrtest!="") {
                                compile=false;
                            }
                        }
                        if (compile) {
                            //run multicore
                            ll folders=min(dtpt,mltcore);
                            for (ll i=1;i<=folders;i++) {
                                system(("mkdir "+safespace(db+"tmp/"+to_string(i))).c_str());
                            }
                            queue<ll>rmtasks;
                            for (ll i=1;i<=dtpt;i++) {
                                rmtasks.push(i);
                            }
                            //Copy over exe
                            for (ll i=1;i<=folders;i++) system(("cp "+safespace(db+"tmp/exe")+" "+safespace(db+"tmp/"+to_string(i)+"/hwexe"+to_string(i))).c_str());
                            //Start the first batch
                            chrono::high_resolution_clock::time_point timer[folders];
                            for (ll i=1;i<=folders;i++) {
                                ll curtask=rmtasks.front();
                                rmtasks.pop();
                                //Write question number
                                //Write to the bridge
                                ofstream foldout(db+"tmp/pth.bridge");
                                foldout<<db<<"tmp/"<<i<<"/"<<endl<<curtask<<endl<<db<<"tmp/"<<endl<<"hwexe"<<i;
                                foldout.close();
                                //Write in files
                                foldout.open(db+"tmp/"+to_string(i)+"/in.txt");
                                if (indata[curtask-1].size()!=0) foldout<<indata[curtask-1][0];
                                for (ll j=1;j<indata[curtask-1].size();j++) {
                                    foldout<<endl<<indata[curtask-1][j];
                                }
                                foldout.close();
                                //Copy over openhelper
                                system(("cp "+safespace(db+"openhelper")+" "+safespace(db+"tmp/"+to_string(i))).c_str());
                                rename((db+"tmp/"+to_string(i)+"/openhelper").c_str(),(db+"tmp/"+to_string(i)+"/openhelper"+to_string(curtask)).c_str());
                                //Open openhelper
                                system(("open "+safespace(db+"tmp/"+to_string(i)+"/openhelper"+to_string(i))).c_str());
                                //Wait for ini.signal
                                while (true) {
                                    ifstream signaltest(db+"tmp/"+to_string(i)+"/ini.signal");
                                    if (signaltest.good()) {
                                        signaltest.close();
                                        break;
                                    }
                                    usleep(1e4);
                                }
                                timer[i-1]=chrono::high_resolution_clock::now();
                                ofstream qnum(db+"tmp/"+to_string(i)+"/qnum.txt");
                                qnum<<curtask;
                                qnum.close();
                            }
                            bool mainsig[folders];
                            for (ll i=1;i<=folders;i++) {
                                mainsig[i-1]=false;
                            }
                            while (!rmtasks.empty()) {
                                for (ll i=1;i<=folders;i++) {
                                    if (!mainsig[i-1]) {
                                        //Look for TE
                                        //Look for main.signal
                                        ifstream mainsigtest(db+"tmp/"+to_string(i)+"/main.signal");
                                        if (mainsigtest.good()) {
                                            mainsig[i-1]=true;
                                            continue;
                                        }
                                        if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - timer[i-1]).count()>1000) {
                                            system(("killall hwexe"+to_string(i)).c_str());
                                            mainsig[i-1]=true;
                                        }
                                    }
                                }
                                for (ll i=1;i<=folders;i++) {
                                    if (rmtasks.empty()) break;
                                    if (mainsig[i-1]) { //if one of them are available...
                                        mainsig[i-1]=false;
                                        system(("rm "+safespace(db+"tmp/"+to_string(i)+"/ini.signal")).c_str());
                                        ofstream mainsil(db+"tmp/"+to_string(i)+"/main.signal");
                                        mainsil<<"SILENCE";
                                        mainsil.close();
                                        system(("rm "+safespace(db+"tmp/"+to_string(i)+"/main.signal")).c_str());
                                        ifstream qdnrd(db+"tmp/"+to_string(i)+"/qnum.txt");
                                        ll curtask=rmtasks.front();
                                        rmtasks.pop();
//                                        cout<<"Start "<<curtask<<endl;
                                        //Write question number
                                        ofstream qnum(db+"tmp/"+to_string(i)+"/qnum.txt");
                                        qnum<<curtask;
                                        qnum.close();
                                        //Write to the bridge
                                        ofstream foldout(db+"tmp/pth.bridge");
                                        foldout<<db<<"tmp/"<<i<<"/"<<endl<<curtask<<endl<<db<<"tmp/"<<endl<<"hwexe"<<i;
                                        foldout.close();
                                        //Write in files
                                        foldout.open(db+"tmp/"+to_string(i)+"/in.txt");
                                        if (indata[curtask-1].size()!=0) foldout<<indata[curtask-1][0];
                                        for (ll j=1;j<indata[curtask-1].size();j++) {
                                            foldout<<endl<<indata[curtask-1][j];
                                        }
                                        foldout.close();
                                        //Copy over openhelper
                                        system(("cp "+safespace(db+"openhelper")+" "+safespace(db+"tmp/"+to_string(i))).c_str());
                                        rename((db+"tmp/"+to_string(i)+"/openhelper").c_str(),(db+"tmp/"+to_string(i)+"/openhelper"+to_string(curtask)).c_str());
                                        //Open openhelper
                                        system(("open "+safespace(db+"tmp/"+to_string(i)+"/openhelper"+to_string(curtask))).c_str());
                                        //Wait for wait.signal
                                        while (true) {
                                            ifstream signaltest(db+"tmp/"+to_string(i)+"/ini.signal");
                                            if (signaltest.good()) {
                                                signaltest.close();
                                                break;
                                            }
                                            usleep(1e4);
                                        }
                                        timer[i-1]=chrono::high_resolution_clock::now();
                                    }
                                }
                                usleep(1e4);
                            }
                            while (true) {
                                bool canbk=true;
                                for (ll i=1;i<=folders;i++) {
                                    if (!mainsig[i-1]) {
                                        canbk=false;
                                        //Something is NOT DONE AND NOT TERMINATED
                                        //Look for TE
                                        ifstream mainsigtest(db+"tmp/"+to_string(i)+"/main.signal");
                                        if (mainsigtest.good()) {
                                            mainsig[i-1]=true;
                                            mainsigtest.close();
                                            continue;
                                        }
                                        mainsigtest.close();
                                        if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - timer[i-1]).count()>1000) {
                                            system(("killall hwexe"+to_string(i)).c_str());
                                            mainsig[i-1]=true;
                                        }
                                        //Look for main.signal
                                    }
                                }
                                if (canbk) break;
                                usleep(1e4);
                            }
                            //Compare output
                            ll timeres[dtpt];
                            for (ll i=1;i<=dtpt;i++) {
                                ifstream timeread(db+"tmp/time"+to_string(i)+".txt");
                                timeread>>timeres[i-1];
                                timeread.close();
                            }
                            ll correct=0;
                            cout<<"Test results:"<<endl;
                            for (ll i=1;i<=dtpt;i++) {
                                if (timeres[i-1]>1000) {
                                    cout<<"#"<<i<<":TE"<<endl;
                                } else {
                                    cout<<"#"<<i;
                                    //Evaluation:Remove last blank line
                                    vector<string>outcomp;
                                    ifstream outputc(db+"tmp/out"+to_string(i)+".txt");
                                    while (!outputc.eof()) {
                                        string tmp;
                                        getline(outputc,tmp);
                                        outcomp.push_back(tmp);
                                    }
                                    if (outcomp[outcomp.size()-1]=="") outcomp.erase(outcomp.begin()+outcomp.size()-1);
                                    for (ll j=0;j<outcomp.size();j++) {
                                        if (outcomp[j][outcomp[j].size()-1]==' ') {
                                            outcomp[j].erase(outcomp[j].begin()+outcomp[j].size()-1);
                                        }
                                    }
                                    if (outdata[i-1][outdata[i-1].size()-1]=="") outdata[i-1].erase(outdata[i-1].begin()+outdata[i-1].size()-1);
                                    for (ll j=0;j<outdata[i-1].size();j++) {
                                        if (outdata[i-1][j][outcomp[j].size()-1]==' ') {
                                            outdata[i-1][j].erase(outdata[i-1][j].begin()+outdata[i-1][j].size()-1);
                                        }
                                    }
                                    bool ac = true;
                                    if (outdata[i-1].size()==outcomp.size()) {
                                        for (ll j=0;j<outdata[i-1].size();j++) {
                                            if (outdata[i-1][j]!=outcomp[j]) ac=false;
                                        }
                                    } else ac = false;
                                    if (ac) {cout<<"-AC:";correct++;}
                                    else cout<<"-WA:";
                                    cout<<timeres[i-1]<<"ms"<<endl;
                                }
                            }
                            system(("rm -r "+safespace(db+"tmp/*")).c_str());
                            ll score = round(((ld)correct/dtpt)*100.0);
                            data[hwpoint[atoll(homeans.c_str())-5]].score=max(data[hwpoint[atoll(homeans.c_str())-5]].score,score);
                            cout<<"Your current score:"<<data[hwpoint[atoll(homeans.c_str())-5]].score<<endl;
                            if (score==100) {
                                cor++;
                                if (cor==1) cout<<"Achievement \"Success\" complete."<<endl;
                                else if (cor==10) cout<<"Achievement \"More!\" complete."<<endl;
                                else if (cor==100) cout<<"Achievement \"Unstoppable\" complete."<<endl;
                                else if (cor==1000) cout<<"Achievement \"Godlike!\" complete."<<endl;
                                if (sound) {
                                    if (selaud.size()>0) {
                                        ofstream songfname(db+"songbrd");
                                        songfname<<audio[selaud[rand()%selaud.size()]].fname;
                                        system(("open "+safespace(db+"acsound")).c_str());
                                    }
                                }
                            } else {
                                if (incor==1) cout<<"Achievement \"You can try again\" complete."<<endl;
                                else if (incor==10) cout<<"Achievement \"Get up!\" complete."<<endl;
                                else if (incor==100) cout<<"Achievement \"Keep going!\" complete."<<endl;
                                else if (incor==1000) cout<<"Achievement \"Nearly there!\" complete."<<endl;
                                incor++;
                            }
                            if (autosave) savedata();
                            cout<<"Press return to continue...";
                            cin.get();
                            system((db+"soundkill").c_str());
                        } else {
                            cout<<"Compilation error."<<endl;
                        }
                    } else {
                        cout<<"Code error!";
                    }
                } else if (hwsubans=="2") {
                    data.erase(data.begin()+hwpoint[atoll(homeans.c_str())-5]);
                    system(("rm "+safespace(db+target)).c_str());
                    if (sccode) system(("rm "+safespace(db+target+".cpp")).c_str());
                    system("clear");
                    break;
                } else if (hwsubans=="3"&&sccode) {
                    system(("open -a Finder "+safespace(db+target+".cpp")).c_str());
                } else if (hwsubans=="3"&&!sccode) {
                    system("clear");
                    break;
                } else if (hwsubans=="4"&&sccode) {
                    system("clear");
                    break;
                } else {
                    cout<<"Invalid response."<<endl;
                }
            }
        }
    }
}
// .lm7hwpkg
/*
 
 Submit homework page:
 [1]New assignment
 [2]Create homework package
 [3]Settings
 [4]Quit
 
 ----------
 
 Incomplete assignments
 [5]A+B Problem:23
 [6]Random_question:93
 [7]ZCrap:0
 
 ----------
 
 Completed assignments
 [8]Fastest man alive
 [9]Compl_question
 
 Settings page:
 [1]Sort:Alphabetical increasing
 [2]Keep assignments for:Forever
 [3]Multicore settings:2 cores
 
 Menu on an incomplete assignment:
 A+B Problem
 Your current score:23
 Question requirements:
 blahblahblah
 
 
 //lmao
 
 How to evaluate:
 RTE&ME CE WA AC TE
 
 Running the program
 1.Open program EXE
 2.Repeatedly check for RTURN for 1s
 3.If program return file is not there, terminate execution
 4.Return file there->Check for ans to see if AC/WA
 Return file not there->TE/RTE
 
 /*
 
 When /* is detetected: DELETE EVERYTHING UNTIL "* /" is found
 When // is detected: DELETE EVERYTHING ON THE SAME LINE
 */
