/***************************************************************************
Copyright (c) 2013, Amir Geva
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
***************************************************************************/
#ifndef H_OGUI_DEFAULT_FONT
#define H_OGUI_DEFAULT_FONT

namespace OGUI {

const unsigned char default_font[] = {
  0x89,0x50,0x4e,0x47,0x0d,0x0a,0x1a,0x0a,0x00,0x00,0x00,0x0d,0x49,0x48,0x44,0x52,
  0x00,0x00,0x00,0xc8,0x00,0x00,0x00,0xc8,0x08,0x06,0x00,0x00,0x00,0xad,0x58,0xae,
  0x9e,0x00,0x00,0x15,0x18,0x49,0x44,0x41,0x54,0x78,0x9c,0xed,0x9d,0x3d,0x7a,0xf4,
  0xb6,0x0e,0x85,0xe9,0xbb,0x89,0xac,0x21,0x5b,0xc8,0x3e,0xb2,0x07,0x2d,0x42,0x4b,
  0xd0,0x0a,0xb4,0x01,0xf5,0xd3,0xa4,0x52,0xad,0x3c,0xa9,0xa6,0x8c,0x4a,0xa5,0x63,
  0x2a,0x96,0xea,0x74,0x0b,0xfb,0x5c,0xc3,0xbc,0xd4,0x78,0x04,0x1c,0xd9,0x1c,0x0f,
  0xde,0xe6,0xcb,0x8c,0x23,0x0c,0x28,0x12,0xfc,0x05,0xc0,0x10,0x1c,0xc7,0x71,0x1c,
  0xc7,0xa9,0x90,0x94,0x52,0x8a,0x31,0xc6,0xef,0xd6,0xc3,0x71,0x28,0xc4,0x18,0x63,
  0x4a,0x29,0xe1,0x73,0x7a,0x43,0x2b,0x6f,0x7b,0x83,0xa3,0x9d,0xf3,0x14,0xc4,0x37,
  0x18,0xb2,0x64,0x03,0xce,0x1b,0xf7,0x51,0xda,0xb6,0x6d,0xb7,0x6d,0xdb,0x20,0x63,
  0x18,0x86,0x61,0xdb,0xb6,0x4d,0xa3,0x6b,0xdb,0xb6,0xed,0xb2,0x2c,0xcb,0x26,0x58,
  0x96,0x65,0x19,0x86,0x61,0x38,0x2a,0x0b,0x72,0x96,0x65,0x59,0xda,0xb6,0x6d,0x43,
  0x08,0x61,0x9a,0xa6,0x89,0xf1,0x0e,0x21,0x3b,0xa5,0x94,0xfa,0xbe,0xef,0xad,0xf2,
  0x42,0xb0,0xd7,0x43,0x89,0xeb,0xf5,0x7a,0xb5,0x96,0x37,0xc6,0x18,0xaf,0xd7,0xeb,
  0x95,0xa5,0xd3,0x69,0x30,0x7b,0x55,0x29,0x4b,0x2b,0x37,0xa5,0x94,0xb6,0x4f,0x38,
  0x52,0xe1,0x6d,0xdb,0xb6,0xeb,0xba,0xae,0x25,0x39,0x47,0x2b,0xb9,0x64,0x64,0x4d,
  0xd3,0x34,0xf8,0xef,0xa3,0x65,0xbd,0x25,0x7b,0x5d,0xd7,0xd5,0x22,0x0f,0xb0,0x47,
  0x4d,0x74,0x54,0x56,0xa3,0x8b,0x31,0xc6,0x6d,0xdb,0x36,0x4d,0x27,0xf5,0xa5,0xd4,
  0x66,0x20,0x78,0x71,0xb7,0x38,0xd2,0xb0,0xd1,0xf0,0x50,0xb1,0x96,0xb2,0xe2,0x79,
  0x8c,0x6e,0xdb,0xb6,0x6d,0xe3,0x38,0x8e,0xdb,0xb6,0x6d,0x5d,0xd7,0x75,0x5a,0xb9,
  0x25,0xd9,0xb5,0x1a,0x08,0x3a,0x30,0x8c,0x9e,0x5a,0xf2,0x19,0x42,0xb5,0x30,0x5f,
  0xa0,0x1c,0xce,0x99,0xeb,0x05,0xcb,0xcb,0x2c,0x35,0x6a,0xad,0x4e,0xa5,0x5e,0x7e,
  0x5d,0xd7,0xd5,0x3a,0x7a,0x84,0xf0,0xde,0x31,0x60,0xb4,0x63,0xf5,0xac,0xd6,0x7a,
  0x90,0xf4,0x7d,0xdf,0x6f,0xdb,0xb6,0xcd,0xf3,0x3c,0x33,0xe4,0xcd,0xf3,0x3c,0x6f,
  0xdb,0xb6,0xb1,0xa6,0x93,0xa7,0xc0,0xee,0x61,0x18,0xe4,0x15,0x71,0xb9,0x5c,0x2e,
  0xdb,0xb6,0x6d,0x9a,0x39,0xeb,0xde,0x88,0xb4,0x2c,0xcb,0x72,0xb4,0x62,0xda,0xb6,
  0x6d,0xd1,0x83,0x2e,0xcb,0xb2,0x4c,0xd3,0x34,0xb1,0x1a,0xb3,0xd4,0xb3,0xd6,0x69,
  0xc7,0xf5,0x7a,0xbd,0x32,0xf5,0xc3,0xa8,0x5e,0xf5,0x5a,0xa4,0x46,0x03,0xc9,0x2b,
  0x02,0x3d,0xb7,0xa6,0xa7,0x69,0x9a,0xa6,0xb9,0x5e,0xaf,0xd7,0xbd,0x75,0x88,0xa5,
  0xb2,0x19,0xbd,0x73,0xd3,0x34,0x0d,0x74,0x83,0x91,0x8c,0xe3,0x38,0x86,0xc0,0xdd,
  0x40,0x61,0x00,0xfd,0xac,0xd3,0x49,0xd0,0x75,0x5d,0x87,0x72,0x33,0xe4,0x9d,0x42,
  0x4d,0x06,0xb2,0xd7,0x88,0x4b,0xbd,0xbf,0x46,0xbe,0x2c,0x2b,0x7a,0x7f,0x6d,0x03,
  0x47,0xef,0x37,0x4d,0xd3,0x24,0x47,0x95,0xa3,0x73,0x73,0x4c,0x33,0x2e,0x97,0xcb,
  0x45,0x1a,0x0b,0xbe,0x67,0xad,0x45,0x18,0x9c,0xd1,0x56,0x6a,0x6a,0x7f,0x45,0x98,
  0x73,0x54,0x2b,0xf7,0x2c,0xd0,0x2d,0x3d,0x4e,0x5e,0x19,0x96,0xca,0xc1,0x7b,0xcb,
  0xd7,0x25,0x47,0xdf,0x65,0xae,0x03,0x16,0xfd,0x60,0x9a,0xa6,0x49,0xa3,0xdf,0x19,
  0x3c,0xa5,0x81,0xd4,0x46,0x3e,0xaf,0xc7,0xe7,0xcb,0xe5,0x72,0xb1,0xca,0x46,0x65,
  0x34,0x4d,0xd3,0xa0,0x87,0xd6,0x18,0x1b,0x46,0x0f,0xb9,0x33,0x86,0xed,0xde,0xa3,
  0x95,0x9d,0x2f,0xca,0xe5,0x66,0x42,0x2d,0x1d,0x17,0x78,0x4a,0x03,0xa9,0xed,0xc0,
  0x06,0xa3,0x08,0x3e,0x63,0xfa,0xd2,0x34,0x4d,0xa3,0x91,0x77,0xeb,0x5c,0x65,0x5d,
  0xd7,0x55,0xb3,0x5d,0x19,0x63,0x8c,0x98,0xfa,0xe4,0xf2,0x8f,0x4e,0xff,0xd0,0x01,
  0xec,0x51,0xd3,0x08,0x02,0x63,0x66,0xca,0x44,0x3d,0x30,0x65,0x52,0x61,0x9c,0x8a,
  0x32,0x89,0x31,0x46,0xb9,0x8d,0xb8,0xae,0xeb,0x6a,0xd1,0x6f,0x9a,0xa6,0x29,0x5f,
  0xdb,0xa4,0x94,0xd2,0x34,0x4d,0x93,0xc5,0xe8,0xb0,0x90,0xce,0x77,0xb6,0x34,0xf2,
  0xc6,0x71,0x1c,0xe5,0x42,0x7d,0x18,0x86,0x01,0x07,0x9c,0x35,0xd5,0x0d,0xa6,0x93,
  0xec,0x45,0x3a,0x63,0x9b,0xdc,0x21,0x50,0xfd,0x70,0x5e,0x39,0x18,0xed,0x58,0xa3,
  0x1a,0x5b,0x9e,0x63,0x04,0x07,0x7b,0xdf,0xad,0xc7,0xa3,0x82,0x75,0x16,0xeb,0x1d,
  0x62,0xd4,0xd4,0x8e,0xe4,0x8e,0x53,0x1d,0xe8,0xf5,0xad,0xd3,0x22,0xac,0x35,0x7d,
  0xf4,0x70,0x7e,0x1c,0x4f,0xe5,0xcd,0xeb,0x38,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,
  0xe3,0x38,0x8e,0x82,0x94,0x52,0xf2,0x7d,0xfc,0x3a,0xb1,0xee,0xec,0xc8,0xb8,0x79,
  0x46,0x4c,0x3a,0xe4,0xb1,0xda,0x4b,0xdf,0xf7,0xbd,0x0c,0xea,0xb2,0x6e,0xcf,0x4a,
  0xef,0x01,0xe9,0x99,0xa0,0x22,0xc6,0x18,0xa5,0xd7,0x28,0x5c,0x1b,0x6a,0x72,0x43,
  0x78,0x66,0xe0,0x32,0x61,0x71,0x2e,0x2c,0xb9,0xfa,0x6b,0x0f,0xd0,0x72,0x8f,0x60,
  0xad,0x4e,0x00,0xf1,0x39,0x39,0xda,0xb3,0x90,0x3d,0xaf,0x6d,0xf5,0xb6,0x6f,0x49,
  0x98,0xfb,0xb0,0xd4,0x83,0x35,0xd2,0x0e,0x0d,0x1a,0xf5,0x89,0xc3,0x38,0x6d,0x83,
  0x41,0xe8,0x33,0xcb,0x40,0xe0,0xda,0x8f,0x51,0x0d,0x1d,0x82,0x56,0x36,0x02,0xc1,
  0xe0,0xd3,0x65,0x95,0xf7,0x7f,0x99,0x39,0xb4,0x5e,0xa8,0x25,0x45,0x6b,0x73,0xa9,
  0x7e,0x34,0x18,0xee,0x17,0x79,0xa4,0x1e,0x64,0x5a,0xeb,0x86,0x65,0x20,0x39,0xcc,
  0xc4,0x12,0x6d,0xdb,0xb6,0xe8,0x20,0xd4,0xf2,0xe4,0xdc,0x4f,0x7a,0x7d,0x5a,0x95,
  0x3b,0xeb,0x05,0x3e,0x13,0x18,0x3d,0x2c,0x73,0xe8,0x52,0x3d,0x30,0xea,0xe6,0x8c,
  0xfa,0x6d,0xdb,0xb6,0xcd,0x43,0x83,0xb5,0xe4,0x53,0x2d,0xf5,0xba,0x06,0x43,0x52,
  0xfb,0x86,0xd5,0x0d,0xba,0x34,0x07,0xf4,0xf5,0xcc,0x71,0x58,0xce,0x7b,0x8f,0x62,
  0x20,0x72,0x6d,0xc3,0x70,0x13,0xc9,0xdb,0x21,0x23,0x28,0x8e,0x42,0xc9,0x40,0x6a,
  0x9b,0x6a,0xe5,0x3a,0xd6,0x68,0xc0,0x32,0x9e,0xdc,0x22,0xe7,0x11,0x0c,0x44,0xce,
  0x62,0xd8,0x69,0x7a,0x90,0xc5,0xa6,0xb6,0x36,0x58,0xf5,0x14,0xab,0x76,0x03,0x61,
  0xec,0x5c,0x01,0x94,0x15,0xeb,0x4a,0x56,0x20,0x11,0xab,0x7e,0xb1,0x69,0x70,0x66,
  0x1d,0x54,0xd9,0x16,0x6b,0x4b,0x2b,0xf3,0x48,0x30,0xa3,0xeb,0xd0,0x00,0x11,0x49,
  0x89,0x91,0xc9,0x7a,0xd6,0xc0,0x6a,0x74,0xec,0xb8,0x0d,0xb4,0x3b,0xc8,0xc3,0xd4,
  0xad,0xba,0x11,0xe4,0x19,0x61,0x74,0x0a,0x48,0xd6,0xc0,0xda,0x66,0x97,0xe9,0x7e,
  0xc0,0xba,0xae,0xab,0xb6,0x41,0xe6,0x99,0x56,0xac,0xba,0xe6,0xb2,0x80,0xd6,0x80,
  0x4b,0xfa,0x6d,0x5b,0xbd,0x09,0xf3,0xa8,0xd4,0xbe,0x75,0xcc,0x30,0x10,0x76,0x02,
  0xb5,0x10,0x5e,0xe7,0xe1,0x38,0xbb,0x48,0x29,0x25,0xcb,0x36,0x7e,0xa9,0x01,0xb2,
  0x37,0x75,0xac,0x32,0x65,0x32,0x3f,0x66,0x36,0xfb,0xaa,0x79,0x96,0x18,0x63,0x78,
  0x36,0x7c,0xb7,0x1e,0xce,0x83,0xe1,0x37,0x38,0x39,0x8e,0xe3,0x38,0x8e,0xe3,0x38,
  0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0x63,0xc5,0x7a,0x1a,0xcc,0xba,
  0x16,0x39,0x87,0xe5,0x82,0xb1,0x77,0x72,0xbb,0x6d,0x3a,0xd7,0xf2,0x71,0x1c,0x47,
  0x29,0xd3,0x1c,0x03,0x1d,0x3e,0xc6,0x68,0xa7,0x94,0xd2,0x53,0xb8,0x49,0x3c,0x02,
  0x32,0x3e,0x58,0x2b,0x63,0xaf,0xf1,0x59,0x6e,0x2f,0x95,0x61,0x93,0xd6,0x5b,0x50,
  0x6f,0x19,0x88,0x46,0xf6,0x9e,0x2c,0xed,0x89,0x3f,0xdc,0xb3,0x73,0x9e,0xc2,0x5d,
  0xa2,0x66,0x2e,0x97,0xcb,0x85,0x69,0x20,0x4c,0xdd,0xe0,0x47,0xc4,0xba,0x22,0x38,
  0x07,0xa3,0x80,0xe6,0x59,0x94,0x17,0xbe,0x53,0xd6,0x2b,0xa1,0xe1,0xeb,0x84,0x51,
  0xc8,0x72,0x5b,0x95,0x43,0xa2,0xeb,0xba,0x0e,0x15,0xc0,0x32,0x10,0xd9,0x53,0x5b,
  0xfc,0xa7,0xd8,0xde,0xad,0x39,0xe8,0xb1,0xb5,0x0e,0x7c,0x79,0x0f,0x2f,0xaf,0x4e,
  0xb3,0xc8,0xc3,0x67,0xed,0xf5,0x6b,0xcf,0x4a,0x3e,0x43,0x30,0x3b,0xb7,0x36,0x4d,
  0xd3,0x48,0x0f,0x4f,0x96,0x81,0xe4,0x68,0xe7,0xe5,0xe8,0x41,0x31,0x8a,0xac,0xeb,
  0xba,0x5a,0xe7,0xf8,0x00,0xae,0xe0,0x96,0x10,0xcf,0xbd,0x6b,0xce,0xb4,0x91,0x80,
  0xa5,0xf7,0xcf,0x32,0x10,0x76,0x8c,0xce,0x19,0x31,0x3f,0x56,0x8f,0xed,0xfc,0xda,
  0x3a,0xb3,0x81,0xc4,0xf8,0x7a,0x2d,0x17,0x3e,0x5b,0x2b,0x23,0xc6,0xd7,0x3b,0xf6,
  0xd0,0x40,0xac,0xd1,0x71,0x7b,0x8b,0x7e,0x86,0x57,0x2f,0xa6,0x94,0x96,0x60,0x9d,
  0xbd,0x35,0x83,0xd6,0x88,0x51,0xc1,0x78,0xfe,0x72,0xb9,0x5c,0xb6,0x8d,0x33,0xc5,
  0xaa,0xd9,0x40,0x90,0xb0,0x61,0x5d,0xd7,0xb5,0x9a,0x4d,0x89,0xbd,0xe0,0x12,0xc0,
  0x9a,0xd6,0x58,0x8c,0x0e,0xcf,0x62,0x8e,0x8f,0x06,0x69,0x4d,0x66,0x00,0xc3,0xb5,
  0x26,0x08,0xc0,0x90,0x9e,0x37,0x68,0x6d,0x87,0x80,0xe7,0xcf,0xe8,0x10,0x6a,0x45,
  0x66,0x42,0x64,0xc6,0xc1,0x98,0xc1,0xf4,0xe5,0x4c,0x03,0xb1,0xce,0xa1,0x4b,0xcf,
  0x5a,0xe4,0x01,0x56,0x58,0xeb,0x19,0xfa,0xc9,0x06,0x83,0x7f,0x19,0xb9,0xca,0x6a,
  0x45,0x76,0xd4,0xd6,0x11,0x29,0x9f,0x62,0xd1,0x37,0x37,0xac,0x95,0x1b,0xe3,0xfb,
  0xed,0x3e,0x4d,0xd3,0x34,0xe8,0x61,0xb5,0x3b,0x50,0x78,0x1e,0x53,0x36,0x46,0x8c,
  0x31,0x33,0x29,0x02,0xde,0x17,0xa6,0x05,0xac,0x11,0x4e,0x26,0x3d,0x63,0xed,0xde,
  0xd5,0x1c,0x53,0xd3,0x75,0x5d,0xc7,0xc8,0xcb,0x76,0x7a,0x42,0x0e,0x86,0x81,0xe4,
  0x23,0x91,0x25,0x5b,0xa3,0xdc,0x15,0x92,0x58,0xce,0x05,0xf2,0xad,0x54,0x0b,0x7b,
  0xb9,0x65,0x2d,0x53,0x22,0xd9,0x0b,0x32,0x77,0xef,0x6a,0x0f,0x59,0xc6,0xb5,0xd7,
  0xb5,0x1a,0x71,0x08,0x81,0xb3,0xf0,0x92,0x53,0xb7,0x79,0x9e,0x67,0xeb,0xf4,0x60,
  0x1c,0xc7,0x51,0xc6,0x54,0x5b,0x17,0x71,0x58,0x0c,0xb2,0x32,0x69,0xe4,0x31,0xd0,
  0x8c,0xac,0x80,0xf9,0xe6,0x49,0x8d,0x9c,0xb1,0x8b,0xe5,0x38,0x3f,0x02,0x8c,0xc2,
  0x7e,0x59,0xa6,0xe3,0x14,0xf0,0xd1,0xc3,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,
  0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x79,0x56,0xe4,0xc9,0xb2,0xf5,0x24,0x5d,0x9e,
  0xa2,0xc3,0xb7,0x66,0x9a,0xa6,0x89,0x75,0x0a,0x1e,0xc2,0xc7,0x80,0xb1,0xa3,0xc8,
  0xb2,0xb2,0x3c,0x07,0x42,0xf8,0x98,0x91,0xdd,0xe2,0x72,0xb2,0x2c,0xcb,0xc2,0x8c,
  0x6b,0x4f,0x29,0xa5,0x52,0x08,0x82,0xd6,0x85,0x65,0x2f,0x04,0xda,0xea,0x12,0x33,
  0x4d,0xd3,0x84,0x7b,0x37,0x59,0xf1,0x43,0x14,0x58,0xbe,0x58,0xf9,0xed,0xbb,0x25,
  0x99,0xac,0x4a,0xc7,0xef,0x68,0x9e,0xdd,0xd3,0xcf,0xe2,0x25,0xbc,0xe7,0x7f,0x66,
  0xd5,0x8f,0xd1,0x58,0xf6,0xca,0x6b,0x0d,0x59,0x66,0xc9,0x0b,0x81,0x7f,0x45,0x03,
  0x95,0x18,0x5f,0xd3,0xf7,0xa3,0x87,0xd7,0xc6,0x54,0xa3,0xf7,0x5c,0x96,0x65,0x91,
  0xc6,0xd5,0xb6,0x6d,0x2b,0x1d,0x04,0xad,0xc9,0x0c,0xa4,0xdf,0x98,0xa6,0x51,0xe7,
  0x8d,0x17,0xba,0x69,0x7b,0x40,0x19,0x80,0x05,0x0f,0xe6,0x65,0x59,0x16,0x46,0xcc,
  0x3c,0x1a,0x4e,0x8c,0xaf,0x97,0xb6,0x5a,0xe4,0x69,0x9e,0xfd,0x0a,0x79,0xf2,0xda,
  0xe7,0xb6,0x6d,0xdb,0xa6,0x69,0x9a,0x79,0x9e,0xe7,0x6a,0x0c,0xa4,0xc4,0xd1,0x97,
  0x80,0x42,0xa2,0x50,0x32,0x0d,0x0e,0x46,0x0d,0x46,0xa4,0x9d,0x74,0x4d,0xdf,0x36,
  0x9d,0x77,0x6f,0xa9,0x6c,0x96,0x4a,0x47,0xc7,0xc0,0xba,0x95,0x35,0xd7,0xc5,0x1a,
  0xd0,0x55,0xbb,0x81,0x9c,0x12,0x78,0x75,0xa6,0x5f,0x8d,0xa6,0x21,0xc3,0x18,0xfa,
  0xbe,0xef,0x31,0xdd,0x98,0xe7,0x79,0xce,0x47,0x0b,0xeb,0xcb,0xc5,0xcb,0x1c,0x86,
  0x61,0x58,0xd7,0x75,0xb5,0xa4,0xfd,0xc1,0x67,0x4b,0xbc,0x0a,0xde,0x15,0xd3,0xc5,
  0xbd,0xf4,0x8e,0xa0,0xa3,0xc6,0x25,0xbf,0x66,0x03,0xc1,0xfb,0xa3,0x3b,0x50,0x62,
  0xe8,0x4d,0x29,0x25,0xa6,0xe5,0x61,0xba,0x71,0x74,0x0d,0x22,0x5f,0x9a,0x5c,0x1f,
  0x20,0x41,0x42,0x08,0xf6,0xf4,0x3a,0x98,0x5a,0xa1,0x31,0x62,0x31,0x7b,0x54,0xce,
  0xb6,0x83,0x66,0x0a,0x83,0x7a,0x60,0xe6,0xc0,0xda,0x7b,0x47,0xa8,0x17,0xad,0xbc,
  0x9c,0x1a,0xd6,0x20,0x32,0x4a,0xb4,0xef,0xfb,0x1e,0x53,0x2b,0xab,0x8e,0x21,0x84,
  0x8f,0x8b,0x6b,0x86,0x05,0x5a,0xe6,0xbb,0x25,0x03,0xd9,0x43,0xa3,0xeb,0x5e,0xdc,
  0x77,0xa9,0x21,0xdd,0xab,0x2b,0xa3,0x82,0xb5,0x3a,0x68,0x64,0xd6,0x50,0x5e,0xb6,
  0x3c,0x59,0xa6,0xbd,0x76,0xa3,0xd1,0x31,0x84,0xf0,0x71,0xe7,0x84,0x61,0x20,0x32,
  0xf4,0xf6,0x28,0x98,0x87,0x77,0x5d,0xd7,0x21,0xca,0x6c,0xdb,0x5e,0xd7,0x08,0x72,
  0x54,0xd2,0xca,0xdf,0xab,0x14,0xfc,0xa6,0x46,0x16,0x3e,0x37,0x4d,0xd3,0xe4,0x6b,
  0x28,0xad,0x2c,0x06,0x25,0x99,0x58,0x7b,0x59,0x46,0xcc,0x33,0xf5,0x63,0xcb,0x42,
  0x88,0xb5,0x3a,0x74,0x19,0x73,0xf0,0x6d,0xe3,0x2d,0x0e,0x2d,0x68,0x1b,0xd8,0x3d,
  0xa0,0x23,0xc8,0x1b,0x07,0xbe,0x3f,0x3a,0x2f,0x97,0x95,0xd2,0x34,0x4d,0xd3,0xf7,
  0x7d,0x8f,0xa9,0xe0,0xd1,0x29,0x4c,0x29,0x08,0x69,0x18,0x86,0xc1,0x12,0x86,0x0a,
  0xfd,0xb0,0xab,0xd8,0x75,0x5d,0x97,0xa7,0x16,0xd2,0xc8,0xd3,0xe8,0x72,0xb6,0x3c,
  0x94,0x4b,0x4e,0x51,0x65,0xdb,0x56,0x2f,0x1f,0xd6,0x75,0x5d,0xf3,0xed,0x54,0x2b,
  0x96,0xad,0xc9,0x10,0xde,0x0b,0x1b,0x63,0x8c,0x79,0x81,0x53,0x4a,0x49,0xbb,0x90,
  0xdd,0x6b,0x1c,0xc8,0xbe,0x72,0xb4,0x57,0xdd,0x1b,0x89,0x34,0x67,0x3f,0x32,0x07,
  0x71,0x0e,0x7b,0xb4,0xd4,0xd6,0x0d,0xfb,0x60,0x8f,0x69,0x20,0xe8,0x58,0x4b,0x54,
  0x17,0xbe,0x6c,0xdd,0x19,0x43,0x22,0xb1,0x33,0x2a,0x78,0xaf,0x32,0xa7,0x69,0x9a,
  0x8e,0xca,0x95,0x87,0x52,0x29,0xa5,0x34,0xcf,0xf3,0x6c,0x19,0x85,0x71,0xaa,0x0f,
  0x23,0x9b,0xe7,0x79,0xb6,0x6c,0x9c,0x74,0x5d,0xd7,0xc9,0xb3,0x1e,0x6b,0xcc,0xfc,
  0x5e,0xbd,0x68,0x3b,0x2c,0x76,0x22,0x89,0xdc,0xf3,0xc2,0xfa,0xfe,0xaa,0xe7,0x72,
  0xb9,0x5c,0xf2,0x9d,0x88,0x1a,0xa6,0x81,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0xe3,
  0x38,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0xf3,0xb0,0xdc,0x3a,0xed,
  0xb6,0xb8,0x8a,0x94,0x4e,0x5a,0x2d,0xa7,0xa5,0x7b,0x27,0xea,0x9a,0xd3,0xdb,0x52,
  0x99,0x11,0xde,0x6b,0x29,0x2f,0xcb,0x6f,0xac,0x74,0x9a,0xbf,0xbc,0xa1,0xd1,0x6b,
  0xcf,0x45,0x05,0xb1,0xfd,0x1a,0x1d,0xf3,0xc3,0xdb,0x94,0x52,0xba,0x5e,0xaf,0x57,
  0x4d,0x9e,0x00,0x79,0xca,0x9f,0xbb,0x15,0x69,0x81,0xf7,0x80,0xbc,0x84,0x48,0x95,
  0x2b,0x00,0x8a,0x1d,0xfd,0xdb,0x67,0x7c,0x95,0x81,0x30,0x5c,0xca,0x65,0xec,0xbb,
  0xd6,0x5d,0xc2,0xf2,0xae,0xf6,0x64,0xc1,0x3d,0x42,0xde,0xd0,0x75,0xb4,0x01,0xe6,
  0xb2,0xf2,0xbf,0x69,0xea,0xe4,0x96,0xfb,0x8f,0xe6,0x4a,0x89,0x92,0x1c,0x8b,0xdf,
  0xd4,0xde,0x7d,0x2d,0x2a,0xd9,0xb7,0x2a,0x96,0x51,0xe9,0xcc,0x86,0xc3,0x92,0x29,
  0x9f,0x97,0xc6,0x61,0x19,0x01,0x58,0xe5,0x94,0xf1,0xe8,0xa8,0x48,0x19,0x86,0xa0,
  0x75,0xc5,0x2f,0x95,0x4d,0xa3,0x33,0x7a,0xfb,0x3c,0x61,0x46,0xdb,0xb6,0x2d,0x7c,
  0xd2,0x8e,0xba,0x94,0x4b,0x3d,0xac,0xe1,0xc0,0x32,0x14,0x62,0x1c,0xc7,0x11,0xc6,
  0xda,0x34,0x4d,0x23,0xff,0x76,0xb7,0x11,0x3f,0xb3,0x81,0xf4,0x7d,0xdf,0xcb,0x21,
  0xd8,0x92,0x46,0x88,0x55,0x4e,0xe9,0x8d,0x0a,0x87,0x42,0xd9,0x23,0x1e,0xf5,0x41,
  0xdb,0x04,0xb9,0x83,0xe2,0x51,0x9d,0xe1,0x69,0xbc,0xe7,0xa5,0x8c,0x91,0xee,0xa8,
  0x8b,0x7f,0xae,0x87,0xf6,0x5d,0xa2,0x23,0xb9,0xe5,0x45,0x0d,0x03,0xbf,0x7b,0x6a,
  0xf9,0xcc,0x06,0x02,0x2c,0xd7,0xc3,0xb1,0x74,0x02,0xd2,0x33,0x18,0x3d,0x31,0x72,
  0x3b,0x1d,0xaa,0xd8,0x4c,0x2f,0x18,0x9e,0x2c,0xe7,0x51,0x9d,0xd1,0xb8,0x6e,0x79,
  0x02,0x6b,0xde,0x83,0x7c,0xc6,0x12,0x07,0x84,0x77,0x77,0x6b,0x0a,0x05,0x23,0xbf,
  0x5b,0x7e,0xde,0x58,0x4a,0x1c,0x55,0xb4,0x24,0xdf,0x22,0x83,0x2d,0x33,0x2f,0x1f,
  0x23,0x06,0x86,0x55,0x4e,0xc8,0x41,0x80,0x14,0xa6,0x5c,0x18,0x45,0x2c,0x11,0x8a,
  0xf9,0x46,0xc2,0x51,0x9d,0x61,0xa4,0xb7,0x46,0xda,0x6d,0xd3,0x8f,0x20,0x12,0xcd,
  0x42,0xfd,0xde,0xf2,0x1c,0x2a,0xf7,0x33,0x1b,0x08,0x16,0x9b,0x8c,0xf0,0x62,0x46,
  0x39,0x61,0x0c,0xd8,0xb1,0x92,0x86,0x21,0xd3,0x1e,0x69,0xf5,0xc2,0x7a,0x0b,0xe5,
  0x3d,0xaa,0xf3,0x67,0xff,0xbf,0xcc,0x3e,0xa3,0xd1,0x71,0xdb,0x5e,0x3b,0x06,0xed,
  0x2e,0xd6,0xa9,0x06,0x62,0x16,0xc4,0x50,0xe6,0x8b,0x64,0xe2,0xf9,0xa6,0x69,0x1a,
  0xf4,0x8a,0x56,0x23,0x61,0x94,0x13,0x61,0xba,0xe3,0x1b,0x90,0x89,0x1e,0x59,0x1a,
  0x8b,0x56,0x2f,0x34,0x62,0xb9,0xf0,0xbf,0x57,0x96,0xcc,0x13,0x50,0xfa,0xbb,0x4c,
  0xa1,0x74,0xaf,0xcc,0x92,0x8e,0x5a,0x4a,0xfa,0xe5,0xa3,0xe6,0x5e,0xb8,0xb5,0x4a,
  0xb9,0x5a,0x0c,0x24,0x8f,0x38,0x63,0x19,0x48,0x08,0x1f,0x43,0x5c,0x2d,0x77,0x91,
  0xb3,0xca,0x89,0x0a,0x96,0xbb,0x59,0xd0,0x4b,0x13,0x33,0x5f,0xd2,0x2b,0xdf,0x06,
  0xbd,0x57,0x96,0xcc,0x58,0x28,0x8d,0x40,0x46,0x40,0x6a,0xb6,0xc9,0x59,0x06,0x52,
  0x5a,0xbf,0xc8,0x1d,0x4a,0x19,0x9b,0x7e,0x77,0x44,0xe5,0x59,0x06,0xc2,0x3c,0x07,
  0xc9,0x93,0x49,0x30,0x0d,0x24,0x84,0x8f,0xdb,0xa8,0x9a,0x3c,0x51,0x52,0x66,0xce,
  0x91,0x35,0x83,0xd4,0x4b,0x9e,0x7d,0xa0,0x31,0x6a,0x62,0xe6,0xf7,0xde,0x95,0xdc,
  0x0c,0xb8,0x57,0x56,0x08,0x1f,0x0f,0xf5,0x2c,0x65,0xbd,0x47,0x47,0x0d,0x32,0x8f,
  0x41,0xd7,0x75,0x5d,0x29,0xc7,0xf1,0x21,0x3d,0x6f,0x9d,0x00,0x5b,0x4e,0x87,0x4b,
  0x06,0xa2,0x95,0x55,0x2a,0xa4,0xe5,0xd0,0xb1,0xe4,0x21,0x80,0x4c,0xea,0x5a,0x1d,
  0xf7,0x0e,0xa7,0x8e,0xe8,0x19,0xe3,0x6b,0x4e,0x63,0xf9,0xb9,0x74,0xa2,0x7e,0x44,
  0xc7,0x5c,0x66,0xfe,0x37,0xcd,0xa8,0x39,0x0c,0xc3,0x90,0xc7,0xe1,0x5b,0x62,0xdc,
  0x99,0x5e,0x08,0x9f,0x25,0x3c,0xdf,0x36,0x72,0x4a,0xd2,0x5a,0x68,0xdb,0xb6,0x95,
  0x87,0x54,0xcc,0xcc,0x83,0xce,0xcf,0x43,0x5e,0x49,0x01,0x37,0x13,0x18,0xc8,0xba,
  0xae,0xeb,0x8f,0x34,0x12,0xc7,0xb1,0x20,0x0f,0x86,0x59,0x53,0x3a,0xc7,0xf9,0x51,
  0x34,0x4d,0xd3,0x58,0xf3,0xb5,0x39,0x8e,0xe3,0x38,0x8e,0xe3,0x38,0x8e,0xe3,0x38,
  0x8e,0xe3,0x38,0x4e,0x85,0xc8,0xeb,0xd7,0x98,0x99,0xb0,0xe5,0x61,0x0d,0x7c,0x61,
  0x8e,0xca,0xb8,0x15,0xde,0xa9,0x3d,0xa1,0xdf,0xdb,0xe6,0xd3,0x6e,0xff,0x95,0x4e,
  0x82,0xe1,0x08,0x79,0x8f,0xbc,0x18,0x63,0x2c,0xb9,0xb8,0x8c,0xe3,0x38,0x96,0x9e,
  0x3f,0x72,0xe2,0x0f,0xdd,0x4a,0x2e,0xfd,0x38,0x75,0x3e,0xe2,0x3f,0x95,0xfb,0xc5,
  0x95,0x7e,0xeb,0x5e,0x59,0x78,0xe6,0x56,0xdd,0x5a,0xee,0x6a,0x94,0xb2,0x4d,0xdb,
  0xba,0x25,0xc5,0xac,0x77,0x69,0xb3,0x5c,0x4d,0xce,0x30,0x10,0x3c,0x77,0xef,0xf7,
  0x9f,0x51,0x8a,0x93,0x80,0x67,0xee,0x3d,0x15,0x8c,0x32,0xe6,0xef,0x1c,0x72,0x65,
  0xe3,0x3e,0x7a,0x21,0xaa,0xf4,0x3e,0xc8,0x8d,0x44,0x13,0x6a,0xbc,0x17,0x56,0x7b,
  0xd8,0x4b,0xf6,0x8d,0x33,0x0d,0xc4,0xda,0xf6,0xfe,0x4f,0x50,0x08,0x1f,0x6f,0xe3,
  0xd1,0x06,0xce,0xa3,0x52,0xb4,0x59,0x2e,0xee,0xd5,0x95,0x2d,0x43,0x2b,0xbb,0xe4,
  0x86,0xfe,0x99,0x6b,0xb8,0xa4,0xd4,0xb8,0xa4,0xff,0x99,0x94,0x8b,0x77,0x7b,0x24,
  0xf4,0xb6,0x74,0x6f,0x3b,0xe4,0x1c,0x6d,0xd0,0x32,0x44,0x40,0x96,0xed,0x9e,0x68,
  0xbe,0xa3,0xfa,0x6a,0x33,0xae,0x00,0x46,0x5b,0x29,0x0a,0xb2,0xdc,0x5f,0x27,0xe5,
  0x9d,0xe1,0xef,0x52,0xa3,0x81,0xe0,0x7d,0x61,0x04,0xd0,0x78,0xdd,0xe6,0xa3,0x85,
  0xf4,0x1d,0x92,0x23,0xcb,0x3d,0x51,0x7d,0x25,0x64,0x44,0xa2,0x34,0x3e,0x4d,0x34,
  0x65,0x9e,0x58,0x41,0x1b,0x8b,0x5e,0x02,0xba,0x31,0xee,0x7f,0x39,0xcd,0x40,0xac,
  0xc2,0xe5,0xed,0x3e,0xc0,0xea,0xf1,0xc9,0xd0,0xeb,0x33,0x19,0xd6,0x4e,0x01,0xd3,
  0x01,0x34,0x20,0x4d,0x2f,0x8f,0x67,0xa4,0xcf,0x10,0x7a,0x52,0x34,0x1e,0x6d,0x70,
  0x57,0xee,0xaa,0x6e,0x69,0x84,0x32,0xf9,0x01,0xa6,0x93,0xd6,0xa0,0x33,0xc4,0xe6,
  0xb0,0xee,0x38,0x3f,0xc5,0x40,0x64,0x7a,0x14,0xed,0xfc,0x0f,0x32,0x4a,0x6e,0xc7,
  0x56,0x23,0x39,0xcb,0x40,0x50,0x39,0xda,0x32,0x23,0x49,0x59,0x08,0xef,0xd3,0x8d,
  0x23,0xcf,0xcb,0x70,0x5b,0x19,0x87,0x2e,0xef,0x62,0x94,0x77,0x80,0x6b,0x74,0x94,
  0xc1,0x61,0x8c,0x2b,0xcf,0xa4,0xb7,0xac,0x45,0xaf,0x10,0xde,0xa7,0x6e,0xcc,0xab,
  0xd8,0xe8,0x06,0x92,0xf7,0xf8,0xcc,0x0b,0x3d,0xd1,0xab,0x5a,0x87,0xe1,0xb3,0x0c,
  0x44,0x7b,0xc3,0x6d,0xfe,0xbc,0xe5,0xba,0x61,0x34,0x34,0xf4,0xce,0x7d,0xdf,0xf7,
  0x30,0x0a,0x4c,0x63,0x2c,0x8b,0xd6,0x7c,0x64,0xb7,0x4e,0x63,0x98,0x06,0x87,0x72,
  0x32,0xdb,0xdc,0x69,0x06,0xc2,0xb4,0xe2,0xd2,0xef,0x7c,0xb7,0x0c,0x19,0xda,0x8a,
  0xef,0x34,0xf1,0xde,0x25,0xdd,0x50,0xd1,0x1a,0x39,0xf9,0x45,0x9b,0x21,0x7c,0xdc,
  0x0d,0xb3,0xe8,0x87,0x32,0xc7,0xf8,0x9e,0x29,0x85,0xd1,0x20,0x61,0x74,0x96,0xc5,
  0x39,0x42,0x65,0x19,0x53,0x70,0x09,0xdd,0x40,0xda,0xb6,0x6d,0x65,0xf6,0x39,0xed,
  0xb9,0x45,0x1e,0x90,0x32,0x0c,0xc3,0x80,0x0a,0xb2,0xf4,0x80,0x52,0x57,0x8b,0x0c,
  0x34,0x3a,0xf4,0xf2,0x6d,0xdb,0xb6,0x8c,0x8e,0x41,0xbb,0x33,0x04,0x30,0xca,0xca,
  0x06,0x27,0xbf,0xd3,0xca,0x95,0xc6,0x81,0xef,0x4a,0x3b,0x5b,0x47,0xd1,0x6e,0xed,
  0x4a,0x60,0xac,0x67,0xb8,0x9f,0xd3,0x0d,0x04,0x9f,0xe5,0x35,0xbf,0x47,0x17,0x4c,
  0xa5,0x05,0x3a,0xa8,0x25,0x41,0x9b,0xdc,0xaa,0x94,0x58,0xa3,0x14,0xd1,0x60,0xb4,
  0x3d,0xa1,0x8c,0x43,0xc7,0x77,0x30,0xde,0x6d,0xd3,0x4d,0x89,0x50,0x8f,0xac,0x73,
  0x90,0x92,0x6c,0x4b,0xcf,0x7f,0xab,0xbd,0x6c,0x1b,0xe7,0x1c,0x44,0xfb,0xfc,0xff,
  0xd8,0x3b,0x01,0xd5,0x9c,0x8c,0x96,0x16,0xe8,0xcb,0xb2,0x2c,0xac,0x6b,0x9b,0x6f,
  0x9d,0xe4,0x1e,0x41,0x66,0xe2,0xb0,0xe4,0x62,0xca,0xb1,0xea,0x56,0x7a,0xe7,0x96,
  0x98,0x6d,0x8c,0xe8,0xb7,0x4e,0xd2,0x2d,0xb2,0xad,0x3d,0xff,0x67,0x07,0x85,0x16,
  0xf9,0x34,0x03,0x71,0x9c,0x9f,0xc8,0x51,0x03,0xf9,0xcf,0x99,0xca,0x38,0xce,0xa3,
  0xe3,0x06,0xe2,0x3c,0x25,0xf7,0x4e,0xd5,0xdc,0x40,0x9c,0xa7,0xe2,0xdf,0x7f,0xff,
  0xfd,0xf7,0xbb,0x75,0x70,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0x87,
  0x4d,0x8c,0xfa,0x3b,0xb3,0xf7,0xe4,0x31,0x4e,0x43,0x25,0x88,0x76,0x4c,0x29,0xa5,
  0x9a,0x92,0x0f,0xe3,0x74,0xbf,0xe6,0x84,0xda,0xd2,0x1d,0xff,0x11,0x60,0x9c,0xd2,
  0x53,0x39,0x12,0x22,0x7a,0x0f,0xb9,0x0b,0x81,0x55,0x9e,0xbc,0xc1,0xd4,0x1a,0x12,
  0xcc,0xa6,0xeb,0xba,0xae,0x36,0x9d,0x72,0x1e,0xcd,0xed,0xa2,0x3a,0x7d,0xb5,0xf7,
  0xcb,0x7d,0x06,0xab,0xa0,0x79,0xf6,0x0d,0x96,0x4f,0x16,0x8b,0xb6,0x6d,0xdb,0xf4,
  0xc6,0x77,0xeb,0x52,0xa2,0xba,0x06,0xf7,0x09,0x55,0xea,0x8b,0x51,0x84,0x99,0x68,
  0xa1,0xca,0x82,0x3e,0x21,0x8f,0x56,0x0f,0xdf,0xa1,0xef,0xa7,0x27,0xe9,0x7f,0xfc,
  0xf1,0xc7,0x1f,0x21,0x84,0xf0,0xfb,0xef,0xbf,0xff,0x7e,0xbe,0x3a,0xce,0x2d,0x72,
  0xaf,0x68,0x04,0x3a,0x59,0xe5,0x22,0xf0,0xca,0x1a,0x97,0x83,0x11,0x13,0xb3,0x0e,
  0x6b,0x18,0xc3,0x30,0x0c,0x03,0xe4,0xb1,0xbd,0xb5,0x59,0x3a,0x86,0x10,0x5e,0xa7,
  0x32,0x55,0xc6,0x05,0x3f,0x11,0xb7,0xae,0x11,0xd3,0xca,0x2c,0xc9,0xb2,0xc4,0xad,
  0xe4,0xfa,0x59,0x36,0x00,0x64,0x84,0x23,0xa3,0xbc,0x32,0x14,0x58,0x42,0x69,0xd7,
  0x88,0x34,0x63,0x2d,0xd6,0xdd,0x40,0x8e,0x23,0x93,0xb3,0x61,0xba,0xcb,0x32,0x90,
  0xee,0x0d,0x4b,0xa3,0x46,0x1b,0x91,0xb7,0xef,0x5a,0x76,0x9c,0xf2,0xc0,0x2b,0x19,
  0x24,0xa6,0x91,0x87,0xc8,0xce,0xfc,0x76,0x60,0x4a,0x3b,0xac,0x36,0xf5,0xca,0x13,
  0x51,0x7a,0x67,0x2c,0x03,0x61,0xc8,0xd3,0xe6,0xe6,0xba,0x57,0x37,0xab,0x7e,0x78,
  0x36,0xbf,0x6c,0x94,0x15,0xb4,0x17,0x52,0x4a,0x89,0xb5,0x67,0xee,0x06,0x72,0x1c,
  0xbc,0x33,0xac,0x39,0xac,0x3d,0xaa,0x94,0x19,0x02,0x3f,0x31,0xe0,0x5e,0x0e,0xe1,
  0x7b,0xc9,0xaf,0xf9,0x96,0x53,0x24,0x8b,0x7e,0x60,0x59,0x96,0x85,0x7a,0x6e,0x86,
  0x2c,0x13,0x8c,0x3d,0x7d,0x37,0x90,0xe3,0xec,0x5d,0x29,0xcd,0x30,0x10,0x89,0xb6,
  0x47,0x45,0xd2,0x0b,0x89,0xc5,0x40,0xd0,0xde,0x58,0xe5,0x2d,0xe9,0xb7,0x6d,0x9c,
  0xcc,0x8f,0x21,0x04,0x5d,0xea,0xcc,0x3d,0xdc,0x40,0x74,0x48,0x23,0xb9,0x5e,0xaf,
  0xd7,0x79,0x9e,0x67,0x4b,0x7d,0x20,0xf6,0x1c,0x0d,0xc5,0x9a,0x62,0x67,0x9a,0xa6,
  0x09,0x3d,0x3f,0x63,0x3a,0x3e,0x8e,0xe3,0x88,0x5d,0x2c,0x9c,0x79,0x59,0x8d,0x4e,
  0x26,0x84,0x40,0x42,0x3e,0xab,0x9e,0xff,0x63,0x9a,0xa6,0x89,0x71,0xd4,0xef,0x06,
  0xe2,0x3c,0x0a,0x2f,0xdf,0xf1,0xa3,0x30,0x8e,0x97,0x97,0x97,0x6f,0xf9,0xfd,0x9c,
  0x7b,0x8c,0xb5,0x16,0x5d,0x9d,0x1f,0x0c,0xdb,0x17,0xcb,0x71,0xce,0xe6,0xdb,0x62,
  0xd2,0x3d,0x36,0xd8,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,
  0xe1,0x22,0x4f,0x20,0x6b,0x8a,0x09,0x8e,0x31,0x46,0x6b,0x0c,0xc3,0xa3,0x70,0x66,
  0x3c,0x76,0x75,0xb1,0xde,0x8f,0x84,0x74,0x0b,0xae,0xcd,0x40,0xce,0x3a,0x4f,0x39,
  0xa3,0xc1,0x58,0x65,0x9e,0x79,0x76,0xe4,0xe7,0x52,0xfb,0x7c,0x7a,0x0e,0xf2,0xdb,
  0x6f,0xbf,0xfd,0x16,0x42,0x08,0x7f,0xfe,0xf9,0xe7,0x9f,0x2f,0x2f,0x2f,0x2f,0xbf,
  0xfc,0xf2,0xcb,0x2f,0xe7,0xab,0xe5,0x38,0x0f,0x42,0xcd,0xbd,0x4b,0xcd,0xba,0xb1,
  0xf1,0x11,0xe4,0x7b,0xd8,0x1d,0x41,0xf2,0x6b,0x8b,0x19,0x53,0xac,0xbe,0xef,0x7b,
  0x19,0x63,0xcc,0xf2,0xc7,0x1f,0xc7,0x71,0x64,0xa6,0xd8,0xa9,0x71,0x8a,0x95,0x83,
  0xf8,0xef,0xef,0x9e,0xf2,0x2e,0xcb,0xb2,0xac,0xeb,0xba,0xca,0xba,0x9d,0xa6,0x69,
  0x42,0x04,0xdf,0xba,0xae,0xab,0xf6,0x9a,0xb8,0x18,0x63,0x44,0xde,0x33,0xed,0xfd,
  0x98,0x92,0xcb,0xe5,0x72,0x81,0x8e,0xe6,0xb5,0xeb,0xde,0x3d,0x71,0x5a,0xc1,0x7b,
  0x31,0xc6,0x16,0x1d,0x4b,0xf2,0x18,0xfe,0xfd,0x67,0xf4,0xa8,0x56,0x99,0xf2,0x79,
  0x99,0x73,0x8b,0xe1,0x56,0x6e,0xd1,0xad,0x54,0x07,0x8c,0x7a,0x2e,0xc9,0x60,0x5c,
  0x0c,0x2a,0xa1,0x44,0xc8,0xb2,0x1a,0x0b,0x1c,0x15,0xd1,0x9b,0x30,0x0d,0x04,0xbd,
  0x28,0x4b,0xd7,0x9a,0x0d,0x44,0xde,0x70,0xcb,0x0a,0x17,0x65,0x18,0x08,0x6e,0x31,
  0xc6,0xe7,0x61,0x18,0x86,0xd2,0x05,0xa4,0x47,0xe5,0xc2,0x28,0xac,0xef,0x0f,0x1d,
  0xfe,0xe5,0x72,0xb9,0x20,0x1a,0x93,0x12,0x2c,0x75,0x46,0xa3,0x63,0x84,0x8b,0x4a,
  0x99,0xac,0x24,0x06,0x25,0x5d,0x59,0xb0,0x0c,0x44,0x66,0x0e,0xa9,0x21,0x89,0xc6,
  0x67,0x75,0x60,0x35,0x10,0x4c,0xab,0x58,0xef,0xcf,0xaa,0xd7,0xa7,0x82,0xad,0x72,
  0x90,0xdb,0x89,0x69,0x20,0x67,0xe9,0x6a,0x95,0xc3,0x94,0x29,0x9f,0x97,0x29,0x57,
  0x19,0x79,0x9d,0x18,0x06,0x72,0xef,0x67,0x96,0xdc,0xa3,0xa0,0x63,0x69,0xdb,0xb6,
  0xc5,0x48,0x47,0x59,0xbf,0xb1,0x1a,0x0b,0x16,0x6d,0x39,0x4c,0xdd,0x9e,0xc5,0x40,
  0x42,0x78,0x8f,0xb1,0x66,0x1c,0x94,0x3e,0x83,0x81,0x94,0x62,0xfa,0x29,0xe1,0xb6,
  0xcc,0xc6,0x22,0x33,0xf8,0x31,0xe4,0xe6,0xb9,0x78,0x59,0xbb,0x3a,0x67,0xec,0x62,
  0x59,0xcb,0x5b,0xd2,0x89,0xa5,0xa7,0x45,0x4e,0xfe,0x6c,0x9e,0x8b,0x58,0x5b,0x27,
  0x79,0xdd,0x5a,0xee,0x6e,0x07,0x68,0x77,0x29,0xa5,0x44,0x49,0x28,0x8e,0x6c,0x79,
  0x6c,0x77,0x0e,0xcb,0xe2,0xed,0x91,0x88,0xf1,0xfd,0xfa,0x88,0x67,0x28,0xaf,0x43,
  0x02,0xc3,0xdd,0x4f,0xf7,0xa3,0xc2,0xce,0x09,0x6b,0x53,0xc2,0xf9,0xc1,0x94,0xf2,
  0xca,0xd6,0x7a,0x6f,0x06,0x8b,0xdc,0x8f,0xed,0xa7,0x77,0x08,0x8e,0x01,0x99,0xb8,
  0x2b,0xa5,0x94,0xac,0x39,0x98,0x1e,0x05,0x94,0x3b,0xa5,0x94,0x28,0x99,0xc4,0x1d,
  0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xc7,
  0x71,0x2a,0xc1,0x33,0x86,0x38,0xce,0x0d,0xdc,0xc5,0xe4,0xb1,0xf9,0x34,0x26,0x9d,
  0x75,0x87,0x76,0x08,0xaf,0x81,0x52,0xd2,0xed,0xdd,0x7a,0x0b,0x6a,0x8c,0x31,0xca,
  0x9c,0x5d,0x70,0x0c,0xb4,0xe8,0x26,0x5d,0x62,0xac,0xfa,0xe5,0xee,0xda,0x56,0x79,
  0xb9,0x97,0xac,0x25,0x04,0x35,0xc6,0x18,0xf3,0x88,0x3a,0x8b,0xe7,0xad,0x7c,0x2e,
  0xff,0xac,0xf1,0xc4,0x45,0x3b,0x91,0x61,0xb1,0x16,0x8f,0x5e,0x94,0x37,0xf7,0x66,
  0x50,0x7b,0x80,0xe7,0x7e,0x53,0xb9,0xb2,0x47,0x91,0x0e,0x7b,0x12,0xad,0xbc,0x92,
  0x2c,0x8b,0xbc,0x92,0xaf,0x98,0x25,0x24,0x53,0xba,0xf4,0x33,0x0c,0x2e,0x2f,0x9f,
  0xb5,0xbc,0x79,0x08,0x34,0xfc,0xc6,0x34,0x1d,0x21,0x74,0x69,0xdb,0xb6,0x95,0xb1,
  0xdf,0xf2,0xf3,0x51,0xb9,0xf2,0x8e,0xc2,0xbe,0xef,0x7b,0x18,0x8c,0xb6,0xa3,0x2e,
  0x75,0xf4,0xf8,0x0d,0x93,0x81,0x74,0x5d,0xd7,0xc1,0x3d,0xdd,0xd2,0x60,0xf2,0x1e,
  0x81,0x65,0x20,0xb8,0x37,0x9c,0xdd,0x60,0x58,0x58,0xf5,0xda,0x93,0x63,0x95,0x8b,
  0xd8,0x76,0x8c,0x42,0xd2,0xf3,0xf8,0xa8,0x2c,0x34,0x3e,0xd9,0x90,0xb7,0xed,0xd5,
  0x19,0x15,0x9e,0xdb,0x1a,0xc7,0x54,0x19,0x39,0x69,0xed,0x60,0x10,0xba,0x21,0x75,
  0x31,0x65,0xc2,0x61,0x57,0xc8,0xd9,0xf2,0x18,0x8b,0x61,0x4c,0xd7,0xd6,0x75,0x5d,
  0x6b,0xbb,0x13,0x9e,0xfd,0xfe,0xa4,0x0c,0x18,0x8b,0xb6,0xcc,0x30,0x10,0x18,0x83,
  0xcc,0xb8,0xb2,0xae,0xeb,0x6a,0x99,0x0a,0xca,0x91,0xd8,0x7a,0x07,0xbb,0xec,0x14,
  0xf2,0x0e,0xe2,0x30,0xb2,0x02,0x10,0xc3,0x6b,0x19,0x41,0x20,0x0f,0x3d,0x14,0xdb,
  0x40,0x98,0x60,0x5a,0xc0,0xd8,0x7d,0x62,0xe9,0x59,0x5a,0xd3,0x58,0xe5,0xca,0xde,
  0xde,0x52,0xb7,0xf9,0x95,0xcd,0x32,0xbb,0x09,0x0c,0x50,0x23,0x37,0x37,0xb8,0x79,
  0x9e,0x67,0xad,0x8e,0x00,0xef,0xd1,0xaa,0x5b,0x71,0x8e,0x6f,0x59,0x04,0xef,0xdd,
  0xf3,0xad,0x95,0xc7,0x36,0x10,0xf6,0x1a,0x04,0xb0,0xf4,0x3c,0x23,0xa6,0x5f,0xae,
  0x17,0x2c,0xe1,0x07,0x32,0xee,0x05,0x73,0x7c,0xbc,0x4f,0xed,0x3b,0x94,0xc6,0x11,
  0xc2,0x7b,0xc3,0xb6,0x8e,0xec,0x72,0x2d,0x6c,0xaa,0xdf,0xbc,0x22,0x18,0x53,0x0e,
  0x79,0x8f,0xb6,0xb5,0x82,0xf3,0x5d,0x1d,0x2b,0x32,0xeb,0xde,0xb6,0xbd,0xf6,0x56,
  0x8c,0xf8,0x0d,0x66,0xf6,0xc3,0x7c,0x07,0x90,0x51,0x7e,0x66,0x5c,0xbb,0x8c,0x79,
  0xc1,0x14,0x46,0x1b,0x14,0x97,0xef,0x3a,0xb5,0x6d,0xdb,0x32,0xe2,0xd2,0x43,0x78,
  0x9f,0xb6,0x99,0x62,0x92,0xd8,0x3d,0xf4,0x57,0xcb,0x77,0x9c,0x12,0x72,0x43,0xc7,
  0xb4,0xa6,0x71,0x03,0x71,0x7e,0x22,0x88,0xf0,0xbc,0x77,0x46,0xf4,0x6d,0xd7,0x40,
  0x3b,0xce,0x77,0xf0,0xeb,0xaf,0xbf,0xfe,0x1a,0x42,0x08,0x7f,0xfd,0xf5,0xd7,0x5f,
  0x26,0x41,0x67,0xfb,0x10,0xb9,0x8f,0x92,0xf3,0x1d,0x78,0xbb,0x73,0x1c,0xc7,0x71,
  0x1c,0xc7,0x71,0x1c,0xc7,0x71,0x1c,0xe7,0x7e,0x70,0x92,0xc9,0xf0,0xad,0x09,0x81,
  0xb7,0x33,0x21,0x5d,0x25,0x1c,0xe7,0x5b,0x60,0x05,0x4c,0x49,0x58,0x87,0x8e,0xd2,
  0xcd,0x84,0xa1,0x17,0x93,0xdc,0xf5,0xe7,0xbb,0xf5,0x71,0x4e,0x82,0x72,0xcc,0xbf,
  0x23,0xd3,0x2a,0xa7,0xe6,0x6b,0x19,0xdc,0x40,0xbe,0x87,0x97,0xaf,0xfe,0x41,0x54,
  0xee,0xcb,0xcb,0x0b,0xed,0xb7,0x99,0x32,0xcf,0xd0,0x8f,0x41,0x6e,0x14,0xb5,0xe9,
  0xf7,0x53,0xd9,0x75,0x35,0xc9,0xfd,0xe6,0x01,0xe5,0x66,0x50,0xc7,0x79,0x10,0x0e,
  0xfb,0x62,0xfd,0xfd,0xf7,0xdf,0x7f,0x9f,0xa1,0xc8,0x4f,0x03,0x4e,0x71,0xeb,0xba,
  0xae,0x70,0xab,0x2e,0x25,0x4a,0xb0,0xe2,0x6e,0x13,0x15,0x80,0x80,0x18,0x6b,0x65,
  0xa0,0xd1,0xb0,0x2b,0x95,0x39,0x2f,0xc7,0xc8,0x69,0x09,0x0e,0xdb,0x0b,0x6e,0xda,
  0x36,0x7d,0x88,0x67,0x69,0x0d,0xe2,0xeb,0x91,0x0a,0x90,0xe1,0xb6,0xd6,0x00,0x22,
  0x54,0x28,0xeb,0x7e,0xef,0x5c,0x2e,0x43,0x96,0x0c,0x17,0xd5,0xca,0xc0,0xb6,0x73,
  0xd3,0x34,0xcd,0x30,0x0c,0x03,0x8c,0xce,0x72,0x89,0xce,0x9e,0x81,0x30,0x83,0xc6,
  0x9c,0x83,0x74,0x5d,0xd7,0x99,0x32,0x3f,0x64,0x30,0xaf,0x2e,0x96,0x30,0x0d,0x84,
  0x12,0x6d,0x76,0x02,0x25,0x03,0x71,0xbe,0x91,0xfc,0x7e,0x3d,0x60,0x9d,0x1e,0x9d,
  0x51,0xc1,0x4c,0x99,0xb5,0x36,0x40,0x37,0x90,0xca,0x90,0xf1,0xd9,0x6e,0x20,0x8e,
  0xf3,0x45,0xb8,0x81,0x38,0x8f,0xc4,0x97,0x87,0xdc,0xfe,0xf3,0xcf,0x3f,0xff,0x84,
  0xf0,0x9a,0x72,0xe6,0xab,0x7f,0xfb,0x33,0xa0,0x13,0x74,0x74,0x9c,0x2f,0x47,0xae,
  0x6d,0x6a,0xf5,0xc5,0xfa,0xe9,0xf7,0xb7,0x3b,0x95,0xc3,0x3e,0x0f,0x59,0x96,0x65,
  0x61,0x79,0xf3,0x5a,0xce,0x3f,0x1c,0xc7,0x71,0x9e,0x8a,0xff,0x02,0x63,0xc2,0x1a,
  0x0a,0x49,0x65,0x8b,0xb0,0x00,0x00,0x00,0x00,0x49,0x45,0x4e,0x44,0xae,0x42,0x60,0x82
};

} // namespace OGUI

#endif // H_OGUI_DEFAULT_FONT



