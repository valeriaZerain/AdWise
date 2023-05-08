#include <bits/stdc++.h>

using namespace std;

int dp[2000][2000];

//vectores con la informacion de los objetos que pueden seleccionarse
vector<int> precio = {75, 18, 150, 34};
vector<int> beneficio = {86, 38, 74, 24};
vector<string> medComu= {"Instagram", "Periodico", "Vallas publicitarias", "Folletos"};
int presu_guardado = 0;


//Resuelve el problema Knapsack con DP, implementacion Top-Down
int knap(int presupuesto, int index)
{
    if (dp[presupuesto][index] == -1)
    {
        if (presupuesto < 0 || index >= precio.size())
        {
            return 0;
        }
        int maxi = knap(presupuesto, index + 1);
        if (presupuesto - precio[index] >= 0)
        {
            maxi = max(beneficio[index] + knap(presupuesto - precio[index], index + 1), maxi);
        }
        dp[presupuesto][index] = maxi;
    }
    return dp[presupuesto][index];
}

//REQUISITO: ejecutar el metodo Knap antes de este
//Muestra los objetos elegidos al resolver el problema del Knapsack
void mostrarObjetosOptimizados(){

    int y = 0;

    while(presu_guardado > 0 && y <precio.size()){
        if(dp[presu_guardado][y] == 0){
            y++;
        }else if(dp[presu_guardado][y] != dp[presu_guardado][y+1]){
            cout << medComu[y] << endl;
            presu_guardado = presu_guardado - precio[y];
            y++;
        }else{
            y++;
        }
    }

}

//Muestra la informacion de los objetos guardada en
//los vectores: precio, beneficio, medCom
void mostrarObjetos()
{
    for (int i = 0; i < precio.size(); i++)
    {
        cout << endl << "Nombre " << medComu[i] << endl;
        cout << "Precio: " << precio[i] << " ";
        cout << "Beneficio porcentual: " << beneficio[i] << endl;
    }
}

//Se utilizan secuencias ANSI para limpiar los datos de la consola
void clearConsole() {
    cout << "\033[2J\033[1;1H";
}

void esperarAMenu()
{
    cout << endl<< "-------------Escoge una opcion-------------" << endl;
    cout << "1. Salir" << endl;
    cout << "2. Volver al menu" << endl;
    cout << "3. Borrar el historial" << endl;
    cout << "Ingresa tu opcion: ";
    int dum;
    cin >> dum;
    switch (dum)
    {
    case 1:
        cout << "Saliendo del programa...";
        exit(0);
    case 2:
        break;
    case 3:
        clearConsole();
        break;
    default:
        cout << "Ingresa una opcion valida." << endl;
    }
    
}

//Inicia el menu del programa. El switch tiene las opciones que puede elegir el usuario
void iniciarMenu()
{
    int choice;
    int knap_counter = 0;
    do
    {
        cout << endl<< "-------------Escoge una opcion-------------" << endl;
        cout << "1. Realizar optimizacion" << endl;
        cout << "2. Mostrar los medios de comunicacion tomados para maximizar el beneficio" << endl;
        cout << "3. Añadir medio de comunicación junto a su beneficio" << endl;
        cout << "4. Mostrar los medios de comunicacion actuales junto a su precio y beneficio porcentual" << endl;
        cout << "5. Salir" << endl;
        cout << "Ingresa tu opcion: ";
        cin >> choice;
        switch (choice)
        {
        //Llama al metodo knap en base a un presupuesto dado por el usuario
        case 1:
            int presu;
            cout << endl << "Ingresa tu presupuesto: ";
            cin >> presu;
            cout << "Con un presupuesto de " << presu << " se consigue ";
            cout << knap(presu, 0);
            cout << " de beneficio máximo." << endl;
            esperarAMenu();
            presu_guardado = presu;
            break;
        case 2:
            //Si presu_guardado ya cambio su valor de 0 se muestran los objetos seleccionados por el metodo Knap
            if(presu_guardado ==0){
                cout << endl;
                cout << "Vuelve al menu y elige la opcion: '1. Realizar optimizacion' para generar una lista de medios de comunicacion que maximizaran tu beneficio." << endl;
            }else{
                if(dp[presu_guardado][0] == 0){
                    cout << endl << "Con un presupuesto de " << presu_guardado;
                    cout << " no se puede realizar una planificacion que maximice el beneficio." << endl;
                }else{
                    cout << endl << "Con un presupuesto de " << presu_guardado;
                    cout << " se consigue los siguientes medios para la publicacion: " << endl;
                    mostrarObjetosOptimizados();
                }
            }
            esperarAMenu();
            break;
        case 3:
        {
            //Añade un objeto junto a su nombre, precio y beneficio al vector respectivo
            string nombre;
            int nprecio, nw;
            cout << endl << "Ingresa el nombre del nuevo medio de comunicacion: ";
            cin>>ignore;
            getline((cin,nombre);
            cout << "Ingresa el precio del nuevo medio de comunicacion: ";
            cin >> nprecio;
            cout << "Ingresa el valor de beneficio porcentual del nuevo medio de comunicacion: ";
            cin >> nw;
            precio.push_back(nprecio);
            beneficio.push_back(nw);
            medComu.push_back(nombre);
            esperarAMenu();
            break;
        }
        case 4:
            mostrarObjetos();
            esperarAMenu();
            break;
        case 5:
            cout << "Gracias por tu consulta, vuelve pronto!" << endl;
            break;
        default:
            cout << "Ingresa una opcion valida." << endl;
            break;
        }
    } while (choice != 5);
}

int main()
{
    memset(dp, -1, sizeof(dp));
    cout << "Se encuentran los siguientes medios de comunicacion por defecto: " << endl;
    mostrarObjetos();
    cout << "Presiona cualquier tecla para ingresar al menu: ";
    cin.ignore();
    cin.get();
    iniciarMenu();
    return 0;
}
