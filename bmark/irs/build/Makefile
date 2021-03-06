
#--------------------------------------------
# The name of the executable file to produce
#--------------------------------------------

CODENAME 	= irs

#--------------------------
# Must use the bourne shell
#--------------------------
SHELL 		= /bin/sh


#-----------------------------------------------------------------------
# DESCRIPTION standard compile on LC chaos_3_x86_64_ib machines WITHOUT SILO
#-----------------------------------------------------------------------

GMAKE		= make -j 4

CC              = mpiicc
LINK            = mpiicc

BASE_LIBPATH    = -L../libs -L/usr/lib \
                -L/usr/lib -L/usr/lib64

BASE_INCPATH    = -I../.. -I../../includes -I/usr/local/include \
                -I/usr/local/apps/include \

BASE_LIBS       = -lpthread -libverbs


MPI_DEFINE      = -DCOMMPI
MPI_LIBS        = -lmpich
#MPI_LIBPATH     = -L/usr/stlocal/tools/mpi/mvapich-0.9.9_osu/usr/lib/mpi/icc/mvapich-gen2/lib
#MPI_INCPATH     = -I/usr/stlocal/tools/mpi/mvapich-0.9.9_osu/usr/lib/mpi/icc/mvapich-gen2/include

OTHER_LIBS 	=
OTHER_LIBPATH 	=
OTHER_INCPATH 	= 

DEFINES_BASE	= -DUNIX -DFUNCTION_TIMERS -Dlinux

IRS_LIBS 	= 	$(MPI_LIBS) \
			$(BASE_LIBS) \
			$(OTHER_LIBS)

IRS_INCPATH 	= 	$(BASE_INCPATH) \
			$(MPI_INCPATH) \
			$(OPENMP_INCPATH) \
			$(OTHER_INCPATH)

IRS_LIBPATH 	= 	$(BASE_LIBPATH) \
			$(MPI_LIBPATH) \
			$(OTHER_LIBPATH)

IRS_DEFINES	=	$(DEFINES_BASE) $(MPI_DEFINE)



CC_FLAGS_OPT    = -c -g -O2 
CC_FLAGS_DEB    = -c -g -O2

LINK_FLAGS_OPT	= -g
LINK_FLAGS_DEB	= -g

ARCHIVE		= ar rc
ARCHIVE_X	= ar x


########################################################################
#                                                                      #
#                   Non-machine specific options                       #
#                                                                      #
########################################################################

CODELIBS = \
	-lctl -lblk -lbndry -llag -lcom -lcur -ldmp \
	-ledits -leos -lgen -lgenrd -lhash \
	-lparm \
	-lreg -lrgst \
	-lsrc -lsys -ltdiff -ltimers \
	-llag -lgen -leos -lbndry -lblk  \
	-lparm -lreg -lparm -lctl  \
	-lcom -lcur -ldmp -lsys -lreg \
	-lbndry -lparm -lsrc -lblk -lparm -ltdiff \
	-llag -lobjects -ldmp  \
	-lgenrd -ledits -lrgst -ledits -lhash \
	-ltimers -lcom -lctl 


#-----------------
# Optimized Target
#-----------------

opt:
	irs_target="Optimized"; \
	irs_fcompile="$(F77) $(F77_FLAGS_OPT)";  \
	irs_cc="$(CC) $(CC_FLAGS_OPT) $(IRS_DEFINES) $(IRS_INCPATH)"; \
	irs_ar="$(ARCHIVE)"; \
	irs_arx="$(ARCHIVE_X)"; \
	LIB_DIR="../lib_opt" ; \
	CODE_DIR="../codes_opt" ; \
	RGSTLIB="../lib_opt/libctl.a"; \
	irs_link="$(LINK) $(LINK_FLAGS_OPT) ";\
	irs_libs="$(CODELIBS) $(IRS_LIBS)"; \
	export irs_target irs_fcompile irs_cc irs_ar irs_link irs_libs\
		irs_arx LIB_DIR CODE_DIR RGSTLIB; \
        make build

#-------------
# Debug Target
#-------------

