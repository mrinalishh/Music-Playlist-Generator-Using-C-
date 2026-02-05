#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Song {
    char title[100];
    char artist[100];
    float duration;
    struct Song *next;
};


struct Song *head = NULL;


struct Song* createSong(char title[], char artist[], float duration) {
    struct Song *newSong = (struct Song*)malloc(sizeof(struct Song));
    strcpy(newSong->title, title);
    strcpy(newSong->artist, artist);
    newSong->duration = duration;
    newSong->next = NULL;
    return newSong;
}


void addSong(char title[], char artist[], float duration) {
    struct Song *newSong = createSong(title, artist, duration);

    if (head == NULL) {
        head = newSong;
    } else {
        struct Song *temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newSong;
    }
    printf("Song '%s' added successfully!\n", title);
}


void displayPlaylist() {
    struct Song *temp = head;
    if (temp == NULL) {
        printf("\nPlaylist is empty.\n");
        return;
    }

    printf("\n------ PLAYLIST ------\n");
    while (temp != NULL) {
        printf("Title: %s | Artist: %s | Duration: %.2f mins\n",
               temp->title, temp->artist, temp->duration);
        temp = temp->next;
    }
    printf("----------------------\n");
}


void deleteSong(char title[]) {
    struct Song *temp = head, *prev = NULL;

    if (temp != NULL && strcmp(temp->title, title) == 0) {
        head = temp->next;
        free(temp);
        printf("Song '%s' deleted successfully.\n", title);
        return;
    }

    while (temp != NULL && strcmp(temp->title, title) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Song not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Song '%s' deleted successfully.\n", title);
}


void searchSong(char title[]) {
    struct Song *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            printf("Found: %s by %s (%.2f mins)\n",
                   temp->title, temp->artist, temp->duration);
            return;
        }
        temp = temp->next;
    }
    printf("Song '%s' not found in playlist.\n", title);
}


void countSongs() {
    int count = 0;
    struct Song *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    printf(" Total songs in playlist: %d\n", count);
}

int main() {
    int choice;
    char title[100], artist[100];
    float duration;

    printf("\n==== MUSIC PLAYLIST USING LINKED LIST ====\n");
    while (1) {
        printf("\n1. Add Song\n2. Display Playlist\n3. Delete Song\n4. Search Song\n5. Count Songs\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1:
                printf("Enter Song Title: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';

                printf("Enter Artist Name: ");
                fgets(artist, 100, stdin);
                artist[strcspn(artist, "\n")] = '\0';

                printf("Enter Duration (in mins): ");
                scanf("%f", &duration);

                addSong(title, artist, duration);
                break;

            case 2:
                displayPlaylist();
                break;

            case 3:
                printf("Enter Song Title to Delete: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';
                deleteSong(title);
                break;

            case 4:
                printf("Enter Song Title to Search: ");
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';
                searchSong(title);
                break;

            case 5:
                countSongs();
                break;

            case 6:
                printf(" Exiting program...\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }
}
