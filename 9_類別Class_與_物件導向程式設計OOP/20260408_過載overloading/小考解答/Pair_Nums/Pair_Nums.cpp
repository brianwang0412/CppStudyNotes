int cmp(pair_nums &X, pair_nums &Y){
    if (X.a>Y.a) return 1;
    else if (X.a<Y.a) return -1;
    else {
        if (X.b>Y.b) return 1;
        else if (X.b<Y.b) return -1;
        else return 0;
    }
}