//  
//  platform.h
//  altair
//  
//  Auther:
//       ned rihine <ned.rihine@gmail.com>
// 
//  Copyright (c) 2012 rihine All rights reserved.
// 
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
// 
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef altair_platform_h
#define altair_platform_h


#undef PROCESSOR_DETECTED
#undef COMPILER_DETECTED
#undef OS_DETECTED


/* ---------------------------------- *
 * Processor Detection                *
 * ---------------------------------- */
/*
  Carbon でこんな風に定義されてる？
 */
#if defined(TARGET_CPU_PPC)
#   define PROCESSOR_DETECTED
#endif  /* defined(TARGET_CPU_PPC) */

/*
  ARM
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__arm__)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_ARM
#   endif  /* defined(__arm__) */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  DEC Alpha
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__alpha) || defined(__alpha__)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_ALPHA
#   endif  /* defined(__alpha) || defined(__alpha__) */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  Sun SPARC
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__sparc) || defined(__sparc__)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_SPARC
#   endif  /* defined(__sparc) || defined(__sparc__) */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  MIPS
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__MIPSEL__)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_MIPS
#   elif defined(__mips__)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_MIPS
#   endif  /* defined(__MIPSEL__) */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  PowerPC
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(_ARCH_PPC) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC) || defined(powerpc) \
       || defined(__PPC__) || defined(__powerpc64__) || defined(__powerpc64)
#       define PROCESSOR_DETECTED
#       define TARGET_BIG_ENDIAN
#   endif  /* defined(_ARCH_PPC) || defined(__ppc__) || defined(__ppc64__) || defined(__PPC) || defined(powerpc) \ */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  x86_64 or AMD64 or x64
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__x86_64__) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_AMD64_) \
    || defined(_M_X64)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_X64
#       define TARGET_CPU_X86_64
#   endif  /* defined(__x86_64__) || defined(__x86_64) || defined(__amd64) || defined(__amd64__) || defined(_AMD64_) \ */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  Intel x86
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__i386__) || defined(__i386) || defined(i386) || defined(_X86_) || defined(_M_IX86)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_X86
#   endif  /* defined(__i386__) || defined(__i386) || defined(i386) || defined(_X86_) || defined(_M_IX86) */
#endif  /* !defined(PROCESSOR_DETECTED) */

/*
  IA64
 */
#if !defined(PROCESSOR_DETECTED)
#   if defined(__ia64__) || defined(_IA64) || defined(__ia64) || defined(_M_IA64)
#       define PROCESSOR_DETECTED
#       define TARGET_CPU_IA64
#   endif  /* defined(__i386__) || defined(__i386) || defined(i386) || defined(_X86_) || defined(_M_IX86) */
#endif  /* !defined(PROCESSOR_DETECTED) */


/* ---------------------------------- *
 * Compiler Detection                 *
 * ---------------------------------- */
/*
  GNU C Compiler
 */
#if !defined(COMPILER_DETECTED)

#   if defined(__GNUC__)
#       define COMPILER_DETECTED
#       define TARGET_COMPILER_GCC
#   endif  /* defined(__GNUC__) */

#   if defined(__CYGWIN__) || defined(__CYGWIN32__)
#       define COMPILER_DETECTED
#       define TARGET_COMPILER_CYGWIN
#   endif  /* defined(__CYGWIN__) || defined(__CYGWIN32__) */

#   if defined(__MINGW32__)
#       define TARGET_COMPILER_MINGW
#   endif  /* defined(__MINGW32__) */

#   if defined(__DJGPP__)
#       define TARGET_COMPILER_DJGPP
#   endif  /* defined(__DJGPP__) */

#endif  /* !defined(COMPILER_DETECTED) */

/*
  Intel Compiler
 */
#if !defined(COMPILER_DETECTED)
#   if defined(__INTEL_COMPILER) || defined(__ICL)
#       define COMPILER_DETECTED
#       define TARGET_COMPILER_ICC
#   endif  /* defined(__INTEL_COMPILER) || defined(__ICL) */
#endif  /* !defined(COMPILER_DETECTED) */

/*
  Visual Studio
 */
#if !defined(COMPILER_DETECTED)
#   ifdef _MSC_VER
#       defined TARGET_COMPILER_VC
#   endif  /* def _MSC_VER */
#endif  /* !defined(COMPILER_DETECTED) */

/*
  CodeWarrior MetroWerks
 */
#ifndef COMPILER_DETECTED
#   ifdef __MWEAKS__
#       define TARGET_OS_MWEAKS
#       define COMPILER_DETECTED
#   endif  /* def __MWEAKS__ */
#endif  /* ndef COMPILER_DETECTED */

/*
  Borland
 */
#if !defined(COMPILER_DETECTED)
#   if defined(__BORLANDC__)
#       if __BORLANDC__ >= 0x0600
#           defined TARGET_COMPILER_BORLAND
#       endif  /* __BORLANDC__ >= 0x0600 */
#   endif  /* defined(__BORLANDC__) */
#endif  /* !defined(COMPILER_DETECTED) */


/* ---------------------------------- *
 * OS Detection                       *
 * ---------------------------------- */
#if !defined(OS_DETECTED)
#   if defined(TARGET_COMPILER_VC) || defined(_WIN32) || defined(_WIN64)
#      define OS_DETECTED
#      define TARGET_OS_WINDOWS
#   endif  /* defined(TARGET_COMPILER_VC) || defined(_WIN32) || defined(_WIN64) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__linux__) || defined(linux) || defined(__linux) || defined(__gnu_linux__) || defined(__CYGWIN__)
#      define OS_DETECTED
#      define TARGET_OS_LINUX
#   endif  /* defined(__linux__) || defined(linux) || defined(__linux) || defined(__gnu_linux__) || defined(__CYGWIN__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(TARGET_CPU_ARM)
#      define OS_DETECTED
#      define TARGET_OS_NDSFIRMWIRE
#   endif  /* defined(TARGET_CPU_ARM) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(MSDOS) || defined(__DOS__) || defined(__DJGPP__)
#       define OS_DETECTED
#      define TARGET_OS_DOS
#   endif  /* defined(MSDOS) || defined(__DOS__) || defined(__DJGPP__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__sun__)
#       define OS_DETECTED
#      define TARGET_OS_SOLARIS
#   endif  /* defined(__sun__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__FreeBSD__)
#       define OS_DETECTED
#      define TARGET_OS_FREEBSD
#   endif  /* defined(__FreeBSD__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__NetBSD__)
#       define OS_DETECTED
#      define TARGET_OS_NETBSD
#   endif  /* defined(__NetBSD__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__OPENBSD__)
#       define OS_DETECTED
#      define TARGET_OS_OPENBSD
#   endif  /* defined(__OpenBSD__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__APPLE__)
#       define OS_DETECTED
#      define TARGET_OS_MACOSX
#   endif  /* defined(__APPLE__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   if defined(__hurd__)
#       define OS_DETECTED
#      define TARGET_OS_HURD
#   endif  /* defined(__hurd__) */
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   define TARGET_OS_UNKNOWN
#endif  /* !defined(OS_DETECTED) */

#if !defined(OS_DETECTED)
#   ifdef TARGET_OS_WINDOWS
#      define TARGET_COMPILER_VC
#   endif  /* def TARGET_OS_WINDOWS */
#endif  /* !defined(OS_DETECTED) */


#endif  /* altair_platform_h */
