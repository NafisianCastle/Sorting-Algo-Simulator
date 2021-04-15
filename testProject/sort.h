
class insertionSort{
public:
  insertionSort(int* arr,int N);
  void sort(int* arr,int N);
  void exchange(int* arr,int i,int j);
};
insertionSort::insertionSort(int* arr,int N){
  sort(arr,N);
}
void insertionSort::sort(int* arr,int N){
  for(int i=1;i<N;i++)
  {
      for(int j=i;j>=1;j--)
      {
          compares++;
          if(arr[j]<arr[j-1])
              {
                exchanges++;
                exchange(arr,j,j-1);
                visual(arr);
              }
          else
              break;
      }
  }
}
void insertionSort::exchange(int* arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

class selectionSort{
public:
  selectionSort(int* arr,int N);
  void sort(int* arr,int N);
  void exchange(int* arr,int i,int j);
};
selectionSort::selectionSort(int* arr,int N){
  sort(arr,N);
}
void selectionSort::sort(int* arr,int N)
{
    for(int i=0;i<N-1;i++)
    {
        int ind = i;
        for(int j=i+1;j<N;j++)
        {
            compares++;
            if(arr[j]<arr[ind])
                ind = j;
        }
        exchanges++;
        exchange(arr,i,ind);
        visual(arr);
    }
}
void selectionSort::exchange(int* arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

class shellSort{
public:
  shellSort(int* arr,int N);
  void sort(int* arr,int N);
  void exchange(int* arr,int i,int j);
};
shellSort::shellSort(int* arr,int N)
{
  sort(arr,N);
}
void shellSort::sort(int* arr,int N)
{
    // using sequence for h to 3x+1
    int h=1;
    while(h<N/3)
    {
        h = 3*h+1;
    }
    while(h>=1)
    {
        for(int i=h;i<N;i++)
        {
            for(int j=i;j>=h;j-=h)
            {
                compares++;
                if(arr[j]<arr[j-h])
                    {
                      exchanges++;
                      exchange(arr,j,j-h);
                      visual(arr);
                    }
                else
                    break;
            }
        }
        h /= 3;
    }
}
void shellSort::exchange(int* arr,int i,int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// can be improved by using insertion sort for small size array
// instead of taking first element as partitioning element
// can sample the array and take median of first last and middle elements
class quickSort{
public:
  quickSort(int* arr,int N);
  void sort(int* arr,int lo,int hi);
  void sort_shuffle(int* arr,int i,int j);
  int part(int* arr,int lo,int hi);
  void exchange(int* arr,int i,int j);
};
quickSort::quickSort(int* arr,int N){
  sort_shuffle(arr,0,N);
}
void quickSort::sort_shuffle(int* arr,int i,int j)
{
  std::random_shuffle(arr,arr+j);
  sort(arr,i,j);
}
void  quickSort::sort(int* arr,int lo,int hi)
{
  visual(arr);
  if(lo>=hi)
  return;
  int j = part(arr,lo,hi);
  sort(arr,lo,j-1);
  visual(arr);
  sort(arr,j+1,hi);
  visual(arr);
}

int quickSort::part(int* arr,int lo,int hi)
{
    int i = lo,j = hi+1;
    while(true)
    {
        while(arr[++i]<arr[lo])
        {
          compares++;
            if(i == hi)
                break;
        }
        while(arr[lo]<arr[--j])
        {
          compares++;
            if(j==lo)
                break;
        }
        if(i>=j)
            break;
        exchanges++;
        exchange(arr,i,j);
        visual(arr);
    }
    exchanges++;
    exchange(arr,lo,j);
    visual(arr);
    return j;
}
void quickSort::exchange(int* arr,int i,int j)
{
  int temp = arr[i];
  arr[i] = arr[j];
  arr[j] = temp;
}

class mergeSort{
public:
  mergeSort(int* arr,int N);
  void sort(int* arr,int* aux,int lo,int hi);
  void merge(int* arr,int* aux,int low,int mid, int high);
};
mergeSort::mergeSort(int* arr,int N){
  int aux[N];
  for(int i=0;i<N;i++){
    aux[i] = arr[i];
  }
  sort(arr,aux,0,N-1);
}
void mergeSort::sort(int* arr,int* aux,int low,int high)
{
  compares++;
  if(low>=high)
  return;
  int mid = low + (high-low)/2;
  sort(arr,aux,low,mid);
  visual(arr);
  sort(arr,aux,mid+1,high);
  visual(arr);
  merge(arr,aux,low,mid,high);
  visual(arr);
}
void mergeSort::merge(int* arr,int* aux,int low,int mid, int high)
{
    int i=low,j=mid+1;
    // This step can be optimized by alternatively using aux and arr array
    // as the auxilary array
    for(int i=0;i<N;i++)
    {
      aux[i] = arr[i];
    }
    for(int k=low;k<=high;k++)
    {
        if(i>mid)
        {
            arr[k] = aux[j++];
            compares++;
            exchanges++;
        }
        else if(j>high)
        {
            arr[k] = aux[i++];
            compares++;
            exchanges++;
        }
        else if(aux[i]>aux[j])
        {
            arr[k] = aux[j++];
            compares++;
            exchanges++;
        }
        else
        {
            arr[k] = aux[i++];
            compares++;
            exchanges++;
        }
        visual(arr);
    }
}
