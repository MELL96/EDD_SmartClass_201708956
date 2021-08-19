#include <iostream>
#include <windows.h>
#include <regex>
#include <string>
#include <conio.h>
#include <locale.h>
#include <clocale>
#include <iterator>
#include <stdio.h>
#include <fstream>

#include "./student/StudentList.cpp"
#include "./graph/StudentGraph.cpp"

using namespace std;
StudentList<string> *cdll;
StudentGraph<string> *sg;


//------------------------------------------------------------- READ STUDENTS FILE

void readStudents(string path){
    ifstream file(path);
    string line;
    char delimiter = ',';
    getline(file, line);
    while(getline(file, line)){
        stringstream stream(line);
        string carnet, dpi, name, email, password, career, credits, age;

        getline(stream, carnet, delimiter);
        getline(stream, dpi, delimiter);
        getline(stream, name, delimiter);
        getline(stream, career, delimiter);
        getline(stream, password, delimiter);
        getline(stream, credits, delimiter);
        getline(stream, age, delimiter);
        getline(stream, email, delimiter);

        cout << carnet << " " << dpi << " " << name << " " << career << " " << email << " " << password << " " << credits << " " << age << endl;
        cdll->addStudent(carnet, dpi, name, career, email, password, credits, age);
    }
}

//------------------------------------------------------------- MODIFY STUDENT INFO MENU

void modifyStudent(string data){
    int option;
    int newInfo;
    bool accepted;
    string newData;
    StudentNode<string> *modify = cdll->searchStudent(data);

    if(modify != NULL){
        do{
            cout << "\n\n\n********************************************" << endl;
            cout << "*********** Modificar Estudiante ***********" << endl;
            cout << "********************************************" << endl;
            cout << "1. Carnet" << endl;   
            cout << "2. DPI" << endl;   
            cout << "3. Nombre" << endl;   
            cout << "4. Carrera" << endl;   
            cout << "5. Correo" << endl;   
            cout << "6. Clave" << endl;   
            cout << "7. Creditos" << endl;   
            cout << "8. Edad" << endl;   
            cout << "9. Regresar" << endl;   
            cout << "********************************************" << endl;
            cout << "Ingresa la opcion deseada: ";
            cin >> option;
            Sleep(600);

            switch (option)
            {
            case 1:
                do{
                    cout <<  "Ingrese el nuevo numero de carnet ";
                    cin >> newInfo;   
                    if(to_string(newInfo).length() != 9){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos" << endl;
                    }                 
                } while(to_string(newInfo).length() != 9);
                modify->carne = newInfo;                        
                break;
            case 2:
                do{
                    cout << "Ingrese el nuevo numero de DPI ";
                    cin >> newData;
                    if(newData.length() != 13){
                        cout << "\t\t\t\t\t    error - Debes de ingresar 13 digitos" << endl;
                    }
                } while(newData.length() != 13);
                modify->dpi = newData;
                break;
            case 3:
                cout << "Ingrese el nuevo nombre ";
                cin >> newData;
                modify->name = newData;
                break;
            case 4:
                cout << "Ingrese el nuevo nombre de carrera ";
                cin >> newData;
                modify->career = newData;
                break;
            case 5:            
                do{
                    cout << "Ingrese el nuevo correo ";
                    cin >> newData;
                    accepted = cdll->verifyEmail(newData);
                    if(accepted == false){
                        cout << "\t\t\t\t\t    error - Debes de seguir la ER user@dominio.[com|es|org]" << endl;
                    }
                } while(accepted != true);
                modify->email = newData;
                break;
            case 6:
                cout << "Ingrese la nueva clave ";
                cin >> newData;
                modify->password = newData;
                break;
            case 7:
                cout << "Ingrese el nuevo numero de creditos ";
                cin >> newInfo;
                modify->credits = newInfo;
                break;
            case 8:
                cout << "Ingrese la nueva edad ";
                cin >> newInfo;
                modify->age = newInfo;
                break;
            case 9:
                break;
            default:
                cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
                break;
            }
        } while(option != 9);
    } else{
        cout << "\t\t\t\t\t    error - No existe estudiante con DPI " << data << endl;        
    }  
}

//------------------------------------------------------------- ADD STUDENT

void insertStudent(){      
    string carnet, dpi, name, career, email, password, credits, age;
    bool accepted;

    do{
        cout << "Ingresa el carnet: ";
        cin >> carnet;
        if(carnet.length() != 9){
            cout << "\t\t\t\t\t    error - Debes de ingresar 9 digitos" << endl;
        }
    } while(carnet.length() != 9);
    do{
        cout << "Ingresa el DPI: ";
        cin >> dpi;
        if(dpi.length() != 13){
            cout << "\t\t\t\t\t    error - Debes de ingresar 13 digitos" << endl;
        }
    } while(dpi.length() != 13);
    cout << "Ingesa el nombre: ";
    cin >> name;
    cout << "Ingresa la carrera: ";
    cin >> career;
    do{
        cout << "Ingresa el correo: ";
        cin >> email;
        accepted = cdll->verifyEmail(email);
        if(accepted == false){
            cout << "\t\t\t\t\t    error - Debes de seguir la ER user@dominio.[com|es|org]" << endl;
        }
    } while(accepted != true);
    cout << "Ingresa la clave: ";
    cin >> password;
    cout << "Ingresa los creditos: ";
    cin >> credits;
    cout << "Ingresa la edad: ";
    cin >> age;

    cdll->addStudent(carnet, dpi, name, career, password, credits, age, email);
}

