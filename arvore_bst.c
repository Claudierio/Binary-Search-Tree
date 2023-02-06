//Arvore Binária de Busca (Binary Search Tree)
//Node == Nó
//root == Raiz
//tree == arvore

#include<stdio.h>
#include<stdlib.h>

struct item{

    int cod;
};

typedef struct item Item;

struct node {
    Item item;
    struct node *left;
    struct node *right;
};

typedef struct node Node;

//Inicializar uma ávore
Node *treeInitialize() {
    return NULL;
}

//funcao que retorna o item
Item itemCreate(int cod){
    Item item;
    item.cod = cod;
    return item;
}


//Inserir
Node *treeInsert(Node *root, Item x) {
    if(root == NULL){
        Node *aux = (Node*)malloc(sizeof(Node));
        aux -> item = x;
        aux->left = NULL;
        aux->right = NULL;
        return aux;
    }
    //caso o nó nao seja nulo, quer dizer que tem alguém lá dentro
    else{
        if(x.cod > root->item.cod){
            root -> right = treeInsert(root->right, x);
        }
        else if (x.cod < root->item.cod){
            root-> left = treeInsert(root->left, x);
        }

    }
    return root;
}

//Funcao recursiva de imprimir
//Ela recebe um nó qualquer, se for diferente de nulo, sai imprimindo esse primeiro elemento e depois vou fazer chamadas recursivas sempre tendendo ir pra esquerda primeiro e depois de todas as esquerdas ele vai pra direita
void treePrint(Node *root) {
    if(root != NULL){
        printf("%d", root->item.cod);
        treePrint(root->left);
        treePrint(root->right);
    }
}

void treeFree(Node *root) {
    if(root != NULL){

        treeFree(root->left);
        treeFree(root->right);
        free(root);
    }
}

//Funcao buscar elementos
Node *treeSearch(Node *root, int cod){
    if(root != NULL){
        if(root->item.cod == cod) return root;
        else{
            if(cod > root->item.cod) return treeSearch(root->right,cod);
            else return treeSearch(root->left, cod);
        }
    }
}
//Funcao de achar quem é nosso menor elemento da maior subarvore
Node *treeMin(Node *root){
    if(root != NULL){
        Node *aux = root;

        while(aux->left != NULL)
        {
            aux = aux->left;
        }
        return aux;
    }
}


//Função remover 
Node  *treeRemove(Node *root, int cod){
    if(root != NULL){
        if(cod > root->item.cod)
        {
            root->right = treeRemove(root->right, cod);
        }
        else if(cod < root-> item.cod)
        {
            root->left = treeRemove(root->left, cod);
        }
        else
        {
            //Quando não tem filhos em baixo
            if(root->left == NULL && root -> right == NULL)
            {
                free(root);
                return NULL;
            }
            //Quando ele tem um filho a direita
            else if(root ->left == NULL && root->right != NULL)
            {
                Node *aux = root->right;
                free(root);
                return aux;
            }
            //Quando ele tem um filho a esquerda
            else if(root->left != NULL && root->right == NULL)
            {
                Node *aux = root->left;
                free(root);
                return aux;
            }
            //Quando tem dois filhos
            else
            {
                Node *aux = treeMin(root->right);
                Item itemAux = aux->item; //fiz uma copia
                root = treeRemove(root, itemAux.cod); //removi o item
                root->item = itemAux; //o item da raiz recebeu o item auxiliar
            }
        }
        return root;
    }
    return NULL;

}

int main() {

    Node *root = treeInitialize();
    root = treeInsert(root, itemCreate(10));
    root = treeInsert(root, itemCreate(15));
    root = treeInsert(root, itemCreate(20));
    root = treeInsert(root, itemCreate(12));
    root = treeInsert(root, itemCreate(5));

    printf("\n>> Antes de remover: ");

    treePrint(root);
    root = treeRemove(root, 10);

    printf("\n>> Depois de remover:");
    treePrint(root);
    
/*
    if(tmp == NULL) printf(">> Elemento nao encontrado! \n");
    else printf(">>Elemento Encontrado \n");
*/
    printf("\n");
    treeFree(root);

    return 0;
}