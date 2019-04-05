#include <stdio.h>
#include <string.h>
#include <math.h>
#include <openssl/aes.h>

int main()

{
    char req_num[12];
	unsigned long long longInt; // 190550043697
    unsigned char final_key[12];
    unsigned char aes_user_key [16];
    unsigned char aes_iv [16];
    unsigned long long req_num_encrypted;
    unsigned char formatted_req_num_encrypted [12];
    int operation_amount = 0;
    AES_KEY aes_key;


    void LongToByteArray(unsigned char byteArray[8], unsigned long longInt) {
    	int i;
		for (i=0; i < 8; i++) {
		    byteArray[i] = (char)(longInt >> (i*8) & 0xFF);
		}
	}

	unsigned long StrToULong(char str[12]) {
		int len = 12;
    	int i;
		unsigned long longInt;
		for (i=0; i<len; i++) {
			longInt += (str[len - i - 1] - 0x30) * pow(10, i);
		}
		return longInt;
	}
    
	while (strlen(req_num) != 12) {
		printf("Request number (12 characters, no spaces): ");
		scanf("%12s", req_num);
	}

	while (operation_amount != 5000 && operation_amount != 2000) {
		printf("Number of points (5000 or 2000): ");
		scanf("%d", &operation_amount);
	}

	longInt = StrToULong(req_num);

    unsigned char byteArray[8];
    memset(byteArray, 0, 8);
    LongToByteArray(byteArray, longInt);

    memset(aes_user_key,0,0x10);
    memset(aes_iv,0,0x10);
    strcpy((char *)aes_user_key,"cityManageoffer");
    sprintf((char *)aes_iv,"initvector_%d",operation_amount);
    AES_set_encrypt_key(aes_user_key,0x80,&aes_key);
    memset(&req_num_encrypted,0,0x10);
    AES_cbc_encrypt(byteArray,(unsigned char *)&req_num_encrypted,8,&aes_key,aes_iv,1);

    sprintf((char *)&formatted_req_num_encrypted,"%llu",req_num_encrypted);
    memset(&final_key,0,0xd);
    strncpy(final_key, formatted_req_num_encrypted, 12);
    printf("%s\n", final_key);
    return 0;
}
