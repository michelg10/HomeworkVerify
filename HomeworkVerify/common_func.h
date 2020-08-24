#ifndef common_func_h
#define common_func_h
string safespace(string s,int OS=SYS) {
    string rturn;
    if (OS==APPL) {
        map<char,bool>toEscape;
        toEscape['~']=toEscape['=']=toEscape['[']=toEscape[']']=toEscape['{']=toEscape['}']=toEscape['\\']=toEscape['|']=toEscape[';']=toEscape['\'']=toEscape['"']=toEscape['<']=toEscape['>']=toEscape['?']=toEscape[' ']=toEscape['!']=toEscape['#']=toEscape['%']=toEscape['&']=toEscape['*']=toEscape['(']=toEscape[')']=1;
        stringstream ss;
        for (ll i=0;i<s.length();i++) toEscape[s[i]] ? ss<<"\\"<<s[i] : ss<<s[i];
        rturn=ss.str();
    } else if (OS==WIN) {
        rturn="\""+s+"\"";
        for (ll i=0;i<rturn.size();i++) if (rturn[i]=='/') rturn[i]='\\';
    }
    return rturn;
}
bool isLpYr(ll yr) {
    return (yr%400==0)||(yr%4==0&&yr%100!=0);
}
string date() {
    time_t tmptime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string tmp = ctime(&tmptime);
    tmp.erase(tmp.size()-1,1);
    return tmp;
}
ll strtm2int(string s) { //epoch time:seconds from jan 1,1970 00:00:00
    s=s.substr(s.find(" ")+1);
    string monstr=s.substr(0,s.find(" "));
    s=s.substr(s.find(" ")+1);
    ll day=atoll(s.substr(0,s.find(" ")).c_str());
    s=s.substr(s.find(" ")+1);
    ll hour=atoll(s.substr(0,s.find(":")).c_str());
    s=s.substr(s.find(":")+1);
    ll minute=atoll(s.substr(0,s.find(":")).c_str());
    s=s.substr(s.find(":")+1);
    ll second=atoll(s.substr(0,s.find(" ")).c_str());
    s=s.substr(s.find(" ")+1);
    ll year=atoll(s.c_str());
    map<string,ll>mon2ll;
    mon2ll["Jan"]=0;
    mon2ll["Feb"]=31;
    mon2ll["Mar"]=mon2ll["Feb"]+(isLpYr(year)?29:28);
    mon2ll["Apr"]=mon2ll["Mar"]+31;
    mon2ll["May"]=mon2ll["Apr"]+30;
    mon2ll["Jun"]=mon2ll["May"]+31;
    mon2ll["Jul"]=mon2ll["Jun"]+30;
    mon2ll["Aug"]=mon2ll["Jul"]+31;
    mon2ll["Sep"]=mon2ll["Aug"]+31;
    mon2ll["Oct"]=mon2ll["Sep"]+30;
    mon2ll["Nov"]=mon2ll["Oct"]+31;
    mon2ll["Dec"]=mon2ll["Nov"]+30;
    ll rturn=0;
    for (ll i=1970;i<year;i++) rturn+=(isLpYr(i)?366:365);
    rturn+=mon2ll[monstr];
    rturn+=day;
    rturn*=24;
    rturn+=hour;
    rturn*=60;
    rturn+=minute;
    rturn*=60;
    rturn+=second;
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

#endif /* common_func_h */
