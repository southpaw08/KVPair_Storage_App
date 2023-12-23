/**************************************************************************
 * Description : Key Value pair storage appplication. Stores the key i.e 
 *               device and its information in a database which is saved 
 *               to disk or loaded from disk
 * 
 * Author      : Anup Vishwakarma
 *               vanup08@gmail.com
***************************************************************************/ 



#include <iostream>
#include <unordered_map>    /* Using unordered map for optimized & efficient solution */
//#include <map>            /* Can use ordered map as well for ordered key val pair */
#include <sstream>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

using namespace std;

unordered_map<string,string> dev_list;
//map<string,string> dev_list;

#define SUCCESS     0
#define FAILURE    -1

/**
 * save_db() - Saves key value pair database in storage
 * Return:     SUCCESS - Successfully saved the database in storage
 *             FAILURE - Couldn't save the databse in storage
 */
int save_db()
{
    const char *filename="KVPStorageDB"; 
    FILE *f = fopen(filename, "wb");
    if(f==NULL)
    {
    	cerr << "Could not open the file - '"
             << filename << "'" << endl;
    	return FAILURE;
    }
    for(auto iter=dev_list.begin(); iter!=dev_list.end(); iter++){

        const char *c_key = iter->first.data();
        const char *c_val = iter->second.data();
       // cout << "Key: " << c_key << " Val: " << c_val << endl;
        fputs(c_key, f);
        fputs(":", f);
        fputs(c_val, f);
        fputs("\n",f);
    }
    fclose(f);
    return SUCCESS;
}

/**
 * load_db() - Loads key value pair database from storage
 * Return:     SUCCESS - Successfully loaded the database
 *             FAILURE - Couldn't load the databse
 */
int load_db()
{
    string key, val, line;
    string filename("KVPStorageDB");
    ifstream db_file(filename);
    if (!db_file.is_open()) {
        cout << "No existing database to load from!" << endl;
        return FAILURE;
    }
    
    while(getline(db_file,line))   
    {
            stringstream iss(line);
            getline(iss, key, ':');
            getline(iss, val);
            dev_list[key] = val;
    }
    db_file.close();
    return SUCCESS;
}

/*
 * db_get():        Retrieves device info from database
 * @arg1-device :   Device name for which information needs to be retrieved from database
 * Return       :   Return device info from database
 */
string db_get(string device)
{
    if(dev_list.count(device)==0)
    {
        cout << device << " is not available" << endl;
        return "N/A";
    }
    //cout << device << " is available and it's value is " << dev_list[device] << endl;
    return dev_list[device];
}

/*
 * db_set()     :   Sets the device info in database
 * @arg1-device :   Device name for which information needs to be set in database
 * @arg2-val    :   Value corresponding to device to be set in database
 * Return       :   SUCCESS - Successfully set the device value
 *                  
 */
int db_set(string device, string val)
{   
    #if 0
    if(val.empty())
    {
        cerr << "No info to set for the device" << endl;
        return FAILURE;
    }
    #endif
    dev_list[device]=val;
    return SUCCESS;
}


/*
 * db_list():       List all the devices and its value in the database
 * Return  :        void
 *                  
 */
int db_list()
{   
    if(dev_list.empty())
    {
        return FAILURE;
    }
    cout << "\nAvailable device list:" << endl;
    cout << "\nDev\t" << "\tConfig  " << endl;
    for(pair<string,string> device:dev_list)
    {
        cout << device.first << "\t\t" << device.second << endl;
    }
    cout << "\n" << endl;
    return SUCCESS;
}

/*
 * db_delete()  :   Delete device and its relevant information from the database
 * @arg1-device :   Name of the device which needs to be deleted
 * Return       :   SUCCESS - Successfully deleted the device and its value
 *                  FAILURE - Couldn't delete the device from database
 *                  
 */
int db_delete(string device)
{
    if(dev_list.empty())
    {
        cout << "Connot delete\n"
             << "Device list is empty\n";
        return FAILURE;
    }
    else if(dev_list.count(device)==0)
    {
        cout << "Operation not allowed!" << endl;
        cout << device << " is not present in the device list" << endl;
        return FAILURE;
    }
    else
    {
        cout << "Deleting device " << device << endl;
        dev_list.erase(device);
        return SUCCESS;
    }
}


