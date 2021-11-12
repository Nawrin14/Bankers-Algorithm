#include<bits/stdc++.h>
using namespace std;
int main()
{

    int m,n,x,y,z,flag, cnt = 0, a, b;

    cout<<"\nEnter the no. of processes: ";
    cin>>n;
    cout<<"\nEnter the no. of resources: ";
    cin>>m;

    vector<vector<int>> Allocation(n, vector<int> (m)), Max(n, vector<int> (m)), Need(n, vector<int> (m));
    vector<int> available(m), finish(n), allocated(m), total_alloc(n), temp_process, temp_alloc, sequence;

    for(int i=0; i<n; i++)
    {
        cout<<"\nProcess "<<i+1<<"\n";
        for(int j=0; j<m; j++)
        {
            cout<<"Maximum value for resource "<<j+1<<": ";
            cin>>x;
            Max[i][j] = x;
        }

        for(int k=0; k<m; k++)
        {
            cout<<"Allocated from resource "<<k+1<<": ";
            cin>>y;
            Allocation[i][k] = y;
            total_alloc[i] += y;
        }
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<m; j++)
        {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    for(int i=0; i<m; i++)
    {
        for(int j=0; j<n; j++)
        {
            allocated[i] += Allocation[j][i];
        }
    }

    for(int i=0; i<m; i++)
    {
        cout<<"\nEnter total value of resource "<<i+1<<": ";
        cin>>z;
        available[i] = z - allocated[i];
    }

    while(cnt != n)
    {
        for(int i=0; i<n; i++)
        {
            flag = 0;
            if(finish[i] == 0)
            {
                for(int j=0; j<m; j++)
                {
                    if(Need[i][j] <= available[j])
                        flag++;
                }

                if(flag == m)
                {
                    temp_process.push_back(i);
                    temp_alloc.push_back(total_alloc[i]);
                }
            }
        }

        if(temp_process.empty())
            break;
        else
        {
            a = max_element(temp_alloc.begin(), temp_alloc.end())-temp_alloc.begin();

            cnt++;
            b = temp_process[a];
            finish[b] = 1;

            for(int j=0; j<m; j++)
            {
                available[j] += Allocation[b][j];
            }

            sequence.push_back(b);
            temp_process.clear();
            temp_alloc.clear();
        }
    }

    if(cnt == n)
    {
        cout<<"\nThe system is currently in safe state and <    ";
        for(int i=0; i<sequence.size(); i++)
        {
            cout<<"P"<<sequence[i]+1<<"\t";
        }
        cout<<"> is the safe sequence.\n";
    }
    else
    {
        cout<<"\nThe system is currently in unsafe state.\n";
    }

}

