template <class tipoPriority, class tipoInfo> class PriorityQueue
{
private:
    struct Node
    {
        tipoPriority Priority;
        tipoInfo data;

        /**
         * void push_back(tipoPriority P, tipoInfo I)
         * ***
         * Inserta los elementos P, I en el nodo
         * O(1)
         * ***
         * Inputs:
         *      tipoPriority P  :   valor de la prioridad del dato
         *      tipoInfo I      :   dato a insertar
        **/
        void push_back(tipoPriority P, tipoInfo I){
            Priority = P;
            data = I;
        }
    };
    
    Node * Heap = nullptr;
    int MaxSize;
    int Size;

    bool Max_Heap;
    bool Min_Heap;

    /**
     * void swap(Node * a, Node * b)
     * ***
     * Intercambia los contenidos de dos nodos a y b
     * O(1)
     * ***
     * Inputs:
     *      Node * a    :   Direccion del elemento a
     *      Node * b    :   Direccion del elemento b
    **/
    void swap(Node * a, Node * b){
        Node temp = *b;
        *b = *a;
        *a = temp;
    }

    /**
     * int compare(Node Heap[], int a, int b)
     * ***
     * Compara las PRIORIDAD de los elementos del index a con el index b contenidos en el Heap
     * O(1)
     * ***
     * Inputs:
     *      Node Heap[] :   Array correspondiente al Heap
     *      int a   :   Index del elemento a
     *      int b   :   Index del elemento b
     * ***
     * Returns:
     *      int :   Index del elemento comparado segun tipo de Heap
    **/
    int compare(Node Heap[], int a, int b){
        if (Min_Heap)
        {
            return (Heap[a].Priority < Heap[b].Priority) ? a : b;
        }

        if (Max_Heap)
        {
            return (Heap[a].Priority > Heap[b].Priority) ? a : b;
        }
        return 0;
    }

    /**
     * void pungleHeap(Node Heap[], int i)
     * ***
     * Realiza algoritmo de ordenamiento del Heap con el nodo i y los hijos izquierdo y derecho
     * flotando el elemento segun el Min/Max Heap
     * O(log n)
     * ***
     * Inputs:
     *      Node Heap[] :   Array correspondiente al Heap
     *      int i   :   Index de la raiz a comparar
    **/
    void floatHeap(Node Heap[], int i){
        int left, rigth, pos;

        pos = i;
        left = 2 * pos;
        rigth = 2 * pos + 1;

        //  El Max/Min de los hijos de la raiz
        if (left <= Size) {
            pos = compare(Heap, left, pos);
        }
        if (rigth <= Size) {
            pos = compare(Heap, rigth, pos);
        }
        
        //  Intercambiar Root con el Min/Max y continuar
        if (pos != i)
        {
            swap(&Heap[i], &Heap[pos]);
            floatHeap(Heap, pos);
        }
    }

    /**
     * void resize()
     * ***
     * Aumenta el tamanio por el doble del Heap si se llena
     * O(n)
    **/
    void resize(){
        int newMaxSize = MaxSize * 2;
        Node * newHeap = new Node[newMaxSize+1];

        for (int i = 1; i <= Size; i++)
        {
            newHeap[i].push_back(Heap[i].Priority, Heap[i].data);
        }
        
        MaxSize = newMaxSize;
        delete[] Heap;
        Heap = newHeap;
    }

public:
    PriorityQueue(const bool tipo);

    void clear();

    tipoInfo front();

    void pop();

    void insert(tipoPriority prio, tipoInfo data);

    int size();

    ~PriorityQueue();
};

/**
 * PriorityQueue<tipoPriority, tipoInfo>::PriorityQueue(const bool tipo)
 * ***
 * Contructor de la cola de prioridad, decide de que tipo es el Heap
 * If (true) -> Max-Heap
 * If (false) -> Min-Heap
 * O(1)
 * ***
 * Inputs:
 *      cont bool tipo  :   Boleano para decidir si es Max heap o Min heap
**/
template <class tipoPriority, class tipoInfo> PriorityQueue<tipoPriority, tipoInfo>::PriorityQueue(const bool tipo)
{
    MaxSize = 8;    //  Tamanio inicial
    Size = 0;
    Heap = new Node[MaxSize+1]; //  Salta el primer elemento

    if (tipo)
    {
        Max_Heap = true;
        Min_Heap = false;

    } else {
        Max_Heap = false;
        Min_Heap = true;
    }
}

/**
 * void PriorityQueue<tipoPriority, tipoInfo>::clear()
 * ***
 * Vacia la PriorityQueue
 * O(1)
*/
template <class tipoPriority, class tipoInfo> void PriorityQueue<tipoPriority, tipoInfo>::clear()
{
    Size = 0; //    Si Size es 0, no posee elemento. 
}

/**
 * tipoInfo PriorityQueue<tipoPriority, tipoInfo>::front()
 * ***
 * Accsede al elemento de mayor prioridad en la cola
 * si cola es vacia, conducta inderterminada
 * O(1)
 * ***
 * Return:
 *      TipoInfo    :   Elemento de mayor prioridad en la cola
**/
template <class tipoPriority, class tipoInfo> tipoInfo PriorityQueue<tipoPriority, tipoInfo>::front()
{
    return Heap[1].data;
}

/**
 * void PriorityQueue<tipoPriority, tipoInfo>::pop()
 * ***
 * Elimina el elemento de mayor prioridad e la cola
 * si cola es vacia, conducta inderterminada
 * O(log n)
**/
template <class tipoPriority, class tipoInfo> void PriorityQueue<tipoPriority, tipoInfo>::pop()
{
    swap(&Heap[1], &Heap[Size]);
    Size--;
    floatHeap(Heap, 1);
}

/**
 * void PriorityQueue<tipoPriority, tipoInfo>::insert(tipoPriority prio, tipoInfo data)
 * ***
 * Inserta un elemento con su debida prioridad a la cola
 * O(log n)
 * ***
 * Inputs:
 *      tipoPriority prio   :   Prioridad del elemento a insertar
 *      tipoInfo    data    :   Dato a insertar
**/
template <class tipoPriority, class tipoInfo> void PriorityQueue<tipoPriority, tipoInfo>::insert(tipoPriority prio, tipoInfo data)
{
    if (Size == 0)
    {
        Heap[1].push_back(prio, data);
        Size++;

    } else {
        Heap[++Size].push_back(prio, data);

        for (int i = Size / 2; i > 0; i--)
        {
            floatHeap(Heap, i);
        }
    }

    if (Size >= MaxSize)
    {
        resize();
    } 
}

/**
 * int PriorityQueue<tipoPriority, tipoInfo>::size()
 * ***
 * Entrega el tamanio actual de la pila de prioridad
 * O(1)
 * ***
 * Returns:
 *      int :   tamanio actual
**/
template <class tipoPriority, class tipoInfo> int PriorityQueue<tipoPriority, tipoInfo>::size()
{
    return Size;
}

/**
 * PriorityQueue<tipoPriority, tipoInfo>::~PriorityQueue()
 * ***
 * Destructor de la cola
 * O(1)
**/
template <class tipoPriority, class tipoInfo> PriorityQueue<tipoPriority, tipoInfo>::~PriorityQueue()
{
    delete[] Heap;
}