debug:
	irs_target="Debug"; \
	irs_fcompile="$(F77) $(F77_FLAGS_DEB)";  \
	irs_cc="$(CC) $(CC_FLAGS_DEB) $(IRS_DEFINES) $(IRS_INCPATH)"; \
	irs_ar="$(ARCHIVE)"; \
	irs_arx="$(ARCHIVE_X)"; \
	LIB_DIR="../lib_debug" ; \
	CODE_DIR="../codes_debug" ; \
	RGSTLIB="../lib_debug/libctl.a"; \
	irs_link="$(LINK) $(LINK_FLAGS_DEB) ";\
	irs_libs="$(CODELIBS) $(IRS_LIBS)"; \
	export irs_target irs_fcompile irs_cc irs_ar irs_link irs_libs\
		irs_arx LIB_DIR CODE_DIR RGSTLIB; \
        make build

#-------------------------------------------------
# Build Target used by both opt and debug targets
#-------------------------------------------------

build:
	if [ ! -e $(LIB_DIR) ]; then  mkdir $(LIB_DIR); fi
	if [ ! -e $(CODE_DIR) ]; then  mkdir $(CODE_DIR); fi
	if [ ! -e ../debug ]; then  mkdir ../debug; fi
	cd ../includes; make -f ../build/Makefile $(RGSTLIB);
	cd ../includes; make -f ../build/Makefile irs_version;
	make sources; 
	cd $(LIB_DIR); $$irs_arx libctl.a main.o
	da=`date +%m%d`; \
	$$irs_link $(LIB_DIR)/main.o -L$(LIB_DIR) $(IRS_LIBPATH)  $$irs_libs \
		 -o $(CODE_DIR)/$(CODENAME)$$da > load.map.$$da; \
	ln -sf $(CODE_DIR)/$(CODENAME)$$da $(CODE_DIR)/$(CODENAME); \
	echo "$(CODENAME)$$da"

#--------------------------------------------------------------
# Help target
#--------------------------------------------------------------
help:
	@echo	"\nMakefile Targets"; \
	echo	"\topt    : Create optimized code (this is the default target)"; \
	echo	"\tdebug  : Create debug version of code"; \
	echo	"\tlint   : Run lint to syntax check the code"; \
	echo	"\tgcc    : Run gcc to syntax check the code"; \
	echo	" "; \
	echo	"\nTargets Used for McCabe Software Analysis Tools"; \
	echo	"\tpreprocess   : Run C Preprocessor and create .i files."; \
	echo	"\tinstrument   : Instrument the .i files."; \
	echo	"\tpostprocess  : Compile instrumented .i files to create"; \
        echo    "\t               an instrumented code."; \
	echo	"\timportnew    : Import test coverage *inst_*out files."; \
        echo    "\t               REMOVES ALL PREVIOUS test coverage data."; \
        echo    "\t               Will import all *inst_*out files in the "; \
        echo    "\t               current build directory."; \
	echo	"\timportadd    : Import test coverage *inst_*out files."; \
        echo    "\t               ADDS COVERAGE DATA to previously imported data."; \
        echo    "\t               Will import all *inst_*out files in the "; \
        echo    "\t               current build directory."; \
	echo	"\tmetrics      : Generate metric reports (no need to import)"; \
        echo    "\t               Can be run immediatedly after 'preprocess'."; \
        echo    "\t               Does not depend on importing test data."; \
	echo	"\tcoverage     : Generate test coverage reports"; \
        echo    "\t               Run after importnew and/or importadd"; \
	echo	" "; 

#--------------------------------------------------------------
# Two-pass lint
#
# Further items that could be 'grep -v'd out of the lint.out file:
#  grep -v "silo.h"
#  grep -v "unused in function"
#  grep -v "set but not used in function"
#
#--------------------------------------------------------------

lint:
	irs_lint="lint -c -x -MA -N600000 \
	$(IRS_DEFINES) $(IRS_INCPATH)\
	-D_REENTRANT"; \
	LO="../../build/lint.out"; \
	LO_FILE="lint.out"; \
	SYNTAX_CHECKER="LINT"; \
	export irs_lint LO LO_FILE SYNTAX_CHECKER; \
	make lint_d; \
	grep -v "silo.h" lint.out    | \
	grep -v "MPI"                | \
	grep -v "RUNNING"            | \
	grep -v "inst_com"           | \
	grep -v "pthread"            | \
	grep -v "pointer alignment"  | \
	grep -v "redefinition hides"   \
	> lint2.out; \
	rm lint.out;  mv lint2.out lint.out

