#include<iostream>
#include<fstream>
#include<string>
#include"pet.h"

pet *pPet = NULL;

int countRecords(char *pFileName){
    ifstream iCount(pFileName);
    if(iCount.fail()){
        cout << "\nFile open error on " << pFileName<< " in countRecords" << endl;
        exit(-1);
    }
    
    int row = 0;
	int iComma = 0;
    char cTest;
    
    while(!iCount.eof()){
        cTest = iCount.get();
        if(cTest == ',') iComma++;
		if(iComma == 8){
			row++;
			iComma = 0;
		}
    }
    
    if(row == 1) cout << "The file has " << row << " record." <<endl;
    else if(row > 1) cout << "The file has " << row << " records." <<endl;
    
    iCount.close();
    
    return row;
}

void loadRecords(char *pFileName,pet *pPet, int iNumber){
	    
	pet *pTemp = pPet;
	
	ifstream iLoad(pFileName);
	
	if(iLoad.fail()){
        cout << "\nFile open error on " << pFileName<<" in iLoadRecords" << endl;
        exit(-1);
    }
	
	string sTemp;
	int i=0;
	while(i<iNumber){
        getline(iLoad,sTemp);
        if(!sTemp.empty()){
            int sLength=sTemp.size();
            int commaPosition[8] = {0};
            int iCP=0;
			commaPosition[0]=sTemp.find(',',0);
            while(sTemp.find(',',commaPosition[iCP++]+1)<1000){
                commaPosition[iCP]=sTemp.find(',',commaPosition[iCP-1]+1);
            }
            int iSpace=sTemp.find(' ',commaPosition[3]);
            iCP = 0;
            pPet->status=sTemp.substr(0,commaPosition[0]);
            pPet->type=sTemp.substr(commaPosition[0]+1,commaPosition[1]-commaPosition[0]-1);
            pPet->gender=sTemp.substr(commaPosition[1]+1,commaPosition[2]-commaPosition[1]-1);
            pPet->breeds=sTemp.substr(commaPosition[2]+1,commaPosition[3]-commaPosition[2]-1);
            pPet->ageOfYear=sTemp.substr(commaPosition[3]+1,iSpace-commaPosition[3]-1);
            pPet->ageOfMonth=sTemp.substr(iSpace+1,commaPosition[4]-iSpace-1);
            pPet->colour=sTemp.substr(commaPosition[4]+1,commaPosition[5]-commaPosition[4]-1);
            pPet->chipNumber=sTemp.substr(commaPosition[5]+1,commaPosition[6]-commaPosition[5]-1);
            pPet->location=sTemp.substr(commaPosition[6]+1,commaPosition[7]-commaPosition[6]-1);
            pPet->contactNumber=sTemp.substr(commaPosition[7]+1,sLength-commaPosition[7]-1);
            pPet++;
			i++;
        }
    }
	
    pPet = pTemp;
	iLoad.close();

}

void printRecords(pet *pPet, int iNumber){
	int k;
	pet *pTemp=pPet;
	for(k=0;k<iNumber;k++){
		cout<<pPet->status<<';';
        cout<<pPet->type<<';';
        cout<<pPet->gender<<';';
        cout<<pPet->breeds<<';';
        cout<<pPet->ageOfYear<<';';
        cout<<pPet->ageOfMonth<<';';
        cout<<pPet->colour<<';';
        cout<<pPet->chipNumber<<';';
        cout<<pPet->location<<';';
        cout<<pPet->contactNumber<<endl;
        pPet++;	
	}
	pPet = pTemp;
}

int main(){
	
	char *pFileName = NULL;
	char fileName[100];

    int iNumber;
    cout<<"Please input the full path of a file : ";
    cin>>fileName;
	pFileName = fileName;
	
	iNumber = countRecords(pFileName);
	pPet = new pet[iNumber];
	loadRecords(pFileName,pPet,iNumber);
	printRecords(pPet,iNumber);
	
	delete[] pPet;
	return 0;
}


















