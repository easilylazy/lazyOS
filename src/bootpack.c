void LazyMain(void){
    int i;
    for (i = 0xa0000; i <= 0xaffff; i++)
    {
        *(char *)i = i & 0x0f;
    }
    fin:
        goto fin;
}