#include <bits/stdc++.h>
using namespace std;
void Affine_Cipher_0(string word, bool isDecipher){
    // If decipher bool is false then we need to cipher else we need to decipher
    if(!isDecipher){
        int a, b, c;
        cout << "Please Enter 3 positive integers 'a, b, c' to use them as keys in the encryption.\n";
        cout << "Make sure that (a * c) mod 26 = 1\n";
        cout << "Fact \"You can use the standard formula {a = 5, b = 8, c = 21} by entering -1 -1 -1.\"\n";
        cin >> a >> b >> c;
        // I made the standard like what the prof. did in the sample to help people with bad math to start faster.
        if(a == -1 && b == -1 && c == -1){
            a = 5;
            b = 8;
            c = 21;
        }
        // Handling cin fail errors and other logical errors.
        while(cin.fail() || (a * c) % 26 != 1 || a < 0 || c < 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 3 positive integers when (a * c) mod 26 = 1.\n";
            cout << "You can enter -1 -1 -1 for the standard formula {a = 5, b = 8, c = 21}\n";
            cin >> a >> b >> c;
            if(a == -1 && b == -1 && c == -1) {
                a = 5;
                b = 8;
                c = 21;
                break;
            }
        }
        string word_encrypted;
        int key;
        for(char &k : word){
            if(isalpha(k)){
                // Making the key first before doing the mod 26
                // to check if it is negative then we got another operation to do with.
                // using (toupper(k) - 'A') to get the value from it.
                // 'A' here is equal to its integer value of the ascii table 65.
                key = a * (toupper(k) - 'A') + b;
                if(key < 0){
                    key = -1 * key;
                    key %= 26;
                    key = 26 - key;
                }
                else{
                    key %= 26;
                }
                // Now adding the char to the word_encrypted.
                // char(key + 'A') is using the ascii code to get the character it is more like char(key + 65).
                word_encrypted += char(key + 'A');
            }
            else{
                word_encrypted += k;
            }
        }
        // I made the encryption print uppercase words because that is what I saw in the sample from the prof.
        cout << "The word \"" << word << "\" after encryption is: " << word_encrypted << '\n';
    }
    else{
        int a, b, c;
        cout << "Please Enter 3 positive integers 'a, b, c' to use them as keys in the decryption process.\n";
        cout << "Make sure that (a * c) mod 26 = 1\n";
        cout << "Fact \"You can use the standard formula {a = 5, b = 8, c = 21} by entering -1 -1 -1.\"\n";
        cin >> a >> b >> c;
        // I made the standard like what the prof. did in the sample to help people with bad math to start faster.
        if(a == -1 && b == -1 && c == -1){
            a = 5;
            b = 8;
            c = 21;
        }
        // Handling cin fail errors and other logical errors.
        while(cin.fail() || (a * c) % 26 != 1 || a < 0 || c < 0){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter 3 positive integers when (a * c) mod 26 = 1.\n";
            cout << "You can enter -1 -1 -1 for the standard formula {a = 5, b = 8, c = 21}\n";
            cin >> a >> b >> c;
            if(a == -1 && b == -1 && c == -1) {
                a = 5;
                b = 8;
                c = 21;
                break;
            }
        }
        string word_decrypted;
        int key;
        for(char &k : word){
            // If the current char is an alpha letter then we add it after encrypting it.
            if(isalpha(k)){
                // Making the key first before doing the mod 26
                // to check if it is negative then we got another operation to do with.
                // using (toupper(k) - 'a') to get the value from it.
                // 'a' here is equal to its integer value of the ascii table 97.
                key = c * ((tolower(k) - 'a') - b);
                // If the key is negative then we calculate the mod by another way as shown in the if condition.
                if(key < 0){
                    key = -1 * key;
                    key %= 26;
                    key = 26 - key;
                }
                // Else we just take the mod normally.
                else{
                    key %= 26;
                }
                // Now adding the char to the word_decrypted.
                // char(key + 'a') is using the ascii code to get the character it is more like char(key + 97).
                word_decrypted += char(key + 'a');
            }
            // Else we add it directly.
            else{
                word_decrypted += k;
            }
        }
        // I made the decryption print lowercase words because that is what I saw in the sample from the prof.
        cout << "The word \"" << word << "\" after decryption is: " << word_decrypted << '\n';
    }
}
void Route_Encrypt_1(string message, int key) {
    // Converting message chars to uppercase.
    for (char c : message) {
        if (isalpha(c)) {
            c = toupper(c);
        }
    }
    int numRows = ceil(static_cast<double>(message.length()) / key); // Calculating number of rows.
    int numCols = key; // Calculating number of columns.

    // Fill the matrix with X.
    vector<vector<char>> matrix(numRows, vector<char>(numCols, 'X'));
    int index = 0; // using this index to iterate in message to fill the chars into the vector.
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols && index < message.length(); ++j) {
            matrix[i][j] = message[index++];
        }
    }

    // Read the grid clockwise, starting from the top right corner
    string encryptedMessage;
    int startRow = 0, endRow = numRows - 1, startCol = numCols - 1, endCol = 0; // We are base 0, so we start the end rows and columns with size - 1.
    while (startCol >= endCol && startRow <= endRow) { // Next four loops is to get the message from the vector using the route way.
        for (int i = startRow; i <= endRow; ++i) {
            encryptedMessage += matrix[i][startCol];
        }
        for (int i = startCol - 1; i >= endCol; --i) {
            encryptedMessage += matrix[endRow][i];
        }
        for (int i = endRow - 1; i >= startRow && startCol != endCol; --i) {
            encryptedMessage += matrix[i][endCol];
        }
        for (int i = endCol + 1; i < startCol && startRow != endRow; ++i) {
            encryptedMessage += matrix[startRow][i];
        }
        startRow++;
        endRow--;
        startCol--;
        endCol++;
    }
    cout << "The word \""<< message << "\" after being ciphered is: " << encryptedMessage << endl;
}
void Route_Decrypt_1(string encrypted_message, int key){
    // Converting the all chars to uppercase.
    for (char c : encrypted_message) {
        if (isalpha(c)) {
            c = toupper(c);
        }
    }
    int numRows = ceil(static_cast<double>(encrypted_message.length()) / key); // Counting number of rows.
    int numCols = key; // Counting number of columns.

    // Fill the matrix with X.
    vector<vector<char>> matrix(numRows, vector<char>(numCols, 'X'));
    int index = 0; // using this index to iterate in message to use put the chars into the vector.
    int startRow = 0, endRow = numRows - 1, startCol = numCols - 1, endCol = 0; // We are base 0, so we start the end rows and columns with size - 1.
    int counter = 0;
    while (startCol >= endCol && startRow <= endRow) {
        for (int i = startRow; i <= endRow; ++i, counter++) { // Next four for loops is to fill the vector with the words in the route way.
            matrix[i][startCol] = encrypted_message[counter];
        }
        for (int i = startCol - 1; i >= endCol; --i, counter++) {
            matrix[endRow][i] = encrypted_message[counter];
        }
        for (int i = endRow - 1; i >= startRow && startCol != endCol; --i, counter++) {
            matrix[i][endCol] = encrypted_message[counter];
        }
        for (int i = endCol + 1; i < startCol && startRow != endRow; ++i, counter++) {
            matrix[startRow][i] = encrypted_message[counter];
        }
        startRow++;
        endRow--;
        startCol--;
        endCol++;
    }
    string decrypted_message;
    for(auto k : matrix){ // Getting the words out of the matrix.
        for(auto l : k){
            decrypted_message += l;
        }
    }
    cout << "The word \""<< encrypted_message << "\" after being deciphered is: " << decrypted_message << endl;
}
void Atbash_Encrypt_V1_2(string message){
    // Iterates through every character in the string to make it Uppercase.
    for (int i =0; i <= message.size(); i++){
        message[i] = toupper(message[i]);
    }
    // Initialize the basic alphabet
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Initialize the cipher alphabet
    string reverseAlpha = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string encryptMessage = "";         // string to store the encrypted message.

    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= alpha.length(); j++){
                // if the character has the same index as the one in the alphabet change it to the encrypted alphabet.
                if (message[i] == alpha[j]){
                    // adds the encrypted character to the string.
                    encryptMessage.push_back(reverseAlpha[j]);
                    break;
                }
            }
        }
            // if the character is anything else it adds it to the encrypted message unchanged.
        else{
            encryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the encrypted Message.
    cout << "The word \""<< message  << "\" after being ciphered is: " << encryptMessage << endl;
}
void Atbash_Decrypt_V1_2(string message){
    // Iterates through every character in the string to make it Uppercase.
    for (int i =0; i <= message.size(); i++){
        message[i] = toupper(message[i]);
    }
    // Initialize the basic alphabet
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Initialize the cipher alphabet
    string reverseAlpha = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    string decryptMessage = "";     // string to store the decrypted message.
    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= reverseAlpha.length(); j++){
                // if the character has the same index as the one in the cipher alphabet change it to the original alphabet.
                if (message[i] == reverseAlpha[j]){
                    // adds the decrypted character to the string.
                    decryptMessage.push_back(alpha[j]);
                    break;
                }
            }
        }
        else{
            // if the character is a space or a punctuation add it to the decrypted message unchanged.
            decryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the decrypted Message.
    cout << "The word \""<< message << "\" after being deciphered is: " << decryptMessage << endl;
}
void Atbash_Encrypt_V2_2(string message){
    // Iterates through every character in the string to make it Uppercase.
    for (int i =0; i <= message.size(); i++){
        message[i] = toupper(message[i]);
    }
    // Initialize the basic alphabet
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Initialize the cipher alphabet
    string reverseAlpha = "MLKJIHGFEDCBAZYXWVUTSRQPON";
    string encryptMessage = "";         // string to store the encrypted message.
    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= alpha.length(); j++){
                // if the character has the same index as the one in the alphabet change it to the encrypted alphabet.
                if (message[i] == alpha[j]){
                    // adds the encrypted character to the string.
                    encryptMessage.push_back(reverseAlpha[j]);
                    break;
                }
            }
        }
            // if the character is a space or a punctuation add it to the encrypted message unchanged.
        else{
            encryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the encrypted Message.
    cout << "The word \""<< message << "\" after being ciphered is: " << encryptMessage << endl;
}
void Atbash_Decrypt_V2_2(string message){
    // Iterates through every character in the string to make it Uppercase.
    for (int i =0; i <= message.size(); i++){
        message[i] = toupper(message[i]);
    }
    // Initialize the basic alphabet
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    // Initialize the cipher alphabet
    string reverseAlpha = "MLKJIHGFEDCBAZYXWVUTSRQPON";
    string decryptMessage = "";     // string to store the decrypted message.
    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= reverseAlpha.length(); j++){
                // if the character has the same index as the one in the cipher alphabet change it to the original alphabet.
                if (message[i] == reverseAlpha[j]){
                    // adds the decrypted character to the string.
                    decryptMessage.push_back(alpha[j]);
                    break;
                }
            }
        }
            // if the character is a space or a punctuation add it to the decrypted message unchanged.
        else{
            decryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the decrypted Message.
    cout << "The word \""<< message << "\" after being deciphered is: " << decryptMessage << endl;
}
void Vingere_Encrypt_3(string message){
    while(message.size() > 80){ // Making sure that the message in meets the conditions.
        cout << "Invalid message to be ciphered\n";
        cout << "Please enter a word maximum 80 character\n";
        cin.ignore();
        getline(cin,message);
    }
    string keyword, encrypt;
    cout << "Please enter The Keyword:";
    cin >> keyword;
    bool isWrongKey = false;
    for(auto &k : keyword){ // Taking keyword and checking it that it meets the conditions.
        if(!isalpha(k)){
            isWrongKey = true;
            break;
        }
    }
    while(isWrongKey || keyword.size() > 8){ // If keyword isn't right one we go into this loop till he input a right key.
        cout << "Invalid keyword it needs to be a word with maximum 8 alphabetic characters\n";
        cout << "Please enter The Keyword:";
        cin >> keyword;
        isWrongKey = false;
        for(auto &k : keyword){
            if(!isalpha(k)){
                isWrongKey = true;
                break;
            }
        }
    }
    for(auto &k : keyword){ // Converting key to uppercase.
        if(isalpha(k)){
            k = toupper(k);
        }
    }
    for(auto &k : message){ // Converting message to uppercase.
        if(isalpha(k)){
            k = toupper(k);
        }
    }
    for (int i = 0; i < message.length(); i++){ // Doing the math equation to convert the message into its decrypted form.
        int j = i % keyword.length();
        if (isalpha(message[i])){
            int newchar =(message[i]+ keyword[j]);
            newchar %= 26;
            newchar += 65;
            encrypt.push_back(char(newchar));
        }
        else {
            encrypt.push_back(message[i]);
        }
    }
    cout << "The word \""<< message << "\" after being ciphered is: " << encrypt << endl;
}
void Vingere_Decrypt_3(string message){
    while(message.size() > 80){ // Making sure that the message meets the conditions.
        cout << "Invalid message to be ciphered\n";
        cout << "Please enter a word maximum 80 character\n";
        cin.ignore();
        getline(cin,message);
    }
    string decrypted_message;
    int used,decrypted_ascii;
    string keyword;
    cout << "Please enter The Keyword:";
    cin >> keyword;
    bool isWrongKey = false;
    for(auto &k : keyword){ // Checking if there is any nonalphabet letters in the input.
        if(!isalpha(k)){
            isWrongKey = true;
            break;
        }
    }
    while(isWrongKey || keyword.size() > 8){ // If the key is wrong we keep going in this loop till he enters a right one.
        cout << "Invalid keyword it needs to be a word with maximum 8 alphabetic characters\n";
        cout << "Please enter The Keyword:";
        cin >> keyword;
        isWrongKey = false;
        for(auto &k : keyword){
            if(!isalpha(k)){
                isWrongKey = true;
                break;
            }
        }
    }
    for(auto &k : keyword){ // Converting the key to uppercase.
        if(isalpha(k)){
            k = toupper(k);
        }
    }
    for(auto &k : message){ // Converting the message to uppercase.
        if(isalpha(k)){
            k = toupper(k);
        }
    }
    for(int i=0;i<message.size();i++){ // Doing the math equation to decrypt the word back to the original word.
        used=i%(keyword.size());
        int temp;
        if(isalpha(message[i])){
            temp= message[i]-65;
            if((temp+130-keyword[used])>64){
                temp+=130;
            }
            else{
                temp+=156;
            }

            decrypted_ascii=temp-keyword[used];
            decrypted_message= decrypted_message+char(decrypted_ascii);
        }
        else{
            decrypted_message+=message[i];
        }

    }
    cout << "The word \""<< message << "\" after being deciphered is: " << decrypted_message << endl;

}
void Baconian_Encrypt_4(string plaintext){
    for(char &k : plaintext){
        k = tolower(k);
    }
    //string key[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};
    // Making the next array of string to use it in our encryption cipher.
    string value[26] = {
            "aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabab", "aabba", "aabbb",
            "abaaa", "abaab", "ababa", "ababb", "abbaa", "abbab", "abbba", "abbbb",
            "baaaa", "baaab", "baaba", "baabb", "babaa", "babab", "babba", "babbb",
            "bbaaa", "bbaab" };
    string encrypted="";
    for(char &l : plaintext) { // Encrypting using the array of string we did earlier.
        if (isalpha(l)) {
            encrypted += value[int(l-'a')];
        }
        else {
            encrypted += l;
        }

    }
    cout << "The word \""<< plaintext << "\" after being ciphered is: " << encrypted << endl;
}
void Baconian_Decrypt_4(string encryptedtext){
    for(char &k : encryptedtext){
        k = tolower(k);
    }
    //char key[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    // Making the next string to use it in our decryption cipher.
    string value[26] = {
            "aaaaa", "aaaab", "aaaba", "aaabb", "aabaa", "aabab", "aabba", "aabbb",
            "abaaa", "abaab", "ababa", "ababb", "abbaa", "abbab", "abbba", "abbbb",
            "baaaa", "baaab", "baaba", "baabb", "babaa", "babab", "babba", "babbb",
            "bbaaa", "bbaab" };

    string decrypted="";
    string temp_string = "";
    for(char &k : encryptedtext){ // Decrypting every 5 letters to its equivalence alphabetical letter.
        if(isalpha(k)){
            temp_string += k;
            if(temp_string.size() % 5 == 0){
                for(int i = 0;i < 26;i++){
                    if(temp_string == value[i]){
                        temp_string = "";
                        decrypted+= char('a' + i);
                    }
                }
            }
        }
        else{
            decrypted += k;
        }

    }
    cout << "The word \""<< encryptedtext << "\" after being deciphered is: " << decrypted << endl;
}
void Simple_Substitution_Encrypt_5(string message){
    string key;
    cout << "Enter Key made of 5 distinct letters:";
    // Get KEY from the user.
    cin.ignore();
    getline(cin, key);
    map <char, short> keytesting;
    bool isNotDistinct = false;
    for(char &k : key){ // Testing if the key is writted wrong and doesn't meet the requirements.
        if(keytesting[k] || key.size() != 5 || isspace(k)){
            isNotDistinct = true;
            break;
        }
        keytesting[k] = 1;
    }
    while(key.size() != 5 || isNotDistinct){
        keytesting.clear();
        isNotDistinct = false;
        cout << "Invalid key it must be 5 distinct letters\n";
        cout << "Please enter a valid key\n";
        getline(cin, key);
        for(char &k : key){
            if(keytesting[k] || key.size() != 5 || isspace(k)){
                isNotDistinct = true;
                break;
            }
            keytesting[k] = 1;
        }
    }
    for (char &c : message) { // Converting all letters to uppercase.
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
    for (char &c : key) { // Converting all letters to uppercase.
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
    // Initialize the basic alphabet
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    string ogAlpha = alpha;
    // Initialize the cipher alphabet
    string cipherAlpha = key;
    for (int j = 0; j < key.length(); j++) {        //iterate through each character in the key
        for (int i = 0; i < alpha.length(); i++){       // iterate through each character in the alphabet
            if (key[j] == alpha[i]){
                alpha.erase(i, 1);
                break;
            }
        }
    }
    cipherAlpha.append(alpha);

    string encryptMessage = "";                 // string to store the encrypted message.
    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= ogAlpha.length(); j++){
                // if the character has the same index as the one in the alphabet change it to the encrypted alphabet.
                if (message[i] == ogAlpha[j]){
                    // adds the encrypted character to the string.
                    encryptMessage.push_back(cipherAlpha[j]);
                    break;
                }
            }
        }
            // if the character is a space or a punctuation add it to the encrypted message unchanged.
        else {
            encryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the encrypted Message.
    cout << "The word \""<< message << "\" after being ciphered is: " << encryptMessage << endl;
}
void Simple_Substitution_Decrypt_5(string message){
    string key;
    cout << "Enter Key made of 5 distinct letters:";
    // Get KEY from the user.
    cin.ignore();
    getline(cin, key);
    map <char, short> keytesting;
    bool isNotDistinct = false;
    for(char &k : key){ // Making sure that the key meet the requirements.
        if(keytesting[k] || key.size() != 5 || isspace(k)){
            isNotDistinct = true;
            break;
        }
        keytesting[k] = 1;
    }
    while(key.size() != 5 || isNotDistinct){
        keytesting.clear();
        isNotDistinct = false;
        cout << "Invalid key it must be 5 distinct letters\n";
        cout << "Please enter a valid key\n";
        getline(cin, key);
        for(char &k : key){
            if(keytesting[k] || key.size() != 5 || isspace(k)){
                isNotDistinct = true;
                break;
            }
            keytesting[k] = 1;
        }
    }
    for (char &c : message) { // Converting letters to uppercase.
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
    for (char &c : key) { // Converting letters to uppercase.
        if (isalpha(c)) {
            c = tolower(c);
        }
    }
    // Initialize the basic alphabet
    string alpha = "abcdefghijklmnopqrstuvwxyz";
    string ogAlpha = alpha;
    // Initialize the cipher alphabet
    string cipherAlpha = key;
    for (int j = 0; j < key.length(); j++) {        //iterate through each character in the key
        for (int i = 0; i < alpha.length(); i++){       // iterate through each character in the alphabet
            if (key[j] == alpha[i]){ // We remove the key words from the alphabet string using these loops.
                alpha.erase(i, 1);
                break;
            }
        }
    }
    cipherAlpha.append(alpha);

    string decryptMessage = "";                 // string to store the decrypted message.
    for (int i =0; i <= message.length(); i++){
        // checks weather the character is a letter or not.
        if (isalpha(message[i])){
            for (int j = 0; j <= cipherAlpha.length(); j++){
                // if the character has the same index as the one in the alphabet change it to the encrypted alphabet.
                if (message[i] == cipherAlpha[j]){
                    // adds the decrypted character to the string.
                    decryptMessage.push_back(ogAlpha[j]);
                    break;
                }
            }
        }
            // if the character is a space or a punctuation add it to the decrypted message unchanged.
        else {
            decryptMessage.push_back(message[i]) ;
        }
    }
    // Printing the decrypted Message.
    cout << "The word \""<< message << "\" after being deciphered is: " << decryptMessage << endl;

}
void Polybius_Square_Cipher_6(string plain, int a, int b, int c, int d, int e) {
    map <char, string> mapping; // Making a map to carry all the (X, Y) values of the 2d array that carries all letters.
    mapping['A'] = to_string(a) + to_string(a);
    mapping['B'] = to_string(a) + to_string(b);
    mapping['C'] = to_string(a) + to_string(c);
    mapping['D'] = to_string(a) + to_string(d);
    mapping['E'] = to_string(a) + to_string(e);
    mapping['F'] = to_string(b) + to_string(a);
    mapping['G'] = to_string(b) + to_string(b);
    mapping['H'] = to_string(b) + to_string(c);
    mapping['I'] = to_string(b) + to_string(d);
    mapping['J'] = to_string(b) + to_string(d);
    mapping['K'] = to_string(b) + to_string(e);
    mapping['L'] = to_string(c) + to_string(a);
    mapping['M'] = to_string(c) + to_string(b);
    mapping['N'] = to_string(c) + to_string(c);
    mapping['O'] = to_string(c) + to_string(d);
    mapping['P'] = to_string(c) + to_string(e);
    mapping['Q'] = to_string(d) + to_string(a);
    mapping['R'] = to_string(d) + to_string(b);
    mapping['S'] = to_string(d) + to_string(c);
    mapping['T'] = to_string(d) + to_string(d);
    mapping['U'] = to_string(d) + to_string(e);
    mapping['V'] = to_string(e) + to_string(a);
    mapping['W'] = to_string(e) + to_string(b);
    mapping['X'] = to_string(e) + to_string(c);
    mapping['Y'] = to_string(e) + to_string(d);
    mapping['Z'] = to_string(e) + to_string(e);
    string ciphered;
    for(auto &k : plain){ // Converting the word using the previous map.
        if(isalpha(k)){
            k = toupper(k);
            ciphered += mapping[k];
        }
        else{
            continue;
        }
    }
    cout << "The word \""<< plain << "\" after being ciphered is: " << ciphered << endl;

}
void Polybius_Square_Decipher_6(string encrypted, int a, int b, int c, int d, int e) {
    map <string, char> mapping; // Making this map to convert the (X, Y) values to its alphabetical letter.
    mapping[to_string(a) + to_string(a)] = 'A';
    mapping[to_string(a) + to_string(b)] = 'B';
    mapping[to_string(a) + to_string(c)] = 'C';
    mapping[to_string(a) + to_string(d)] = 'D';
    mapping[to_string(a) + to_string(e)] = 'E';
    mapping[to_string(b) + to_string(a)] = 'F';
    mapping[to_string(b) + to_string(b)] = 'G';
    mapping[to_string(b) + to_string(c)] = 'H';
    mapping[to_string(b) + to_string(d)] = 'I';
    mapping[to_string(b) + to_string(e)] = 'K';
    mapping[to_string(c) + to_string(a)] = 'L';
    mapping[to_string(c) + to_string(b)] = 'M';
    mapping[to_string(c) + to_string(c)] = 'N';
    mapping[to_string(c) + to_string(d)] = 'O';
    mapping[to_string(c) + to_string(e)] = 'P';
    mapping[to_string(d) + to_string(a)] = 'Q';
    mapping[to_string(d) + to_string(b)] = 'R';
    mapping[to_string(d) + to_string(c)] = 'S';
    mapping[to_string(d) + to_string(d)] = 'T';
    mapping[to_string(d) + to_string(e)] = 'U';
    mapping[to_string(e) + to_string(a)] = 'V';
    mapping[to_string(e) + to_string(b)] = 'W';
    mapping[to_string(e) + to_string(c)] = 'X';
    mapping[to_string(e) + to_string(d)] = 'Y';
    mapping[to_string(e) + to_string(e)] = 'Z';

    string deciphered;
    string temp;
    for(int i=0;i<encrypted.size();i+=2){ // Decrypting the word using the previous map.
        temp += encrypted[i];
        temp += encrypted[i+1];
        deciphered+=mapping[temp];
        temp = "";
    }
    cout << "The word \""<< encrypted << "\" after being deciphered is: " << deciphered << endl;

}
void MorseCode_Encrypt_7(string message){
    for(char &k : message){ // Converting the words to lowercase.
        k = tolower(k);
    }
    string value[26] = { // Making this string to carry every letter's value in morse code.
            ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
            "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
            "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
            "-.--", "--.." };
    string encrypted="";
    for(char &k : message) { // Encrypting every letter to its value.
        if (isalpha(k)) {
            encrypted += value[int(k-'a')];
            encrypted += ' ';
        }
        else if(isspace(k)) {
            encrypted += "  ";
        }
    }
    cout << "The word \""<< message << "\" after being ciphered is: " << encrypted << endl;
}
void MorseCode_Decrypt_7(string encryptedtext){
    bool isNotMorseCode = false;
    for(char &k : encryptedtext){ // Making sure that the input is in morse code syntax.
        if(k != '-' && k != '.' && !isspace(k)){
            isNotMorseCode = true;
            break;
        }
    }
    while(isNotMorseCode){ // If it is not in more code syntax we keep asking for a right message.
        isNotMorseCode = false;
        cout << "The message provided isn't a morse code it got other letters than - or . or space\n";
        cout << "Please enter a right morse code to be deciphered\n";
        cin.ignore();
        getline(cin, encryptedtext);
        for(char &k : encryptedtext){
            if(k != '-' && k != '.' && !isspace(k)){
                isNotMorseCode = true;
                break;
            }
        }
    }
    map <string, char> value = {
            //A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
            // Making this string to carry every letter's value in morse code.
            {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'}, {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'},
            {"..", 'i'}, {".---", 'j'}, {"-.-", 'k'}, {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'}, {".--.", 'p'},
            {"--.-", 'q'}, {".-.", 'r'}, {"...", 's'}, {"-", 't'}, {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'}, {"-..-", 'x'},
            {"-.--", 'y'}, {"--..", 'z'}};
    string decrypted="";
    string temp_string = "";
    string spaces_string = "";
    for(char &k : encryptedtext){ // This loop is to decrypt the morse code message.
        // if we found 3 spaces or more that means we r in a new word else we r in a new char in the word.
        if(isspace(k)){
            spaces_string += ' ';
            continue;
        }
        else{
            if(spaces_string.size() >= 3 && !temp_string.empty()){
                spaces_string = "";
                if(value[temp_string]){
                    decrypted += value[temp_string];
                    decrypted += ' ';

                }
                else{
                    int x = temp_string.size();
                    while(x--){
                        decrypted += '?';
                    }
                }
                temp_string = "";
                temp_string += k;
                spaces_string = "";
            }
            else if(spaces_string.size() == 1 && !temp_string.empty()){
                spaces_string = "";
                if(value[temp_string]){
                    decrypted += value[temp_string];
                }
                else{
                    int x = temp_string.size();
                    while(x--){
                        decrypted +="?";
                    }
                }
                temp_string = "";
                temp_string += k;
                spaces_string = "";

            }
            else{
                temp_string += k;
                spaces_string = "";
            }
        }
    }
    if(value[temp_string]){ // Making sure that there is nothing left in temp_string.
        decrypted += value[temp_string];
    }
    else{
        int x = temp_string.size();
        while(x--){
            decrypted +="?";
        }
    }
    cout << "The word \""<< encryptedtext << "\" after being deciphered is: " << decrypted << endl;
}
string XOR_Encrypt_8(const string& plaintext, const string& key) {
    // This function performs XOR encryption on plaintext using the provided key.
    // It iterates through each character of the plaintext and performs XOR operation with the corresponding character in the key.
    // If the key is shorter than the plaintext, it wraps around.
    string ciphertext;
    for (size_t i = 0; i < plaintext.size(); ++i) {
        ciphertext += plaintext[i] ^ key[i % key.size()];
    }
    return ciphertext;
}
string XOR_Decrypt_8(const string& ciphertext, const string& key) {
    // This function performs XOR decryption on ciphertext using the provided key.
    // It iterates through each character of the ciphertext and performs XOR operation with the corresponding character in the key.
    // If the key is shorter than the ciphertext, it wraps around.
    string plaintext;
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        plaintext += ciphertext[i] ^ key[i % key.size()];
    }
    return plaintext;
}
void railFence_encrypt_9(string message){
    string encrypt;
    string key;
    cout << "Choose a valid Key Value (2~3):";
    cin >> key;
    // Prompt the user to choose a key value of either 2 or 3
    while (key != "2" && key != "3"){
        cout << "INVALID INPUT.\n";
        cout << "Choose a valid Key Value (2~3):";
        cin >> key;
    }
    // Encryption for key value 2
    if (key == "2"){
        for (int i =0; i < message.length(); i+=2){
            encrypt += message[i];
        }
        for (int i =1; i < message.length(); i+=2){
            encrypt += message[i];
        }
        // Display the encrypted message
        cout << "The word \""<< message << "\" after being ciphered is: " << encrypt << endl;
    }
        // Encryption for key value 3
    else if (key == "3"){
        for (int i =0; i < message.length(); i+=4){
            encrypt += message[i];
        }
        for (int i =1; i < message.length(); i+=2){
            encrypt += message[i];
        }
        for (int i =2; i < message.length(); i+=4){
            encrypt += message[i];
        }
        // Display the encrypted message
        cout << "The word \""<< message << "\" after being ciphered is: " << encrypt << endl;
    }
}
void railFence_decrypt_9(string message){
    deque <char> dq1,dq2,dq3;
    string key;
    cout << "Choose a valid Key Value (2~3):";
    cin >> key;
    // Prompt the user to choose a key value of either 2 or 3
    while (key != "2" && key != "3"){
        cout << "INVALID INPUT.\n";
        cout << "Choose a valid Key Value (2~3):";
        cin >> key;
    }
    map <char, int> mp;
    int counter = 0, counter2 = 0, counter3 = 0, counter4 = 0;
    int index = 1;
    string decryptedMessage;
    // Decryption for key value 2
    if (key == "2"){
        for (int i = 0; i < ceil(message.length()); i+=2, counter++){
            dq1.push_back(message[counter]);
        }
        for (int i = 1; i < ceil(message.length()); i+=2, counter++){
            dq2.push_back(message[counter]);
        }
        // Reconstruct the original message
        for (int i =0; i < message.length(); i++){
            if (i % 2 == 0){
                decryptedMessage += dq1[counter2];
                counter2++;
            }
            else {
                decryptedMessage += dq2[counter3];
                counter3++;
            }
        }
        // Display the decrypted message
        cout << "The word \""<< message << "\" after being deciphered is: " << decryptedMessage << endl;
    }
        // Decryption for key value 3
    else if (key == "3"){
        for (int i = 0; i < ceil(message.length()); i+=4, counter++){
            dq1.push_back(message[counter]);
        }
        for (int i = 1; i < ceil(message.length()); i+=2, counter++){
            dq2.push_back(message[counter]);
        }
        for (int i = 2; i < ceil(message.length()); i+=4, counter++){
            dq3.push_back(message[counter]);
        }
        // Reconstruct the original message
        for (int i =0; i < message.length(); i++){
            if  (index == 1){
                decryptedMessage += dq1[counter2];
                counter2++;
                index++;
            }
            else if (index == 2){
                decryptedMessage += dq2[counter3];
                counter3++;
                index++;
            }
            else if (index == 3){
                decryptedMessage += dq3[counter4];
                counter4++;
                index ++;
            }
            else if  (index == 4){
                decryptedMessage += dq2[counter3];
                counter3++;
                index = 1;
            }
        }
        // Display the decrypted message
        cout << "The word \""<< message << "\" after being deciphered is: " << decryptedMessage << endl;
    }
}
string string_to_hex(const string& input) {
    // This function converts a string to its hexadecimal representation.
    // It iterates through each character of the input string and converts it to its hexadecimal representation.
    stringstream hex_stream;
    hex_stream << hex << setfill('0');
    for (unsigned char c : input) {
        hex_stream << setw(2) << static_cast<unsigned int>(c);
    }
    return hex_stream.str();
}
string hex_to_string(const string& hex) {
    // This function converts a hexadecimal string to its corresponding string representation.
    // It iterates through each pair of characters in the hexadecimal string, converts them back to their original byte values, and appends them to the result string.
    string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        char byte = (char)strtol(byteString.c_str(), nullptr, 16);
        result += byte;
    }
    return result;
}
int main(){
    while(true){
        bool isDecipher = false;
        string word;
        cout << "Ahlan ya user ya habibi.\nWhat do you like to do today?\n";
        cout << "1) Cipher a message\n2) Decipher a message\n3) End\n";
        string choice;
        cin >> choice;
        // Making the choice lowercase to handle any upper case problems.
        for(char &k : choice){
            k = tolower(k);
        }
        // Next conditions trying to handle user input as much as possible.
        // If the user chose to cipher then decipher is false.
        if(choice == "1" || choice == "1)" || choice == "cipher"){
            isDecipher = false;
        }
        // If the user chose to decipher then decipher is true.
        else if(choice == "2" || choice == "2)" || choice == "decipher"){
            isDecipher = true;
        }
        else if(choice == "exit" || choice == "3" || choice == "end" || choice == "3)" ){
            break;
        }
        else{
            cout << "\"" << choice <<"\" Is and invalid choice.\nRestarting the program.\n";
            continue;
        }
        // If decipher is false then we cipher.
        cout << "Please enter the word that you want to " << ((!isDecipher) ? "cipher\n" : "decipher\n");
        // I'm using cin.ignore() because we are using cin before it which cause problems with getline().
        cin.ignore();
        getline(cin,word);
        while(true){
            cout << "Which Cipher do you like to choose?\n";
            cout << "1) Affine Cipher.\n2) Route Cipher.\n3) Atbash Cipher.\n4) Vignere Cipher.\n5) Baconian Cipher.\n6) Simple Substitution Cipher.\n7) Polybius Square Cipher.\n8) Morse Code Cipher.\n9) XOR Cipher.\n10) Rail-fence Cipher." << endl;
            string cipher_name;
            cin >> cipher_name;
            // Making the cipher_name lowercase to handle any upper case problems.
            for(char &k : cipher_name){
                k = tolower(k);
            }
            if(cipher_name == "1" || cipher_name == "1)" || cipher_name == "Affine"){
                // Sending string and bool to use them in the function.
                Affine_Cipher_0(word, isDecipher);
                break;
            }
            else if(cipher_name == "2" || cipher_name == "2)" || cipher_name == "Route"){
                string key;
                cout << "Please Enter the integer key to use it in Route cipher\n";
                bool isNotRightKey;
                while(true){ // Checing if the key is wrong.
                    isNotRightKey = false;
                    cin >> key;
                    for(char &k : key){
                        if(!isdigit(k)){
                            isNotRightKey = true;
                            break;
                        }
                    }
                    if(isNotRightKey){
                        cout << "Invalid Key please enter a valid integer key\n";
                    }
                    else{
                        break;
                    }
                }
                if(!isDecipher){
                    Route_Encrypt_1(word, stoi(key));
                }
                else{
                    Route_Decrypt_1(word, stoi(key));
                }
                break;
            }
            else if(cipher_name == "3" || cipher_name == "3)" || cipher_name == "Atbash"){
                string version;
                cout << "Please choose the version of atbash that you want to use.\n";
                cout << "1) Version 1.0\n2) Version 2.0\n";
                cin >> version;
                while(version != "1" && version != "2" && version != "1)" && version != "2)" && version != "Version 1.0" && version != "Version 2.0"){
                    cout << "\"" << version << "\" Isn't one of the choices please choose 1 or 2.\n";
                    cin >> version;
                }
                if(version == "1" || version == "1)" || version == "Version 1.0"){
                    if(!isDecipher){
                        Atbash_Encrypt_V1_2(word);
                    }
                    else{
                        Atbash_Decrypt_V1_2(word);
                    }
                }
                else{
                    if(!isDecipher){
                        Atbash_Encrypt_V2_2(word);
                    }
                    else{
                        Atbash_Decrypt_V2_2(word);
                    }
                }
                break;
            }
            else if(cipher_name == "4" || cipher_name == "4)" || cipher_name == "Vignere"){
                if(!isDecipher){
                    Vingere_Encrypt_3(word);
                }
                else{
                    Vingere_Decrypt_3(word);
                }
                break;
            }
            else if(cipher_name == "5" || cipher_name == "5)" || cipher_name == "Baconian"){
                if(!isDecipher){
                    Baconian_Encrypt_4(word);
                }
                else{
                    Baconian_Decrypt_4(word);
                }
                break;
            }
            else if(cipher_name == "6" || cipher_name == "6)" || cipher_name == "Simple" || cipher_name == "Substitution"){
                if(!isDecipher){
                    Simple_Substitution_Encrypt_5(word);
                }
                else{
                    Simple_Substitution_Decrypt_5(word);
                }
                break;
            }
            else if(cipher_name == "7" || cipher_name == "7)" || cipher_name == "Polybius"){
                int a, b, c, d, e;
                cout << "Please Enter 5 integers from 0 to 9 separated with a space to use it in Polybius cipher\n";
                cin >> a >> b >> c >> d >> e;
                while(cin.fail() || a > 9 || a < 0 || b > 9 || b < 0 || c > 9 || c < 0 || d > 9 || d < 0 || e > 9 || e < 0){
                    // If cin failed by input char or out of legal input we go into this loop.
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    cout << "Please Enter 5 integers from 0 to 9 separated with a space to use it in Polybius cipher\n";
                    cin >> a >> b >> c >> d >> e;
                }
                if(!isDecipher){
                    Polybius_Square_Cipher_6(word, a, b, c, d, e);
                }
                else{
                    bool isNotFullNumbers = false;
                    for(auto &k : word){ // If the input isn't full numbers integar we go into th
                        if((int(k) >= 48 && int(k <= 57)) || isspace(k)){
                            continue;
                        }
                        else{
                            isNotFullNumbers = true;
                            break;
                        }
                    }
                    while(isNotFullNumbers){
                        cout << "The word \""<< word << "\" Isn't a Full numbers word to be decrypted in Polybius Square cipher\n";
                        cout << "Please enter a Hexadecimal number to be deciphered\n";
                        cin.ignore();
                        getline(cin,word);
                        isNotFullNumbers = false;
                        for(auto &k : word){
                            if((int(k) >= 48 && int(k <= 57)) || isspace(k)){
                                continue;
                            }
                            else{
                                isNotFullNumbers = true;
                                break;
                            }
                        }
                    }
                    Polybius_Square_Decipher_6(word, a, b, c, d, e);
                }
                break;
            }
            else if(cipher_name == "8" || cipher_name == "8)" || cipher_name == "Morse"){
                if(!isDecipher){
                    MorseCode_Encrypt_7(word);
                }
                else{
                    MorseCode_Decrypt_7(word);
                }
                break;
            }
            else if(cipher_name == "9" || cipher_name == "9)" || cipher_name == "XOR" || cipher_name == "xor"){
                string key;
                cout << "Please enter a key to use in XOR cipher\n";
                cin >> key;
                if(!isDecipher){
                    string ciphertext = XOR_Encrypt_8(word, key);
                    string word_to_hexa = string_to_hex(ciphertext);
                    int oneandtwo = 0;
                    string encrypted_word;
                    for(char &k : word_to_hexa){
                        oneandtwo++;
                        if(oneandtwo <= 2){
                            encrypted_word += k;
                        }
                        else{
                            encrypted_word += ' ';
                            encrypted_word += k;
                            oneandtwo = 1;
                        }
                    }
                    cout << "The word \""<< word << "\" after being ciphered is: " << encrypted_word << endl;
                }
                else{
                    bool isNotHexa = false;
                    for(auto &k : word){ // Checing if the input isn't a full hexadecimal input.
                        if((int(k) <= 70 && int(k) >= 65) || (int(k) >= 97 && int(k) <= 102) || (int(k) >= 48 && int(k <= 57)) || isspace(k)){
                            continue;
                        }
                        else{
                            isNotHexa = true;
                            break;
                        }
                    }
                    while(isNotHexa){ // loop till he enters a right hexadecimal input.
                        cout << "The word \""<< word << "\" Isn't a hexadecimal number to be deciphered in XOR cipher\n";
                        cout << "Please enter a Hexadecimal number to be deciphered\n";
                        cin.ignore();
                        getline(cin,word);
                        isNotHexa = false;
                        for(auto &k : word){
                            if((int(k) <= 70 && int(k) >= 65) || (int(k) >= 97 && int(k) <= 102) || (int(k) >= 48 && int(k <= 57)) || isspace(k)){
                                continue;
                            }
                            else{
                                isNotHexa = true;
                                break;
                            }
                        }
                    }
                    string temp_word;
                    for(char &k : word){
                        k = tolower(k);
                        if(isdigit(k) || (k >= 'a' && k <= 'z')){
                            temp_word += k;
                        }
                    }
                    word = temp_word;
                    cout << "The word \""<< word << "\" after being deciphered is: " << XOR_Decrypt_8(hex_to_string(word),key) << endl;
                }
                break;
            }
            else if(cipher_name == "10" || cipher_name == "10)" || cipher_name == "Rail-fence"){
                if(!isDecipher){
                    railFence_encrypt_9(word);
                }
                else{
                    railFence_decrypt_9(word);
                }
                break;
            }
            else{
                cout << "\"" << choice <<"\" Is an invalid choice.\n";
                continue;
            }
        }
    }
    return 0;
}
