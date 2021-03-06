!***********************************************************************
!                        Version 0:  02/02, MKN                        *
!                                                                      *
!   RESETSIZE   -   Wrapper for modules that can be called from C++    * 
!                   used to get IterControls pointer                   *
!                                                                      *
!***********************************************************************

   subroutine ResetSize(Size,                                &
                        tfloor, tmin, igeom, ittyp, iaccel,  &
                        imatc, iscat, itimsrc, decomp_s)

!  Include

   use kind_mod
   use Size_mod


   implicit none

!  Arguments

   type(MeshSize)                :: Size

   real(adqt),        intent(in) :: tfloor
   real(adqt),        intent(in) :: tmin
    
   character(len=8),  intent(in) :: igeom
   character(len=8),  intent(in) :: ittyp
   character(len=8),  intent(in) :: iaccel
   character(len=8),  intent(in) :: imatc
   character(len=8),  intent(in) :: iscat
   character(len=8),  intent(in) :: itimsrc
   character(len=8),  intent(in) :: decomp_s


   Size % tfloor   = tfloor
   Size % tmin     = tmin

   Size % igeom    = igeom
   Size % ittyp    = ittyp
   Size % iaccel   = iaccel
   Size % imatc    = imatc
   Size % iscat    = iscat
   Size % itimsrc  = itimsrc
   Size % decomp_s = decomp_s


   return
   end subroutine ResetSize

