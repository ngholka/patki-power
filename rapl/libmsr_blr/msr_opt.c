#include <unistd.h>	//getopt
#include <getopt.h>
#include <stdlib.h>	//strtoll
#include <stdint.h>
#include "msr_rapl.h"
#include "msr_core.h"
#include "msr_opt.h"

static char *
msr2str( uint64_t msr ){
	switch(msr){
		case MSR_PKG_POWER_LIMIT:	return "MSR_PKG_POWER_LIMIT";	break;	
		case MSR_PP0_POWER_LIMIT:	return "MSR_PP0_POWER_LIMIT";	break;
#ifdef ARCH_062D
		case MSR_DRAM_POWER_LIMIT:	return "MSR_DRAM_POWER_LIMIT";	break;
#endif
		default:			return "WTF?";			break;
	}
}

/*PATKI: If we ever decide to write a command line interface,
 * we can use the following prototype:
 *
	// BLR: TODO:  write a command-line interface.
	// PATKI: This can wait, because this eventually messes up applications
	// that take their own command line parameters.
	// Lets just stick to environment variables for now.	//
 
 	 	argc=argc;
 		 argv=argv;

*void
get_command_line(int argc, char **argv )*/


/*
 * PATKI: get_env_variables()
 * 
 * This module will serve as an entry point into the library functionality and will be
 * called by rapl_init. It determine whether you want to do a dry run, a read-only-run or allow
 * writing to msrs based on environment variables. This will call the init_msr(), set_power_bounds() module
 * only when writing to msrs is enabled. 
 * Also, note that finalize_msr() needs to be called only when init_msr() has been called. 
 * So we need something that will help us check that as well.
 */

void
get_env_variables(){

	char *env = NULL;

	int dry_run_flag = 1;
	int read_only_flag = 0;
	int read_write_flag = 0;

	env = get_env("READ_ONLY");
	if(env == NULL){
		//Read only flag has not been set.
		//Ensure that it is still zero.
		read_only_flag = 0;
	}
	if(env){
		read_only_flag = strtoll(env,NULL,0);
	}

	env = get_env("READ_WRITE");
	
	if(env == NULL){
		//Read_write flag has not been set.
		//Ensure that it is still zero.
		read_write_flag = 0;
	}
	if(env){
		read_write_flag = strtoll(env,NULL,0);
	}

/* We are dealing with MSRs and need to be very careful, hence, if the 
 * environment variables contain any thing other than 1, none of the code
 * should run and it should default to the dry-run.
 * The dry_run_flag is always 1.
 * If read_write_flag is 1, it should not matter what the value of read_only_flag is. 
 *
 * If read_only_flag is 1, the read_write_flag has to be ZERO.
 *
 * */

	if(dry_run_flag == 1){

		/*READ_ONLY_MODE*/		
		if(read_only_flag == 1 && read_write_flag == 0){
			/*Need to determine what to do here. Output should probably be a file 
 			* with the measured power values. So, call init_msr(), 
 			* followed by the get_rapl_data(), followed by finalize_msr(). */ 	

//			if(permissions_flag == 1)

		}
	
		/*READ_WRITE_MODE. Care should be taken that the user has the right permissions, and
 		* that even if the environment variable is set, you can't write to MSRs unless 
 		* you have the right permissions. How do I check for this? */
	 
		if(read_write_flag == 1){	

//			if(permissions_flag == 1)
				set_power_bounds();	
		}
	}
}

void 
set_power_bounds(){
	int cpu;
	uint64_t msr_pkg_power_limit=-1, msr_pp0_power_limit=-1; 
#ifdef ARCH_062D
	uint64_t msr_dram_power_limit=-1;
#endif
	char *env = NULL;


	// First, check the environment variables.
	env = getenv("MSR_PKG_POWER_LIMIT");
	if(env){
		msr_pkg_power_limit = strtoll( env, NULL, 0 );
	
	env = getenv("MSR_PP0_POWER_LIMIT");
	if(env){
		msr_pp0_power_limit = strtoll( env, NULL, 0 );
	}
#ifdef ARCH_062D
	env = getenv("MSR_DRAM_POWER_LIMIT");
	if(env){
		msr_dram_power_limit = strtoll( env, NULL, 0 );
	}
#endif

	// Now write the MSRs.  Zero is a valid value
	for( cpu=0; cpu<NUM_PACKAGES; cpu++ ){
		if( msr_pkg_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_PKG_POWER_LIMIT), msr_pkg_power_limit, cpu);
			write_msr( cpu, MSR_PKG_POWER_LIMIT, msr_pkg_power_limit );
		}
		if( msr_pp0_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_PP0_POWER_LIMIT), msr_pp0_power_limit, cpu);
			write_msr( cpu, MSR_PP0_POWER_LIMIT, msr_pp0_power_limit );
		}
#ifdef ARCH_062D
		if( msr_dram_power_limit != -1 ){
			fprintf(stderr, "%s::%d setting %s to 0x%lx on cpu %d\n", 
				__FILE__, __LINE__, msr2str(MSR_DRAM_POWER_LIMIT), msr_dram_power_limit, cpu);
			write_msr( cpu, MSR_DRAM_POWER_LIMIT, msr_dram_power_limit );
		}
#endif
	}
}