#--------------------------------------------------------------
# GCC checking (similar to lint checking)
#
# Warnings standard in -Wall that I do not use :
#   -Wunused
# Warnings used IN ADDITION to standard -Wall:
#   -Wcast-align -Wstrict-prototypes -Wmissing-declarations
#   -Wmissing-prototypes
# Warnings I'd like to use but can't yet:
#   -Wshadow -Wredundant-decls
# Warnings I don't ever want to use:
#   -Wnested-externs    BECAUSE OF      extern int  nparms; in a C file
#   -Wconversion
#--------------------------------------------------------------
gcc:
	irs_lint="gcc -c -O -fsyntax-only \
	-W -Wimplicit -Wreturn-type -Wswitch -Wcomment \
	-Wtrigraphs -Wformat -Wchar-subscripts -Wuninitialized \
	-Wparentheses -Wcast-align \
	-Wmissing-declarations \
	-Wmissing-prototypes \
	$(IRS_DEFINES) $(IRS_INCPATH)\
	-D_POSIX_SOURCE=1"; \
	LO="../../build/gcc.out"; \
	LO_FILE="gcc.out"; \
	SYNTAX_CHECKER="GCC"; \
	export irs_lint LO LO_FILE SYNTAX_CHECKER; \
	make lint_d;

#---------------------------------------------------------------
# Generates .i files which may be instrumented by  McCabe.
#---------------------------------------------------------------
preprocess:
	irs_target="Instrumented"; \
	irs_fcompile="$(F77) $(F77_FLAGS_DEB)"; \
	irs_cc="$(CC) $(CC_FLAGS_DEB) $(IRS_DEFINES) $(IRS_INCPATH)"; \
	irs_pre="$(CC_PRE) $(CC_FLAGS_PRE) $(IRS_DEFINES) $(IRS_INCPATH) "; \
	DEBUG_DIR="../debug" ; \
	MCCABE_DIR="../mccabe" ; \
	INST_DIR="../mccabe/inst" ; \
	PRE_DIR="../mccabe/pre" ; \
	RGSTLIB="../lib_inst/libctl_inst.a" ; \
	export irs_target irs_cc irs_fcompile irs_pre \
		DEBUG_DIR MCCABE_DIR INST_DIR PRE_DIR RGSTLIB; \
	make preprocess_build;

preprocess_build:
	if [ ! -e $(DEBUG_DIR) ];     then  mkdir $(DEBUG_DIR); fi 
	if [ ! -e $(MCCABE_DIR) ];    then  mkdir $(MCCABE_DIR); fi 
	if [ ! -e $(INST_DIR) ];      then  mkdir $(INST_DIR); fi 
	if [ ! -e $(PRE_DIR) ];       then  mkdir $(PRE_DIR); fi 
	cd ../includes; make -f ../build/Makefile rgst_types.inst.i
	cd ../includes; make -f ../build/Makefile irs_version;
	make sources_preprocess;

#---------------------------------------------------------------
# Runs mccabe to instrument the code
# Change the name of the trace file to include %p which will
#   replace by getpid() at run time.  This allows each process
#   of a parallel run to have it's own trace file.
#---------------------------------------------------------------
instrument:
	cp irs.pcf irs.scf user.def irs.ckw ../mccabe;
	cd ../mccabe; cli export -pcf irs.pcf -scf irs.scf;
	/usr/local/apps/irs/bin/replace inst.out inst_%p.out ../mccabe/inst/instlib.c;
	/usr/local/apps/irs/bin/mccabe_mv;

#---------------------------------------------------------------
# Compiles an instrumented executable from the .i files 
# instrumented by mccabe.
#---------------------------------------------------------------
postprocess:
	irs_fcompile="$(F77) $(F77_FLAGS_DEB)"; \
	irs_post="$(CC_PRE) $(CC_FLAGS_POST) "; \
	irs_ar="$(ARCHIVE)"; \
	irs_arx="$(ARCHIVE_X)"; \
	DEBUG_DIR="../debug" ; \
	LIB_DIR="../lib_inst" ; \
	CODE_DIR="../codes_inst" ; \
	INST_DIR="../mccabe/inst" ; \
	PRE_DIR="../mccabe/pre" ; \
	RGSTLIB="../lib_inst/libctl_inst.a" ; \
	irs_link="$(LINK_PRE) $(LINK_FLAGS_DEB) ";\
	irs_libs="$(CODELIBS) $(IRS_LIBS)"; \
	export irs_fcompile irs_post irs_ar irs_arx irs_link irs_libs \
		DEBUG_DIR LIB_DIR CODE_DIR INST_DIR PRE_DIR RGSTLIB; \
	make postprocess_build;
 
