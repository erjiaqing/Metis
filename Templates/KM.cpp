int weight[M][M], lx[M], ly[M];
bool sx[M], sy[M];
int match[M];
bool search_path(int u){
	sx[u] = true;
	for (int v = 0; v < n; v++){
		if (!sy[v] && lx[u] + ly[v] == weight[u][v]){
			sy[v] = true;
			if (match[v] == -1 || search_path(match[v])){
				match[v] = u;
				return true;
			}
		}
	}
	return false;
}

int KM()
{
	for (int i = 0; i < n; i++){
		lx[i] = ly[i] = 0;
		for (int j = 0; j < n; j++)
			if (weight[i][j] > lx[i])
				lx[i] = weight[i][j];
	}
	memset(match, -1, sizeof(match));
	for (int u = 0; u < n; u++){
		while (1){
			memset(sx, 0, sizeof(sx));
			memset(sy, 0, sizeof(sy));
			if (search_path(u)) break;
			
			int inc = len * len;
			for (int i = 0; i < n; i++)
            if (sx[i])
            for (int j = 0; j < n; j++)
            if (!sy[j] && ((lx[i] + ly[j] - weight[i][j]) < inc))
                inc = lx[i] + ly[j] - weight[i][j];
			for (int i = 0; i < n; i++){
				if (sx[i]) lx[i] -= inc;
				if (sy[i]) ly[i] += inc;
			}
		}
	}
	int sum = 0;
	for (int i = 0; i < n; i++)
    if (match[i] >= 0) sum += weight[match[i]][i];
	return sum;
}

int main()
{
	memset(weight, 0, sizeof(weight));
	for (int i = 1; i <= len; i++)
		weight[a[i]][b[i]]++;
	cout<<KM()<<endl;
	return 0;
}
