def pai(index):
    return int((index-1)/2)
def filhoEsquerdo(index):
    return 2*index +1
def filhoDireito(index):
    return 2*index+2

def downHeap(minHeap: list, novoIndex = 0):
    idxEqd = filhoEsquerdo(novoIndex)
    idxDrt = filhoDireito(novoIndex)
    maior = novoIndex

    if minHeap[idxEqd] > minHeap[maior]:
        maior = idxEqd
    if minHeap[idxDrt] > minHeap[maior]:
        maior = idxDrt

def upHeap(minHeap: list, novoIndex = 0):
    if novoIndex == 0:
        indexDoUltimo = len(minHeap)-1
    else:
        indexDoUltimo = novoIndex
    
    indexPai = pai(indexDoUltimo)

    if minHeap[indexDoUltimo] < minHeap[indexPai]:
        temp = minHeap[indexPai]
        minHeap[indexPai] = minHeap[indexDoUltimo]
        minHeap[indexDoUltimo] = temp
        upHeap(minHeap, indexPai)

def inserirMinHeap(minHeap: list, novoElemento: int):
    minHeap.append(novoElemento)
    upHeap(minHeap)


def imprimirHeap(minHeap: list):
    if len(minHeap) == 0:
        print("Lista Vazia!")
        return
    print(f"Exibindo como Array:\n{minHeap}\n")

    nivel= 0
    elementoNoNivel = 1
    contador = 0

    for i in range(len(minHeap)):
        print(f"{minHeap[i]}", end=" ")
        contador+=1
        if contador == elementoNoNivel:
            print("\n", end="")
            nivel+=1
            elementoNoNivel*=2
            contador = 0


# Para teste individual
if __name__ == "__main__":
    lista = list()

    inserirMinHeap(lista, 2)
    inserirMinHeap(lista, 1)
    inserirMinHeap(lista, 4)
    inserirMinHeap(lista, 0)
    inserirMinHeap(lista, 7)
    imprimirHeap(lista)