postprocess_build:
	if [ ! -e $(LIB_DIR) ]; then  mkdir $(LIB_DIR); fi
	if [ ! -e $(CODE_DIR) ]; then  mkdir $(CODE_DIR); fi
	if [ ! -e $(DEBUG_DIR) ]; then  mkdir $(DEBUG_DIR); fi 
	make -f ./Makefile rgst_types.inst.o
	make -f ./Makefile instlib.o
	make sources_postprocess;
	cd $(LIB_DIR); $$irs_arx $(RGSTLIB) main.inst.o
	da=`date +%m%d`; \
	$$irs_link $(LIB_DIR)/main.inst.o -L$(LIB_DIR) $(IRS_LIBPATH)  $$irs_libs \
		 -o $(CODE_DIR)/$(CODENAME)$$da; \
	ln -sf $(CODE_DIR)/$(CODENAME)$$da $(CODE_DIR)/$(CODENAME); \
	echo "$(CODENAME)$$da"

#---------------------------------------------------------------
# Imports *inst_*out files generated by running an instrumented
# code.  Place all the *inst_*out files in the same directory
# as the main makefile before using the import target.
# These will be copied to the mccabe directory, imported,
# and then the copies will be removed
#
# importnew - clears out old test coverage data before importing
# importadd - adds test coverage data to previously imported data
#---------------------------------------------------------------
importnew:
	@cp *inst_*out ../mccabe; \
	cd ../mccabe; \
	mccabe_import clear; \
	rm *inst_*out

importadd:
	@cp *inst_*out ../mccabe; \
	cd ../mccabe; \
	mccabe_import; \
	rm *inst_*out

#---------------------------------------------------------------
# Generate reports of program metrics which don't depend
# on running the code.  IE, this is a static analysis
# of the code which doesn't use the *inst_*out files created
# at run time
#---------------------------------------------------------------
metrics:
	@cd ../mccabe; \
	echo " ... generating branch report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail branch     -output branch.rpt; \
	echo " ... generating cyclomatic report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail cyclomatic -output cyclomatic.rpt; \
	echo " ... generating design report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail design     -output design.rpt; \
	echo " ... generating program metrics report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail progmet    -output progmet.rpt; \
	echo " ... generating halstead report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail halstead   -output halstead.rpt; \
	echo " ... generating essential report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail essential  -output essential.rpt; \
	echo " ... generating linecount report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail linecount  -output linecount.rpt; \
	echo " ... generating module metrics report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail modmet     -output modmet.rpt; \
	echo " ... generating operand count report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail operand    -output operand.rpt; \
	echo " ... generating test summary report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail test       -output test.rpt; \
	echo " ... generating verbose halstead report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail verbosehal -output verbosehal.rpt;

branch:
	@cd ../mccabe; \
	echo " ... generating branch report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail branch     -output branch.rpt; 

cyclomatic:
	@cd ../mccabe; \
	echo " ... generating cyclomatic report\n"; 
	cli metrics -pcf irs.pcf -scf irs.scf -detail cyclomatic -output cyclomatic.rpt; 

design:
	@cd ../mccabe; \
	echo " ... generating design report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail design     -output design.rpt; 

progmet:
	@cd ../mccabe; \
	echo " ... generating program metrics report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail progmet    -output progmet.rpt; 

halstead:
	@cd ../mccabe; \
	echo " ... generating halstead report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail halstead   -output halstead.rpt; 

essential:
	@cd ../mccabe; \
	echo " ... generating essential report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail essential  -output essential.rpt;

linecount:
	@cd ../mccabe; \
	echo " ... generating linecount report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail linecount  -output linecount.rpt; 

modmet:
	@cd ../mccabe; \
	echo " ... generating module metrics report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail modmet     -output modmet.rpt; 

operand:
	@cd ../mccabe; \
	echo " ... generating operand count report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail operand    -output operand.rpt; 

test:
	@cd ../mccabe; \
	echo " ... generating test summary report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail test       -output test.rpt; 

verbosehal:
	@cd ../mccabe; \
	echo " ... generating verbose halstead report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -detail verbosehal -output verbosehal.rpt;

