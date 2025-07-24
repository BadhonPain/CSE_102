#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DOCS 50
#define MAX_LEN 5000
#define MAX_TOKENS 500
#define MAX_TOKEN_LEN 50
#define NUM_STOP_WORDS 8

char documents[MAX_DOCS][MAX_LEN];
char tokens[MAX_TOKENS][MAX_TOKEN_LEN];
char stop_words[NUM_STOP_WORDS][MAX_TOKEN_LEN] = {"the", "is", "a", "an", "and", "in", "of", "to"};
int docs_count = 0;
int token_count = 0;
int preprocessed = 0;

void display_help() {
    printf("set        - Prompt for the number of documents and their text.\n");
    printf("preprocess - Apply normalization, tokenization, stop-words removal, and stemming orderly.\n");
    printf("tf         - Compute and display Term Frequency for a specified word across documents.\n");
    printf("idf        - Compute and display Inverse Document Frequency for a specified word.\n");
    printf("tfidf      - Compute and display TF-IDF scores for a specified word across documents.\n");
    printf("help       - Print the list of all available commands.\n");
    printf("stat       - Display TF, IDF, and TF-IDF for all tokens across all documents in a matrix format.\n");
    printf("exit       - Exit the program.\n");
}

void normalize_case_all() {
    printf("Normalized Documents:\n");
    for (int i = 0; i < docs_count; i++) {
        for (int j = 0; documents[i][j]; j++) {
            documents[i][j] = tolower(documents[i][j]);
        }
        printf("Document %d: %s\n", i + 1, documents[i]);
    }
    printf("Documents normalized.\n");
}

