typedef int tElem;

class ABB
{
private:
    struct Node
    {
        tElem data;
        Node * left;
        Node * rigth;
    };

    Node * root;    // Puntero al primer elemento del abb
    int nElements; // Contador de numeros de elementos

    /**
     * void clearHelp(Node * nodo)
     * ***
     * funcion recursiva para eliminar todos los nodos del ABB
     * ***
     * Input:
     *      Node * nodo :   puntero al nodo a eliminar
    **/
    void clearHelp(Node * nodo){
        if (nodo == nullptr)
        {
            return;
        }
        clearHelp(nodo->left);
        clearHelp(nodo->rigth);
        delete nodo;
    }

    /**
     * bool findHelp(Node * nodo, tElem item)
     * ***
     * funcion recursiva de busqueda del ABB
     * ***
     * Input:
     *      Node * nodo :   puntero al nodo actual
     *      tElem item  :   elemento a buscar
     * ***
     * Return:
     *      bool    :   True si encuentra el dato, False en caso contrario
    **/
    bool findHelp(Node * nodo, tElem item){
        if(nodo == nullptr) return 0;
        if(nodo->data == item) return 1;
        if (item < nodo->data){
            return findHelp(nodo->left, item);
        } else {
            return findHelp(nodo->rigth, item);
        }
    }

    /**
     * bool insertHelp(Node * prev, Node * nodo, tElem item)
     * ***
     * funcion recurdiva de interrcion del ABB
     * ***
     * Input:
     *      Node * prev :   puntero al nodo anterior
     *      Node * nodo :   puntero al nodo actual
     *      tElm item   :   elemento a insertar
     * ***
     * Return:
     *      bool    :   True si se inserta un elemento, False si ya existe en el ABB
    **/
    bool insertHelp(Node * prev, Node * nodo, tElem item){
        if (nodo == nullptr){
            if (item < prev->data){
                prev->left = new Node;
                prev->left->data = item;
                prev->left->left = nullptr;
                prev->left->rigth = nullptr;
                nElements++;
                return 1;
            } else {
                prev->rigth = new Node;
                prev->rigth->data = item;
                prev->rigth->left = nullptr;
                prev->rigth->rigth = nullptr;
                nElements++;
                return 1;
            }
        }
        if (item == nodo->data) return 0;
        if (item < nodo->data){
            return insertHelp(nodo, nodo->left, item);
        } else {
            return insertHelp(nodo, nodo->rigth, item);
        }
    }

    /**
     * tElem lower_boudHelp(Node * nodo, tElem item, bool & found)
     * ***
     * Funcion recursiva de busqueda del primer menor o igual de un elemento del ABB
     * ***
     * Input:
     *      Node * nodo :   Puntero al nodo actual
     *      tElem item  :   Elemento a buscar el primer menor o igaul
     *      bool & found    :   Referencia de un flag si ya es encontrado o no
     * ***
     * Return:
     *      tElem   :   Elemento del primer menor o igual, retorna -1 si no existe
    **/
    tElem lower_boudHelp(Node * nodo, tElem item, bool & found){
        if (nodo == nullptr){   //Si llega a al final, no existe
            found = false;
            return -1;
        }
        if (item == nodo->data){    //Si es igual, existe y retorna
            found = true;
            return nodo->data;
        }

        if (item < nodo->data){     //Paso a la izq
            return lower_boudHelp(nodo->left, item, found);
        } else {    //  Paso a al der si es mayo o igual, si existe
            tElem rigth_val = lower_boudHelp(nodo->rigth, item, found); // Paso a la der
            if (found == false) {   // Si llega a nullptr el valor en que esta es el menor
                found = true;
                return nodo->data;
            } else {
                return rigth_val;   // Si no, el valor a la der es el menor o igual
            }
        }
    }

public:
    ABB();

    void clear();

    bool find(tElem item);

    bool insert(tElem item);

    tElem lower_boud(tElem item);

    int getSize();

    ~ABB();
};

/**
 * ABB::ABB()
 * ***
 * Construcctor, inicializa el ABB vacia
 * O(1)
**/
ABB::ABB()
{
    root = nullptr;
    nElements = 0;
}

/**
 * void ABB::clear()
 * ***
 * Elimina todos los elemnetos del ABB, entregrandolo vacia
 * O(n)
**/
void ABB::clear()
{
    clearHelp(root);
    root = nullptr;
    nElements = 0;
}

/**
 * bool ABB::find(tElem item)
 * ***
 * Busca si existe un elemento en el ABB
 * O(log n)
 * ***
 * Input:
 *      tElem item  :   Elemento a buscar
 * ***
 * Return:
 *      bool    :   Falso si no existe, True si existe
**/
bool ABB::find(tElem item)
{
    return findHelp(root, item);
}

/**
 * bool ABB::insert(tElem item)
 * ***
 * Inserta un elemento en el ABB, solo elementos unicos, no repetidos.
 * O(log n)
 * ***
 * Input:
 *      tElem item  :   Elemento a insertar
 * ***
 * Return:
 *      bool    :   Falso si ya existe en el ABB, True si se realiza exitosamente
**/
bool ABB::insert(tElem item)
{
    if(root == nullptr){
        root = new Node;
        root->data = item;
        root->left = nullptr;
        root->rigth = nullptr;
        nElements++;
        return 1;
    }
    return insertHelp(nullptr, root, item);
}

/**
 * tElem ABB::lower_boud(tElem item)
 * ***
 * Busca el primer menor o igual de un elemento en el ABB
 * O(log n)
 * ***
 * Input:
 *      tElem item  :    Elemento a buscar el primer menor o igual
 * ***
 * Return:
 *      tElem   :   Retorna el primer menor o igual elemento en el ABB. Si no exite retorna -1
**/
tElem ABB::lower_boud(tElem item)
{
    bool found = true;
    return lower_boudHelp(root, item, found);
}

/**
 * int ABB::getSize()
 * ***
 * Retorna el numero de elementos que hay en el ABB
 * O(1)
 * ***
 * Return:
 *      int :   numero de elementos que hay en el ABB
**/
int ABB::getSize()
{
    return nElements;
}

/**
 * ABB::~ABB()
 * ***
 * Destructor
 * O(n)
**/
ABB::~ABB()
{
    clear();
}