#---------------------------------------------------------------
# Generate coverage reports.  These depend on the *inst_*out
# test coverage data having been already imported into mccabe
# using the import target.  
#---------------------------------------------------------------
coverage:
	@cd ../mccabe; \
	echo " ... generating branch coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail branch     -output branch.coverage.rpt; \
	echo " ... generating cyclomatic coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail cyclomatic -output cyclomatic.coverage.rpt; \
	echo " ... generating design coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail design     -output design.coverage.rpt; \
	echo " ... generating program metrics coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail progmet    -output progmet.coverage.rpt; 

branch_coverage:
	@cd ../mccabe; \
	echo " ... generating branch coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail branch     -output branch.coverage.rpt

cyclomatic_coverage:
	@cd ../mccabe; \
	echo " ... generating cyclomatic coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail cyclomatic -output cyclomatic.coverage.rpt

design_coverage:
	@cd ../mccabe; \
	echo " ... generating design coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail design     -output design.coverage.rpt 

program_coverage:
	@cd ../mccabe; \
	echo " ... generating program metrics coverage report\n"; \
	cli metrics -pcf irs.pcf -scf irs.scf -coverage -detail progmet    -output progmet.coverage.rpt

#-------------------------
# non target-specific jazz
#-------------------------

irs_version: 
	irs_version $(irs_target) 

$(RGSTLIB): [A-Z]*.h pint.h
	cat [A-Z]*.h pint.h > temp.h
	irs_hrcreate temp.h
	irs_hrparse temp.hr
	cp rgst_types.c  ../debug
	$$irs_cc -I../ rgst_types.c
	$$irs_ar $(RGSTLIB) rgst_types.o
	rm temp.hr

rgst_types.inst.i: [A-Z]*.h pint.h
	cat [A-Z]*.h pint.h > temp.h
	irs_hrcreate temp.h
	irs_hrparse temp.hr
	mv rgst_types.c rgst_types.inst.c
	rm -f rgst_types.inst.i
	$$irs_pre -I../ rgst_types.inst.c >> rgst_types.inst.i
	cp rgst_types.inst.i $(PRE_DIR)/rgst_types.inst.i
	rm temp.hr 

rgst_types.inst.o: $(INST_DIR)/rgst_types.inst.i
	$$irs_post $(INST_DIR)/rgst_types.inst.i
	ln -sf $(INST_DIR)/rgst_types.inst.i $(DEBUG_DIR)/rgst_types.c
	$$irs_ar $(RGSTLIB) rgst_types.inst.o

instlib.o: $(INST_DIR)/instlib.c
	$$irs_post $(INST_DIR)/instlib.c
	ln -sf $(INST_DIR)/instlib.c $(DEBUG_DIR)/instlib.c
	$$irs_ar $(RGSTLIB) instlib.o

depend:
	DEPFLAGS="$(IRS_DEFINES) $(IRS_INCPATH)"; \
	export DEPFLAGS; \
	make depend2

depend2:
	cd ../sources/blk; 		make -f Makefile.blk 		depend > depend.log 2>&1
	cd ../sources/bndry; 		make -f Makefile.bndry 		depend > depend.log 2>&1
	cd ../sources/com; 		make -f Makefile.com 		depend > depend.log 2>&1
	cd ../sources/ctl; 		make -f Makefile.ctl 		depend > depend.log 2>&1
	cd ../sources/cur; 		make -f Makefile.cur 		depend > depend.log 2>&1
	cd ../sources/dmp; 		make -f Makefile.dmp 		depend > depend.log 2>&1
	cd ../sources/edits; 		make -f Makefile.edits 		depend > depend.log 2>&1
	cd ../sources/eos; 		make -f Makefile.eos 		depend > depend.log 2>&1
	cd ../sources/gen; 		make -f Makefile.gen 		depend > depend.log 2>&1
	cd ../sources/genrd; 		make -f Makefile.genrd 		depend > depend.log 2>&1
	cd ../sources/hash; 		make -f Makefile.hash 		depend > depend.log 2>&1
	cd ../sources/lag; 		make -f Makefile.lag 		depend > depend.log 2>&1
	cd ../sources/objects; 		make -f Makefile.objects 	depend > depend.log 2>&1
	cd ../sources/parm; 		make -f Makefile.parm 		depend > depend.log 2>&1
	cd ../sources/reg; 		make -f Makefile.reg 		depend > depend.log 2>&1
	cd ../sources/rgst; 		make -f Makefile.rgst 		depend > depend.log 2>&1
	cd ../sources/src; 		make -f Makefile.src 		depend > depend.log 2>&1
	cd ../sources/sys; 		make -f Makefile.sys 		depend > depend.log 2>&1
	cd ../sources/tdiff; 		make -f Makefile.tdiff 		depend > depend.log 2>&1
	cd ../sources/timers; 		make -f Makefile.timers 	depend > depend.log 2>&1

