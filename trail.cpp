#include<bits/stdc++.h>
using namespace std;
set<int>boxes;
map<int,int> S_box;
void path(int cur,int round,vector<int>trail)
{
    if(round==4) 
    {
        cur = S_box[cur];
        trail.push_back(cur);
        for(auto i: trail) cout<<i<<' ';
        cout<<'\n';
        boxes.insert((cur-1)/4+1);
        trail.push_back(cur);
        return;
    }
    if(cur<1 || cur>32) return;
    if(round==1);
    else cur = S_box[cur];
    trail.push_back(cur);
    switch(cur%4)
    {
        case 1:
        
        path(cur,round+1,trail);
        path(cur+2,round+1,trail);
        break;
        case 2:
        path(cur-1,round+1,trail);
        path(cur+1,round+1,trail);
        path(cur,round+1,trail);
        break;
        case 3:
        path(cur-1,round+1,trail);
        path(cur-2,round+1,trail);
        path(cur,round+1,trail);
        break;
        default:
        ;

        
    }
    trail.pop_back();
}
int main()
{
    S_box[1]=1;
    S_box[2]=9;
    S_box[3]=17;
    S_box[4]=25;

    S_box[5]=2;
    S_box[6]=10;
    S_box[7]=18;
    S_box[8]=26;

    S_box[9]=3;
    S_box[10]=11;
    S_box[11]=19;
    S_box[12]=27;

    S_box[13]=4;
    S_box[14]=12;
    S_box[15]=20;
    S_box[16]=28;

    S_box[17]=5;
    S_box[18]=13;
    S_box[19]=21;
    S_box[20]=29;

    S_box[21]=6;
    S_box[22]=14;
    S_box[23]=22;
    S_box[24]=30;

    S_box[25]=7;
    S_box[26]=15;
    S_box[27]=23;
    S_box[28]=31;

    S_box[29]=8;
    S_box[30]=16;
    S_box[31]=24;
    S_box[32]=32;

    
    vector<int>trail;
    for(int i=0;i<8;i++)
    {
        path(4*i+1,1,trail);
        path(4*i+2,1,trail);
        path(4*i+3,1,trail);
    }
    cout<<"boxes"<<'\n';
    for(auto i: boxes) cout<<i<<' ';
    cout<<'\n';

}