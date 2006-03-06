! { dg-do run }
! Test procedures with allocatable dummy arguments
program alloc_dummy

    implicit none
    integer, allocatable :: a(:)
    integer, allocatable :: b(:)

    call init(a)
    if (.NOT.allocated(a)) call abort()
    if (.NOT.all(a == [ 1, 2, 3 ])) call abort()

    call useit(a, b)
    if (.NOT.all(b == [ 1, 2, 3 ])) call abort()

    call kill(a)
    if (allocated(a)) call abort()

    call kill(b)
    if (allocated(b)) call abort()

contains

    subroutine init(x)
        integer, allocatable, intent(out) :: x(:)
        allocate(x(3))
        x = [ 1, 2, 3 ]
    end subroutine init

    subroutine useit(x, y)
        integer, allocatable, intent(in)  :: x(:)
        integer, allocatable, intent(out) :: y(:)
        if (allocated(y)) call abort()
        allocate (y(3))
        y = x
    end subroutine useit

    subroutine kill(x)
        integer, allocatable, intent(out) :: x(:)
    end subroutine kill

end program alloc_dummy