//------------------------------------------------------------- REPORTS MENU

void showReports(){
    int option;

    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "***************** Reportes *****************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Lista de estudiantes" << endl;
        cout << "2. Linealizacion de tareas" << endl;
        cout << "3. Lista de errores" << endl;
        cout << "4. Regresar" << endl;   
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            cdll->print();
            sg->generateGraph(&*cdll);
            break;
        case 2:
            cout << "Muestra la linealizacion de tareas" << endl;
            break;
        case 3:
            cdll->printErrors();
            break;
        case 4:
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }        
    } while(option != 4);
}

//------------------------------------------------------------- EDIT INFORMATION MENU

void editInformation(int selected, string str){
    int option;
    string data;

    do {
        cout << "\n\n\n********************************************" << endl;
        cout << str << endl;    
        cout << "********************************************" << endl;
        cout << "1. Ingresar" << endl;
        cout << "2. Modificar" << endl;
        cout << "3. Eliminar" << endl;
        cout << "4. Regresar" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option) {
        case 1:
            if(selected == 0){
                insertStudent();
            } else{
                cout << "Entraste a ingresar tarea" << endl;
            }
            break;
        case 2:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante ";
                cin >> data;
                modifyStudent(data);
            } else{
                cout << "Entraste a modificar tarea" << endl;
            }
            break;
        case 3:
            if(selected == 0){
                cout << "Ingresa el DPI del estudiante ";
                cin >> data;
                if(cdll->searchStudent(data)){
                    cdll->deleteStudent(data);
                } else {
                    cout << "\t\t\t\t\t    error - No existe estudiante con DPI " << data << endl;
                }
            } else{
                cout << "Entraste a eliminar tarea" << endl;
            }
            break;
        case 4:            
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while(option != 4);
}


//------------------------------------------------------------- SELECT MENU

void manualInput(){
    int option;
    string str = "";
    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "************** Ingreso Manual **************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Estudiante" << endl;
        cout << "2. Tarea" << endl;
        cout << "3. Regresar" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            str = "************ Editar Estudiante *************";
            editInformation(0, str);
            break;
        case 2:
            str = "*************** Editar Tarea ***************";             
            editInformation(1, str);
        case 3:
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while (option != 3);
}

//------------------------------------------------------------- INT MAIN

int main(){
    system("cls");
    setlocale(LC_ALL, "");
    int option;
    string studentsPath, homeworkPath;
    cdll = new StudentList<string>();
    
    do{
        cout << "\n\n\n********************************************" << endl;
        cout << "************** Menu Principal **************" << endl;
        cout << "********************************************" << endl;
        cout << "1. Carga de usuarios" << endl;
        cout << "2. Carga de tareas" << endl;
        cout << "3. Ingreso manual" << endl;
        cout << "4. Reportes" << endl;
        cout << "5. Salir" << endl;
        cout << "********************************************" << endl;
        cout << "Ingresa la opcion deseada: ";
        cin >> option;
        Sleep(600);

        switch (option){
        case 1:
            cout << "Ingrese la ruta del archivo *.cvs" << endl;
            cin >> studentsPath;
            readStudents(studentsPath);
            break;
        case 2:
            cout << "Ingrese la ruta del archivo *.cvs" << endl;
            cin >> homeworkPath;
            break;
        case 3:
            manualInput();
            break;
        case 4:
            showReports();
            break;
        case 5:
            cout << "Hasta luego" << endl;
            break;
        default:
            cout << "\t\t\t\t\t    error - Opcion no existente" << endl;
            break;
        }
    } while (option != 5);
    return 0;
}

/*
    cdll = new StudentList<string>();

    cdll->addStudent("207089560", "1234567891230", "Jose Joses Lopez", "Ingenieria", "ingelover", "50", "24", "inge@gmail.com");  
    cdll->addStudent("201700000", "1234567891231", "Juanito sEstrada", "Ingenieria", "inover", "50", "240", "inge@gmail.com");  
    cdll->addStudent("201711111", "1234567891232", "Leidy Ramesn", "Ingenieria", "ingeler", "50", "2", "inge@gmail.com");  
    cdll->addStudent("201733333", "1234567891233", "Jonh Wick", "Ingenieria", "ingelov", "5", "4", "inge@gmail.com");  

    cdll->deleteStudent("1234567891230");

    StudentGraph<string> *sg = new StudentGraph<string>();
    sg->generateGraph(&*cdll);
*/