int main()
{
    
    string input;
    int ret = load_db();
    if(ret == 0)
    {
        cout << "************************************************************\n"
             << "   Key Value Storage database loaded successfully\n"  
             << "************************************************************"<< endl;
    }
    else
    {
        cerr << "Error in loading Key Value Storage database" << endl;
    }
    cout << "\nPlease enter a command" << endl;
    while(1)
    {
       cout << "> ";
       string cmd;
       vector <string> vec_input;
       getline(cin,input);
       //cout << "Input is: " << input << endl;
       stringstream s_stream(input);
       while(s_stream.good())
       {
            string substr;
            getline(s_stream,substr,' ');
            vec_input.push_back(substr);
       }
       
       #if 0
       for(int i=0; i < vec_input.size(); i++)
       {
           cout << vec_input[i] << endl;
       }
       #endif
       
            cmd = vec_input[0];

               if(cmd == "SET"|| cmd == "set")
               {
                   string key,val;
                   if(vec_input.size()<3)
                   {
                       cout << "Not enough arguments to SET\n"
                            << "Usage: SET KEY VAL\n" << endl;
                   }
                   else if(vec_input.size()>3)
                   {
                       cout << "Too many arguments to SET\n"
                            << "Usage: SET KEY VAL\n" << endl;
                   }
                   else
                   {
                        key = vec_input[1];
                        val = vec_input[2];
                        //cout << "Key is " << key << endl;
                        // cout << "Val is " << val << endl;
                        if(key.empty() || val.empty())
                        {
                            cout << "Not enough arguments to SET\n"
                            << "Usage: SET KEY VAL\n" << endl;
                        }
                        else
                        {
                            int ret = db_set(key,val);
                            if(ret == SUCCESS)
                            {
                                cout << "OK" << endl;
                            }
                        }
                   }
                   
               }
               else if(cmd == "GET" || cmd == "get")
               {
                   string device;
                   if(vec_input.size()<2)
                   {
                       cout << "Not enough arguments to GET\n"
                            << "Usage: GET DEVICE_NAME\n" << endl;
                   }
                   else if(vec_input.size()>2)
                   {
                       cout << "Too many arguments to GET\n"
                            << "Usage: GET DEVICE_NAME\n" << endl;
                   }
                   else
                   {
                       device = vec_input[1];
                       //cout << "Entered command is GET" << endl;
                       //cout << "Getting device details" << endl;
                       if(device.empty())
                       {
                            cout << "Not enough arguments to GET\n"
                                 << "Usage: GET DEVICE_NAME\n" << endl;
                       }
                       else
                       {
                            cout << db_get(device) << endl;
                       }
                   }
               }
               else if(cmd == "DELETE" || cmd == "delete")
               {
                   string device;
                   if(vec_input.size()<2)
                   {
                       cout << "Not enough arguments to DELETE\n"
                            << "Usage: DELETE DEVICE_NAME\n" << endl;
                   }
                   else if(vec_input.size()>2)
                   {
                       cout << "Too many arguments to DELETE\n"
                            << "Usage: DELETE DEVICE_NAME\n" << endl;
                   }
                   else
                   {
                       device = vec_input[1];
                       //cout << "Entered command is DELETE" << endl;
                       if(device.empty())
                       {
                           cout << "Not enough arguments to DELETE\n"
                            << "Usage: DELETE DEVICE_NAME\n" << endl;
                       }
                       else
                       {
                           int res= db_delete(device);
                           if(res == SUCCESS)
                           {    
                               cout << "OK" << endl;
                               //db_list();
                           }
                       }

                   }
               }
               else if(cmd == "Q" || cmd == "QUIT")
               {   cout << "Saving key value pair database in storage" << endl;
                   int ret = save_db();
                   if(ret == SUCCESS)
                   {
                       cout << "Successfully saved the key value pair database to storage disk" << endl;
                   }
                   else
                   {
                       cout << "Unable to save key value pair database to storage disk" << endl;
                   }
                   
                   cout << "Quitting database application" << endl;
                   exit(0); 
               }
               else if(cmd == "LIST" || cmd == "list")
               {
                   int ret = db_list();
                   if(ret == FAILURE)
                   {
                       cout << "Device list is empty" << endl;
                   }
               }
               else if(cmd.empty())
               {
                   /* Do nothing */
               }
               else
               {
                   cout << "Wrong command !!\n";
                   cout << "Please enter a proper command\n" << endl;
                   
                   cout << "**************************************************************\n";
                   cout     << "Allowed Commands: " << endl;
                   cout << "**************************************************************\n";
                   cout << "SET/set         : Set the device info in database\n" 
                        << "GET/set         : Get the device info from database\n"
                        << "DELETE/delete   : Delete a device from database\n"
                        << "Q or QUIT       : Quit and save the database application\n";
                   cout << "**************************************************************\n";
               }
    }
    return 0;
}