void tokenize_all() {
    token_count = 0;
    char *token;

    for (int i = 0; i < docs_count; i++) {
        char temp[MAX_LEN];
        strcpy(temp, documents[i]);
        token = strtok(temp, " ,:?.!;");
        
        while (token != NULL && token_count < MAX_TOKENS) {
            int valid = 0;
            for (int k = 0; token[k] != '\0'; k++) {
                if (isalnum(token[k])) {
                    valid = 1;
                    break;
                }
            }
            
            if (valid) {
                strncpy(tokens[token_count], token, MAX_TOKEN_LEN - 1);
                tokens[token_count][MAX_TOKEN_LEN - 1] = '\0';
                token_count++;
            }
            token = strtok(NULL, " ,:?.!;");
        }
    }
    
    printf("Tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
    printf("Tokenization Complete. Total tokens: %d\n", token_count);
}

void remove_stop_words_all() {
    int newCount = 0;
    char tokens_tempr[MAX_TOKENS][MAX_TOKEN_LEN];
    
    for (int i = 0; i < token_count; i++) {
        int word_Stopped = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++) {
            if (strcmp(tokens[i], stop_words[j]) == 0) {
                word_Stopped = 1;
                break;
            }
        }
        
        if (!word_Stopped) {
            strcpy(tokens_tempr[newCount], tokens[i]);
            newCount++;
        }
    }

    token_count = newCount;
    for (int i = 0; i < token_count; i++) {
        strcpy(tokens[i], tokens_tempr[i]);
    }
    
    printf("Tokens after stop-word removal:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
    printf("Stop Word removal complete. Tokens remaining: %d\n", token_count);
}

void stem_all_tokens() {
    for (int i = 0; i < token_count; i++) {
        int length = strlen(tokens[i]);
        if (length > 3 && strcmp(tokens[i] + length - 3, "ing") == 0) {
            tokens[i][length - 3] = '\0';
        }
        else if (length > 2 && strcmp(tokens[i] + length - 2, "ed") == 0) {
            tokens[i][length - 2] = '\0';
        }
        else if (length > 1 && tokens[i][length - 1] == 's') {
            tokens[i][length - 1] = '\0';
        }
    }
    
    printf("Stemmed tokens:\n");
    for (int i = 0; i < token_count; i++) {
        printf("%d. %s\n", i + 1, tokens[i]);
    }
    printf("Stemming complete. Total stemmed tokens: %d\n", token_count);
}

double compute_tf(char word[], int doc_id) {
    if (doc_id < 1 || doc_id > docs_count) 
    {
        printf("Invalid document ID. Must be between 1 and %d.\n", docs_count);
        return 0.0;
    }
    
    char doc_cpy[MAX_LEN];
    strcpy(doc_cpy, documents[doc_id - 1]);

    char stemmedWord[MAX_TOKEN_LEN];
    strcpy(stemmedWord, word);
    
    
    stemmedWord[strlen(word)] = '\0';
    
    for (int i = 0; stemmedWord[i] != '\0'; i++) {
        stemmedWord[i] = tolower(stemmedWord[i]);
    }
    
    int length = strlen(stemmedWord);
    if (length > 3 && strcmp(stemmedWord + length - 3, "ing") == 0) {
        stemmedWord[length - 3] = '\0';
    }
    else if (length> 2 && strcmp(stemmedWord + length- 2, "ed") == 0) {
        stemmedWord[length - 2] = '\0';
    }
    else if (length > 1 && stemmedWord[length - 1] == 's') {
        stemmedWord[length - 1] = '\0';
    }
    
    char *token = strtok(doc_cpy, " ,.:;?!()");
    int tempTokenCount = 0;
    char temp_tokens[MAX_TOKENS][MAX_TOKEN_LEN];
    while (token != NULL && tempTokenCount < MAX_TOKENS) {
        for (int i = 0; token[i] != '\0'; i++) 
            token[i] = tolower(token[i]);
        int stoppedWord = 0;
        for (int j = 0; j < NUM_STOP_WORDS; j++) {
            if (strcmp(token, stop_words[j]) == 0) {
                stoppedWord = 1;
                break;
            }
        }
        
        if (!stoppedWord) {
            strncpy(temp_tokens[tempTokenCount], token, MAX_TOKEN_LEN - 1);
            temp_tokens[tempTokenCount][MAX_TOKEN_LEN - 1] = '\0';
            
            int length = strlen(temp_tokens[tempTokenCount]);
            if (length > 3 && strcmp(temp_tokens[tempTokenCount] + length - 3, "ing") == 0) {
                temp_tokens[tempTokenCount][length - 3] = '\0';
            }
            else if (length > 2 && strcmp(token + length - 2, "ed") == 0) {
                temp_tokens[tempTokenCount][length - 2] = '\0';
            }
            else if (length > 1 && token[length - 1] == 's') {
                temp_tokens[tempTokenCount][length - 1] = '\0';
            }
            
            tempTokenCount++;
        }
        token = strtok(NULL, " ,.:;?!()");
    }
    double word_count = 0;
    for (int i = 0; i < tempTokenCount; i++) {
        if (strcmp(temp_tokens[i], stemmedWord) == 0) {
            word_count ++;
        }
    }
    if (tempTokenCount == 0) 
        return 0.0;
    return (double) word_count / tempTokenCount;
}



double compute_idf(char word[])
{
    if (docs_count == 0)
    {
        printf("No documents set. Use 'set' command first.\n");
        return -1.0;
    }
    char processed_word[MAX_TOKEN_LEN];
    strcpy(processed_word, word);

    processed_word[strlen(word)] = '\0';
    for (int i = 0; processed_word[i] != '\0'; i++)
        processed_word[i] = tolower(processed_word[i]);

    int length = strlen(processed_word);
    if (length > 3 && strcmp(processed_word + length - 3, "ing") == 0)
        processed_word[length - 3] = '\0';
    else if (length > 2 && strcmp(processed_word + length - 2, "ed") == 0)
        processed_word[length - 2] = '\0';
    else if (length > 1 && processed_word[length - 1] == 's')
        processed_word[length - 1] = '\0';

    int docs_freq = 0;
    for (int i = 0; i < docs_count; i++)
    {
        char tempr[MAX_LEN], tokens_tempr[MAX_TOKENS][MAX_TOKEN_LEN];
        int tokens_tempr_counter = 0;
        strcpy(tempr, documents[i]);

        // tokenizing
        char *token = strtok(tempr, " ,.:;?!()");

        while (token != NULL && tokens_tempr_counter < MAX_TOKENS) // !tokens_temp_ccounter
        {
            // normalizing
            for (int j = 0; token[j] != '\0'; j++)
            {
                token[j] = tolower(token[j]);
            }
            // stop word removing
            int word_Stopped = 0;
            for (int k = 0; k < NUM_STOP_WORDS; k++)
            {
                if (strcmp(token, stop_words[k]) == 0)
                {
                    word_Stopped = 1;
                    break;
                }
            }
            // stemming
            if (!word_Stopped)
            {
                char tokens_tempr[MAX_TOKENS][MAX_TOKEN_LEN];
                strncpy(tokens_tempr[tokens_tempr_counter], token, MAX_TOKEN_LEN - 1);

                tokens_tempr[tokens_tempr_counter][MAX_TOKEN_LEN - 1] = '\0';
                tokens_tempr_counter++;
                int length = strlen(tokens_tempr[tokens_tempr_counter - 1]);
                if (length > 3 && strcmp(tokens_tempr[tokens_tempr_counter - 1] + length - 3, "ing") == 0)
                    tokens_tempr[tokens_tempr_counter - 1][length - 3] = '\0';
                else if (length > 2 && strcmp(token + length - 2, "ed") == 0)
                    tokens_tempr[tokens_tempr_counter - 1][length - 2] = '\0';
                else if (length > 1 && token[length - 1] == 's')
                    tokens_tempr[tokens_tempr_counter - 1][length - 1] = '\0';
            }

            token = strtok(NULL, " ,.:;?!()");
        }
        for (int j = 0; j < tokens_tempr_counter; j++)
        {
            if (strcmp(tokens_tempr[j], processed_word) == 0)
            {
                docs_freq++;
                break;
            }
        }
    }

    if (docs_freq == 0)
    {
        return 0.0;
    }

    return log10((double)MAX_DOCS / (docs_freq + 1));
}

void compute_tfidf_all(char word[]) {
    double idf = compute_idf(word);
    for (int i = 0; i < docs_count; i++) {
        double tf = compute_tf(word, i + 1);
        printf("Document %d: %.4f\n", i + 1, tf * idf);
    }
}

void display_stat() {
    char distinct_toks[MAX_TOKENS][MAX_TOKEN_LEN];
    int distinct_count = 0;

    for (int i = 0; i < token_count; i++) {
        int found = 0;
        for (int j = 0; j < distinct_count; j++) {
            if (strcmp(tokens[i], distinct_toks[j]) == 0) {
                found = 1;
                break;
            }
        }
        
        if (!found) {
            strcpy(distinct_toks[distinct_count], tokens[i]);
            distinct_count++;
        }
    }

    for (int i = 0; i < distinct_count - 1; i++) {
        for (int j = i + 1; j < distinct_count; j++) {
            if (strcmp(distinct_toks[i], distinct_toks[j]) > 0) {
                char temp[MAX_TOKEN_LEN];
                strcpy(temp, distinct_toks[i]);
                strcpy(distinct_toks[i], distinct_toks[j]);
                strcpy(distinct_toks[j], temp);
            }
        }
    }

    printf("============== TF ================\n");
    printf("%-15s", "Token");
    for (int i = 1; i <= docs_count; i++) {
        printf("  doc%-3d", i);
    }
    printf("\n");

    for (int i = 0; i < distinct_count; i++) {
        printf("%-15s", distinct_toks[i]);
        for (int j = 1; j <= docs_count; j++) {
            double tf = compute_tf(distinct_toks[i], j);
            printf("  %.4f", tf);
        }
        printf("\n");
    }

    printf("=============== IDF ===============\n");
    printf("%-15s  IDF\n", "Token");
    for (int i = 0; i < distinct_count; i++) {
        printf("%-15s  %.4f\n", distinct_toks[i], compute_idf(distinct_toks[i]));
    }

    printf("============= TF-IDF ==============\n");
    printf("%-15s", "Token");
    for (int i = 1; i <= docs_count; i++) {
        printf("  doc%-3d", i);
    }
    printf("\n");

    for (int i = 0; i < distinct_count; i++) {
        printf("%-15s", distinct_toks[i]);
        double idf = compute_idf(distinct_toks[i]);
        for (int j = 1; j <= docs_count; j++) {
            double tf = compute_tf(distinct_toks[i], j);
            printf("  %.4f", tf * idf);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    char command[50];
    printf("Welcome to the Document Processing System!\n");
    display_help();

    while (1) {
        printf("Enter command: ");
        fgets(command, 50, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strcmp(command, "exit") == 0) {
            break;
        }
        else if (strcmp(command, "help") == 0) {
            display_help();
        }
        else if (strcmp(command, "set") == 0) {
            printf("Enter number of documents (1-50): ");
            int docs_num;
            scanf("%d", &docs_num);
            while (getchar() != '\n');

            if (docs_num < 1 || docs_num > MAX_DOCS) {
                printf("Invalid number of documents. Must be from 1 to 50.\n");
                continue;
            }

            docs_count = docs_num;
            for (int i = 0; i < docs_num; i++) {
                printf("Enter document %d: ", i + 1);
                fgets(documents[i], MAX_LEN, stdin);
                documents[i][strcspn(documents[i], "\n")] = '\0';

                if (strlen(documents[i]) >= MAX_LEN - 1) {
                    printf("Document too long.\n");
                    i--;
                    continue;
                }
            }
            printf("Documents set successfully. Please, enter 'preprocess' command now.\n");
            preprocessed = 0;
        }
        else if (strcmp(command, "preprocess") == 0) {
            if (docs_count == 0) {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            normalize_case_all();
            tokenize_all();
            remove_stop_words_all();
            stem_all_tokens();
            preprocessed = 1;
        }
        else if (strcmp(command, "tf") == 0) {
            if (docs_count == 0) {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            char word[MAX_TOKEN_LEN];
            printf("Enter word to compute TF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            for (int i = 0; i < docs_count; i++) {
                double tf = compute_tf(word, i + 1);
                printf("Document %d: %.4f\n", i + 1, tf);
            }
        }
        else if (strcmp(command, "idf") == 0) {
            if (docs_count == 0) {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            char word[MAX_TOKEN_LEN];
            printf("Enter word to compute IDF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            double idf = compute_idf(word);
            printf("IDF for '%s': %.4f\n", word, idf);
        }
        else if (strcmp(command, "tfidf") == 0) {
            if (docs_count == 0) {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            char word[MAX_TOKEN_LEN];
            printf("Enter word to compute TF-IDF: ");
            fgets(word, sizeof(word), stdin);
            word[strcspn(word, "\n")] = '\0';
            compute_tfidf_all(word);
        }
        else if (strcmp(command, "stat") == 0) {
            if (docs_count == 0) {
                printf("No documents set. Use 'set' command first.\n");
                continue;
            }
            if (!preprocessed) {
                printf("Documents not preprocessed yet. Use 'preprocess' command first.\n");
                continue;
            }
            display_stat();
        }
        else {
            printf("Unknown command. Type 'help' for list of commands.\n");
        }
    }
    printf("Exiting program.\n");
    return 0;
}