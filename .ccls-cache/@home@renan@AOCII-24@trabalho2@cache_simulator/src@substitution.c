void PingContexto (uint32_t indice, uint32_t via, Cache *cache) {

    if (cache->contexto == NULL ||
        cache->contexto[indice].pUltimo == NULL ||
        cache->contexto[indice].pUltimo->via == via)
        return;

    Nodo *atual;

    for (atual = cache->contexto[indice].pPrimeiro; atual != NULL &&  atual->via != via; atual = atual->pProx);

    if (atual == cache->contexto[indice].pPrimeiro) {
        cache->contexto[indice].pPrimeiro = atual->pProx;
        if (cache->contexto[indice].pPrimeiro !=  NULL) {
            cache->contexto[indice].pPrimeiro->pAnterior = NULL;
        }
    } else {
        if (atual->pAnterior != NULL)
            atual->pAnterior->pProx = atual->pProx;
        if (atual->pProx != NULL)
            atual->pProx->pAnterior = atual->pAnterior;
    }

    atual->pAnterior = cache->contexto[indice].pUltimo;
    atual->pProx = NULL;

    if (cache->contexto[indice].pUltimo != NULL)
        cache->contexto[indice].pUltimo->pProx = atual;

    cache->contexto[indice].pUltimo = atual;
}
uint32_t SubstituiFIFO (uint32_t indice, Cache *cache) {
    uint32_t via = cache->contexto[indice].pPrimeiro->via;
    PingContexto(indice, via, cache);
    return via;
}
uint32_t SubstituiLRU (uint32_t indice,  Cache *cache) {
    uint32_t via = cache->contexto[indice].pPrimeiro->via;
    PingContexto(indice, via, cache);
    return via;
}

uint32_t SubstituiRANDOM (uint32_t indice, Cache *cache) {
    Nodo *nodo = cache->contexto[indice].pPrimeiro;

    if (nodo != NULL) {
        uint32_t via = nodo->via;
        cache->contexto[indice].pPrimeiro = nodo->pProx;

        if (cache->contexto[indice].pPrimeiro != NULL)
            cache->contexto[indice].pPrimeiro->pAnterior = NULL;

        if (cache->contexto[indice].pPrimeiro == NULL)
            cache->contexto[indice].pUltimo = NULL;

        free(nodo);
        return via;
    }

    return FastRandomUint32(&(cache->seed), cache->assoc);
}

uint32_t SubstituiDIRETO (uint32_t indice, Cache* cache) {
    // escreve sempre na via 0
    return 0U;
}
