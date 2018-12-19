#pragma once
extern "C" __declspec(dllexport) int get_rs_mask(int shift);
extern "C" __declspec(dllexport) void shift_right(char* buf, int msg_len, int shift);
extern "C" __declspec(dllexport) int get_ls_mask(int shift);
extern "C" __declspec(dllexport) void shift_left(char* buf, int msg_len, int shift);
extern "C" __declspec(dllexport) void crypt(char* buf, int msg_len, bool decrypt);