sources:
	cd ../sources/blk;     	   $(GMAKE) -f Makefile libblk ; 
	cd ../sources/bndry;   	   $(GMAKE) -f Makefile libbndry ; 
	cd ../sources/com;         $(GMAKE) -f Makefile libcom ; 
	cd ../sources/ctl;         $(GMAKE) -f Makefile libctl ; 
	cd ../sources/cur;         $(GMAKE) -f Makefile libcur ; 
	cd ../sources/dmp;         $(GMAKE) -f Makefile libdmp ; 
	cd ../sources/edits;       $(GMAKE) -f Makefile libedits ; 
	cd ../sources/eos;         $(GMAKE) -f Makefile libeos ; 
	cd ../sources/gen;         $(GMAKE) -f Makefile libgen ; 
	cd ../sources/genrd;       $(GMAKE) -f Makefile libgenrd ; 
	cd ../sources/hash;        $(GMAKE) -f Makefile libhash ; 
	cd ../sources/lag;         $(GMAKE) -f Makefile liblag ; 
	cd ../sources/objects;	   $(GMAKE) -f Makefile libobjects ; 
	cd ../sources/parm;    	   $(GMAKE) -f Makefile libparm ; 
	cd ../sources/reg;         $(GMAKE) -f Makefile libreg ; 
	cd ../sources/rgst;        $(GMAKE) -f Makefile librgst ; 
	cd ../sources/src;         $(GMAKE) -f Makefile libsrc ; 
	cd ../sources/sys;         $(GMAKE) -f Makefile libsys ; 
	cd ../sources/tdiff;       $(GMAKE) -f Makefile libtdiff ; 
	cd ../sources/timers;      $(GMAKE) -f Makefile libtimers ; 

lint_d:
	rm -f $(LO_FILE)
	cd ../sources/blk;         make -f Makefile.blk         lint ; 
	cd ../sources/bndry;       make -f Makefile.bndry       lint ; 
	cd ../sources/com;         make -f Makefile.com         lint ; 
	cd ../sources/ctl;         make -f Makefile.ctl         lint ; 
	cd ../sources/cur;         make -f Makefile.cur         lint ; 
	cd ../sources/dmp;         make -f Makefile.dmp         lint ; 
	cd ../sources/edits;       make -f Makefile.edits       lint ; 
	cd ../sources/eos;         make -f Makefile.eos         lint ; 
	cd ../sources/gen;         make -f Makefile.gen         lint ; 
	cd ../sources/genrd;       make -f Makefile.genrd       lint ; 
	cd ../sources/hash;        make -f Makefile.hash        lint ; 
	cd ../sources/lag;         make -f Makefile.lag         lint ; 
	cd ../sources/objects;     make -f Makefile.objects     lint ; 
	cd ../sources/parm;        make -f Makefile.parm        lint ; 
	cd ../sources/reg;         make -f Makefile.reg         lint ; 
	cd ../sources/rgst;        make -f Makefile.rgst        lint ; 
	cd ../sources/src;         make -f Makefile.src         lint ; 
	cd ../sources/sys;         make -f Makefile.sys         lint ; 
	cd ../sources/tdiff;       make -f Makefile.tdiff       lint ;
	cd ../sources/timers;      make -f Makefile.timers      lint ;

