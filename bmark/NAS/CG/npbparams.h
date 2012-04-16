c NPROCS = 2048 CLASS = D
c  
c  
c  This file is generated automatically by the setparams utility.
c  It sets the number of processors and the class of the NPB
c  in this directory. Do not modify it by hand.
c  
        integer            na, nonzer, niter
        double precision   shift, rcond
        parameter(  na=1500000,
     >              nonzer=21,
     >              niter=100,
     >              shift=500.,
     >              rcond=1.0d-1 )

c number of nodes for which this version is compiled
        integer    nnodes_compiled
        parameter( nnodes_compiled = 2048)
        integer    num_proc_cols, num_proc_rows
        parameter( num_proc_cols=64, num_proc_rows=32 )
        logical  convertdouble
        parameter (convertdouble = .false.)
        character*11 compiletime
        parameter (compiletime='14 Apr 2012')
        character*3 npbversion
        parameter (npbversion='3.3')
        character*6 cs1
        parameter (cs1='mpif77')
        character*9 cs2
        parameter (cs2='$(MPIF77)')
        character*46 cs3
        parameter (cs3='-Xlinker -rpath=$(HOME)/local/src/power/rap...')
        character*6 cs4
        parameter (cs4='(none)')
        character*9 cs5
        parameter (cs5='-O3 -fPIC')
        character*30 cs6
        parameter (cs6='-O3 -fPIC  -Wl,--build-id=none')
        character*6 cs7
        parameter (cs7='randi8')