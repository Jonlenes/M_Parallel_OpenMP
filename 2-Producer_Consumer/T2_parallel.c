#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

void producer_consumer(int size, int *vec, int n, int threadsCount) {
	int i, j;
	long long unsigned int sum = 0;
	
	//Criando um buffer para cada thread
	int buffer[threadsCount][size];
	
	//Paralelização do for: cada thread irá executar duas interações seguidas do for
	#pragma omp parallel for num_threads(threadsCount) \
		schedule(static, 2) private(i, j) reduction(+: sum) 
	
	//n, buffer, vec e size são publicos
	//sum está protegido por reduction 	
		 	
	for(i = 0; i < n; i++) {		
		if(i % 2 == 0) {	// PRODUTOR
			for(j = 0; j < size; j++) {
				buffer[ omp_get_thread_num() ][j] = vec[i] + j * vec[i + 1];
			}
		}
		else {	// CONSUMIDOR
			for(j = 0; j < size; j++) {
				sum += buffer[ omp_get_thread_num() ][j];
			}
		}
	}
	
	printf("%llu\n", sum);
}

int main(int argc, char * argv[]) {
	double start, end;
	int i, n, size, threadsCount;
	int *vec;

	scanf("%d %d %d", &threadsCount	, &n, &size);
	
	vec = (int *)malloc(n * sizeof(int));

	for(i = 0; i < n; i++)
		scanf("%d", &vec[i]);
	
	start = omp_get_wtime();
	producer_consumer(size, vec, n, threadsCount);
	end = omp_get_wtime();

	printf("%lf\n", end - start);

	free(vec);

	return 0;
}


/*

LSCPU-------------------------------------------------------------------

	Architecture:        x86_64
	CPU op-mode(s):      32-bit, 64-bit
	Byte Order:          Little Endian
	CPU(s):              4
	On-line CPU(s) list: 0-3
	Thread(s) per core:  1
	Core(s) per socket:  4
	Socket(s):           1
	NUMA node(s):        1
	Vendor ID:           GenuineIntel
	CPU family:          6
	Model:               60
	Model name:          Intel(R) Core(TM) i5-4590 CPU @ 3.30GHz
	Stepping:            3
	CPU MHz:             2905.785
	CPU max MHz:         3700.0000
	CPU min MHz:         800.0000
	BogoMIPS:            6584.61
	Virtualization:      VT-x
	L1d cache:           32K
	L1i cache:           32K
	L2 cache:            256K
	L3 cache:            6144K
	NUMA node0 CPU(s):   0-3
	Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc cpuid aperfmperf pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 sdbg fma cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm cpuid_fault epb invpcid_single pti retpoline tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 avx2 smep bmi2 erms invpcid xsaveopt dtherm ida arat pln pts

LSCPU-------------------------------------------------------------------


SERIAL==================================================================

ARQ1--------------------------------------------------------------------
	Each sample counts as 0.01 seconds.

	  %   cumulative   self              self     total           
	 time   seconds   seconds    calls  Ts/call  Ts/call  name    
	  0.00      0.00     0.00        1     0.00     0.00  producer_consumer
ARQ1--------------------------------------------------------------------


ARQ2--------------------------------------------------------------------
	Each sample counts as 0.01 seconds.
	  %   cumulative   self              self     total           
	 time   seconds   seconds    calls  ms/call  ms/call  name    
	 97.01      0.23     0.23        1   232.82   232.82  producer_consumer

ARQ2--------------------------------------------------------------------


ARQ3--------------------------------------------------------------------
	Each sample counts as 0.01 seconds.
	  %   cumulative   self              self     total           
	 time   seconds   seconds    calls   s/call   s/call  name    
	 91.44      2.18     2.18        1     2.18     2.18  producer_consumer

ARQ3--------------------------------------------------------------------


Flag -O0
	Arq1 ---> Speedup = 0
	Arq2 ---> Speedup = -0.01
	Arq3 ---> Speedup = -0.23
	
Flag -O1
	Arq1 ---> Speedup = 0
	Arq2 ---> Speedup = 0.19
	Arq3 ---> Speedup = 1.75

Flag -O2
	Arq1 ---> Speedup = 0
	Arq2 ---> Speedup = 0.19
	Arq3 ---> Speedup = 1.73

Flag -O3
	Arq1 ---> Speedup = 0
	Arq2 ---> Speedup = 0.21
	Arq3 ---> Speedup = 1.95
	
SERIAL==================================================================
	
 */