lintall:
	rm -f lintall.out
	lint ../sources/*/*.ln | \
	grep -v "math.h"   | grep -v "signal.h" | grep -v "silo.h"   | \
	grep -v "stdio.h"  | grep -v "stdlib.h" | grep -v "string.h" | \
	grep -v "unistd.h" | grep -v "Xlib.h"   | grep -v "Xutil.h" \
	> lintall.out

sources_preprocess:
	cd ../sources/blk;         make -f Makefile.blk         preprocess ; 
	cd ../sources/bndry;       make -f Makefile.bndry       preprocess ; 
	cd ../sources/com;         make -f Makefile.com         preprocess ; 
	cd ../sources/ctl;         make -f Makefile.ctl         preprocess ; 
	cd ../sources/cur;         make -f Makefile.cur         preprocess ; 
	cd ../sources/dmp;         make -f Makefile.dmp         preprocess ; 
	cd ../sources/edits;       make -f Makefile.edits       preprocess ; 
	cd ../sources/eos;         make -f Makefile.eos         preprocess ; 
	cd ../sources/gen;         make -f Makefile.gen         preprocess ; 
	cd ../sources/genrd;       make -f Makefile.genrd       preprocess ; 
	cd ../sources/hash;        make -f Makefile.hash        preprocess ; 
	cd ../sources/lag;         make -f Makefile.lag         preprocess ; 
	cd ../sources/objects;     make -f Makefile.objects     preprocess ; 
	cd ../sources/parm;        make -f Makefile.parm        preprocess ; 
	cd ../sources/reg;         make -f Makefile.reg         preprocess ; 
	cd ../sources/rgst;        make -f Makefile.rgst        preprocess ; 
	cd ../sources/src;         make -f Makefile.src         preprocess ; 
	cd ../sources/sys;         make -f Makefile.sys         preprocess ; 
	cd ../sources/tdiff;       make -f Makefile.tdiff       preprocess ;
	cd ../sources/timers;      make -f Makefile.timers      preprocess ;

sources_postprocess:
	cd ../sources/blk;         make -f Makefile.blk         postprocess ; 
	cd ../sources/bndry;       make -f Makefile.bndry       postprocess ; 
	cd ../sources/com;         make -f Makefile.com         postprocess ; 
	cd ../sources/ctl;         make -f Makefile.ctl         postprocess ; 
	cd ../sources/cur;         make -f Makefile.cur         postprocess ; 
	cd ../sources/dmp;         make -f Makefile.dmp         postprocess ; 
	cd ../sources/edits;       make -f Makefile.edits       postprocess ; 
	cd ../sources/eos;         make -f Makefile.eos         postprocess ; 
	cd ../sources/gen;         make -f Makefile.gen         postprocess ; 
	cd ../sources/genrd;       make -f Makefile.genrd       postprocess ; 
	cd ../sources/hash;        make -f Makefile.hash        postprocess ; 
	cd ../sources/lag;         make -f Makefile.lag         postprocess ; 
	cd ../sources/objects;     make -f Makefile.objects     postprocess ; 
	cd ../sources/parm;        make -f Makefile.parm        postprocess ; 
	cd ../sources/reg;         make -f Makefile.reg         postprocess ; 
	cd ../sources/rgst;        make -f Makefile.rgst        postprocess ; 
	cd ../sources/src;         make -f Makefile.src         postprocess ; 
	cd ../sources/sys;         make -f Makefile.sys         postprocess ; 
	cd ../sources/tdiff;       make -f Makefile.tdiff       postprocess ;
	cd ../sources/timers;      make -f Makefile.timers      postprocess ;

#---------------
# clean utility
#---------------
touch:
	cd ../sources; touch */*.c

clean:
	if [ -e ../lib_debug   ]; then cd ../lib_debug;	rm -f *.a *.o ; fi
	if [ -e ../lib_opt     ]; then cd ../lib_opt;	rm -f *.a *.o ; fi
	cd ../debug;    rm -f *
	cd ../includes; rm -f *.hh *.hr rgst_types* irsversion.h temp* *.hh~ *.h~
	cd ../sources/blk; rm -f *.o
	cd ../sources/bndry; rm -f *.o
	cd ../sources/com; rm -f *.o
	cd ../sources/ctl; rm -f *.o
	cd ../sources/cur; rm -f *.o
	cd ../sources/dmp; rm -f *.o
	cd ../sources/edits; rm -f *.o
	cd ../sources/eos; rm -f *.o
	cd ../sources/gen; rm -f *.o
	cd ../sources/genrd; rm -f *.o
	cd ../sources/hash; rm -f *.o
	cd ../sources/lag; rm -f *.o
	cd ../sources/objects; rm -f *.o
	cd ../sources/parm; rm -f *.o
	cd ../sources/reg; rm -f *.o
	cd ../sources/rgst; rm -f *.o
	cd ../sources/src; rm -f *.o
	cd ../sources/sys; rm -f *.o
	cd ../sources/tdiff; rm -f *.o
	cd ../sources/timers; rm -f *.o

