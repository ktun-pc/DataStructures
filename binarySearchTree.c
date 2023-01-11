#include <stdio.h>
#include <stdlib.h>

// Agac yapisinin her bir dugumu
typedef struct Node
{
    // Dugumun degeri
    int value;
    // Dugumun sol cocugu
    struct Node *left;
    // Dugumun sag cocugu
    struct Node *right;
} Node;

// Ekleme
Node * Add(Node *root, int value)
{
    Node *node = malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;

    // Eger kok NULL ise yeni dugumu kok olarak geriye dondur
    if (root == NULL)
    {
        return node;
    }

    // Gecici degiskene koku ata
    Node *tmp = root;
    
    // Kucukleri sola buyukleri ise saga atayacagimiz dongu
    while (1)
    {
        // Eger yeni dugumun degeri gecicideki degerden kucukse
        if (node->value < tmp->value)
        {
            // Eger gecicinin solu bos ise soluna ekleme yap ve donguden cik
            if (tmp->left == NULL)
            {
                tmp->left = node;
                break;
            }
            
            // Geciciyi soluna esitle
            tmp = tmp->left;
        }
        // Eger yeni dugumun degeri gecicideki degerden buyuk ya da esitse
        else
        {
            // Eger gecicinin sagi bos ise sagina ekleme yap ve donguden cik
            if (tmp->right == NULL)
            {
                tmp->right = node;
                break;
            }

            // Geciciyi sagina esitle
            tmp = tmp->right;
        }
    }

    // Geriye degismemis kok dugumu dondur
    return root;
}

// Silme
void DeleteTree(Node *root)
{
    // Eger kok dugum NULL ise geri don
    if (root == NULL) return;
    // Dugumun solunu recursive olarak sil
    DeleteTree(root->left);
    // Dugumun sagini recursive olarak sil
    DeleteTree(root->right);
    // Dugumun kendisini sil
    free(root);
}

// Pre Order olarak yazdirma
void PreOrder(Node *root)
{
    if (root == NULL) return;
    // Once koku yazdir
    printf("%d ", root->value);
    // Daha sonra ise sag ve sol cocugu recursive olarak yazdir
    PreOrder(root->left);
    PreOrder(root->right);
}

void InOrder(Node *root)
{
    if (root == NULL) return;
    // Once sol dugumu recursive olarak yazdir
    InOrder(root->left);
    // Daha sonra kok dugumu yazdir
    printf("%d ", root->value);
    // En son sag dugumu recursive olarak yazdir
    InOrder(root->right);
}

void PostOrder(Node *root)
{
    if (root == NULL) return;
    // Once sag ve sol cocugu recursive olarak yazdir
    PostOrder(root->left);
    PostOrder(root->right);
    // En son kok dugumu yazdir
    printf("%d ", root->value);
}

// Sadece yaprak dugumleri yazdir
void PrintLeafNodes(Node *root)
{
    if (root == NULL) return;

    // Eger sag ve sol NULL ise cocugu yoktur yani yaprak dugumdur
    if (root->left == NULL && root->right == NULL)
    {
        printf("%d\n", root->value);
    }

    PrintLeafNodes(root->left);
    PrintLeafNodes(root->right);
}

// Dugum sayisini donduren fonksiyon
int GetNodeCount(Node *root)
{
    if (root == NULL) return 0;

    // Dugumun kendisi ile sol ve sag cocuklarinin
    // adetini toplayi geriye dondur
    int count = 1;
    count += GetNodeCount(root->left);
    count += GetNodeCount(root->right);
    return count;
}

// Dugumdeki degerlerin toplamini donduren fonksiyon
int GetTotalValue(Node *root)
{
    if (root == NULL) return 0;

    // Dugumun kendisi ile sol ve sag cocuklarinin
    // degerlerini toplayi geriye dondur
    int value = root->value;
    value += GetTotalValue(root->left);
    value += GetTotalValue(root->right);
    return value;
}

// Agacin ortalama degerini ekrana yazdirma
void CalculateAverageValue(Node *root)
{
    int count = GetNodeCount(root);
    int total = GetTotalValue(root);

    printf("%f\n", (float)total / count);
}

// Sadece sol ve sag cogucu olanlari ekrana yazdirma
void PrintFullyChildRoots(Node *root)
{
    if (root == NULL) return;

    // Solu ve sagi NULL degilse yazdir
    if (root->left != NULL && root->right != NULL)
    {
        printf("%d\n", root->value);
    }

    PrintFullyChildRoots(root->left);
    PrintFullyChildRoots(root->right);
}

// Sol ve sag cocuk sayisi arasindaki farki ekrana yazdirma (sag - sol)
void PrintChildDifference(Node *root)
{
    int left = GetNodeCount(root->left);
    int right = GetNodeCount(root->right);

    printf("%d\n", right - left);
}

//       3
//     /   \
//    2     5
//   /     / \
//  1     4   6

// Pre  Order: 3  2  1  5  4  6
// In   Order: 1  2  3  4  5  6
// Post Order: 1  2  4  6  5  3

int main(void)
{
    Node *root = NULL;
    root = Add(root, 3);
    root = Add(root, 5);
    root = Add(root, 2);
    root = Add(root, 1);
    root = Add(root, 4);
    root = Add(root, 6);
    
    // PreOrder(root);
    // printf("\n");
    // InOrder(root);
    // printf("\n");
    // PostOrder(root);
    // printf("\n");

    // PrintLeafNodes(root);
    
    // CalculateAverageValue(root);

    // PrintFullyChildRoots(root);

    PrintChildDifference(root);

    DeleteTree(root);
    return 0;
}
