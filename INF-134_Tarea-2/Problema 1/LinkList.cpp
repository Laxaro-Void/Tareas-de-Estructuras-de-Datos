typedef int tList;

class LinkList
{
private:
    struct Node
    {
        tList data;
        Node * next;
    };

    Node * head;    // Inicio de la Lista
    Node * tail;    // Ultimo de la Lista
    Node * curr;    // Nodo ANTERIOR del Nodo acutal
    unsigned int listSize;  //  Tamanio de la Lista
    unsigned int pos;       //  Posicion Actual

public:
    LinkList();

    ~LinkList();

    void clear();

    unsigned int insert(tList item);

    unsigned int append(tList item);

    unsigned int replace(tList item);
    
    tList erase();

    void moveToStart();

    void moveToEnd();

    void next();

    void prev();

    unsigned int length();

    unsigned int currPos();

    void moveToPos(unsigned int posicion);

    tList getValue();
};

/**
 * LinkList::LinkList()
 * ***
 * Constructor, inicializa la lista vacia.
 * O(1)
**/
LinkList::LinkList()
{
    head = tail = curr = new Node;  //DUMY NODE
    listSize = 0;
    pos = 0;
}

/**
 * unsigned int LinkList::insert(tList item)
 * ***
 * Inserta un elemento en la posicion actual
 * O(1)
 * ***
 * Input:
 *      tList item  :   Elemento a insertar
 * ***
 * Return:
 *      unsigned int    :   Retorna la posicion en donde es insertado el elemento
**/
unsigned int LinkList::insert(tList item){
    Node * aux = curr->next;
    curr->next = new Node;

    curr->next->data = item;
    curr->next->next = aux;

    if (curr == tail)
    {
        tail = curr->next;
        tail->next = nullptr;
    }
    
    listSize++;
    return pos;
}

/**
 * unsigned int LinkList::append(tList item)
 * ***
 * Agrega un elemento al final de la lista
 * O(1)
 * ***
 * Input:
 *      tList item  :   Elemento a agregar
 * ***
 * Return:
 *      unsigned int    :   Retorna la posición en donde es insertado el elemento
**/
unsigned int LinkList::append(tList item){
    tail->next = new Node;
    tail = tail->next;

    tail->data = item;
    tail->next = nullptr;

    listSize++;
    return listSize-1;
}

/**
 * unsigned int LinkList::replace(tList item)
 * ***
 * Remplaza el contenido de la posición actual por otro
 * O(1)
 * ***
 * Input:
 *      tList item  :   Elemento a agregar
 * ***
 * Return:
 *      unsigned int    :   Retorna la posición en donde es remplazado el elemento
**/
unsigned int LinkList::replace(tList item){
    curr->next->data = item;
    return pos;
}

/**
 * tList LinkList::erase()
 * ***
 * Elimina el contenido de la posicion actual, retorna el elemento eliminado
 * O(1)
 * ***
 * Return:
 *      tList   :   Elemento eliminado de la posicion actual
**/
tList LinkList::erase(){

    Node * aux = curr->next;
    tList data = aux->data;

    curr->next = aux->next;

    if(aux == tail){
        tail = curr;
    }

    delete aux;

    listSize--;

    return data;
}

/**
 * void LinkList::clear()
 * ***
 * Elimina todos los elementos de la lista, vaciando la lista
 * O(n)
**/
void LinkList::clear(){
    Node * aux = head;
    curr = head;

    while (aux != tail)
    {
        aux = head->next;
        head->next = aux->next;
        delete aux;
    }

    tail = head;
    pos = 0;
    listSize = 0;
}

/**
 * void LinkList::moveToStart()
 * ***
 * Mueve el puntero de posicion al inicio de la lista
 * O(1)
**/
void LinkList::moveToStart(){
    curr = head;
    pos = 0;
}

/**
 * void LinkList::moveToEnd()
 * ***
 * Mueve el puntero de posicion al final de la lista
 * O(n)
**/
void LinkList::moveToEnd(){
    Node * aux = head;
    while (aux->next != tail){
        aux = aux->next;
    }
    pos = listSize;
}

/**
 * void LinkList::moveToPos(unsigned int posicion)
 * ***
 * Mueve el puntero de posicion a un lugar deseado
 * O(n)
 * ***
 * Input:
 *      unsigned int posicion   :   numero de posicion deseada
**/
void LinkList::moveToPos(unsigned int posicion){
    unsigned int i;
    if (posicion < 0 || posicion > listSize)
    {
        return;
    }

    curr = head;
    pos = 0;
    for (i = 0; i < posicion; i++)
    {
        curr = curr->next;
        pos++;
    }
}

/**
 * void LinkList::next()
 * ***
 * Mueve el puntero de posicion al elemento siguiente
 * O(1)
**/
void LinkList::next(){
    if (curr == tail) return;
    curr = curr->next;
    pos++;
}

/**
 * void LinkList::prev()
 * ***
 * Mueve el puntero al elemento anterior
 * O(n)
**/
void LinkList::prev(){
    if (curr == head) return;
    Node * aux = head;
    while (aux->next != curr)
    {
        aux = aux->next;
    }
    curr = aux;
    pos--;
}

/**
 * unsigned int LinkList::length()
 * ***
 * Entrega el tamanio actual de la lista
 * O(1)
 * ***
 * Return:
 *      unsigned int    :   tamanio actual de la lista
**/
unsigned int LinkList::length(){
    return listSize;
}

/**
 * unsigned int LinkList::currPos()
 * ***
 * Entrega la poscion actual en la lista
 * O(1)
 * ***
 * Return:
 *      unsigned int    :   posicion actual en la lista
**/
unsigned int LinkList::currPos(){
    return pos;
}

/**
 * tList LinkList::getValue()
 * ***
 * Entrega el valor de la poscion actual en la lista
 * O(1)
 * ***
 * Return:
 *      tList   :   valor de la posicion actual en la lsita
**/
tList LinkList::getValue(){
    return curr->next->data;
}

/**
 * LinkList::~LinkList()
 * ***
 * Destructor de la lista
 * O(n)
**/
LinkList::~LinkList(){
    clear();
    delete head;
}
