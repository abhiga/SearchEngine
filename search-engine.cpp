
#include <string.h>
#include "search-engine.h"

char * nextword(char*p);

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType):
  MiniHTTPD(port)
{
  // Create dictionary of the indicated type
	FILE *log = fopen("log.txt","a");

  // Populate dictionary and sort it if necessary
	if (dictionaryType == ArrayDictionaryType) {
		fprintf(log,"%s\n", "dictionaryType=ArrayDicitonary");
		_wordToURLList = new ArrayDictionary();
	}
	else if (dictionaryType == AVLDictionaryType) {
		fprintf(log,"%s\n", "dictionaryType=AVLDicitonary");
		_wordToURLList = new AVLDictionary();
	}
	else if (dictionaryType == BinarySearchDictionaryType) {
		fprintf(log,"%s\n", "dictionaryType=BinarySearchDicitonary");
		_wordToURLList = new BinarySearchDictionary();
	}
	else if (dictionaryType == HashDictionaryType) {
		 fprintf(log,"%s\n", "dictionaryType=HashDicitonary");
		_wordToURLList = new HashDictionary();
	}
	else {
		exit(1);
	}
	fprintf(log,"%s\n", "Initializing variables");
	int count = 0;
	int countLines = 0;
	int c;
	char *url;// = new char[400];
	char *desc;// = new char[1000];
	int index;
	char *temp = new char[1000];
	char * elem;// = new char[1000];
	fprintf(log,"%s\n", "Attempting to open Url.txt");
	FILE *fd = fopen("url.txt","r");
	if(fd == NULL) {
		printf("Could not open file %s\n", "url.txt");
			fprintf(log,"%s\n", "Could not open Url.txt");
		exit(1);
		
	}
	else {
		while ((c=fgetc(fd))!=-1) {
		if(c=='\n')
			countLines++;
		}
	}
	fclose(fd);
	int numUrls = countLines/3;
	fprintf(log,"%s\n","numUrls=");
	fprintf(log,"%d\n", numUrls);
	URLRecord **list = new URLRecord*[numUrls];
	fd = fopen("url.txt","r");
	fprintf(log,"%s\n", "Intializing URLRecords");
	for(int i = 0; i < numUrls; i++) 
		list[i] = new URLRecord();
	fprintf(log,"%s\n", "End of url.txt While Loop");
	while (fgets(temp,1000,fd)) {
		if(strcmp(temp,"\n") == 0) {
			fprintf(log,"%s\n", "temp = \n");			
		}
		else {
			elem = strtok(temp," ");
			//fprintf(log,"%d",index);
			index = atoi(elem);
			fprintf(log,"%d\n",index);			
			elem = strtok(NULL," ");
			list[index]->_url = strdup(elem);
			fprintf(log,"%s\n",list[index]->_url);
			fgets(temp,1000,fd);
			elem = strtok(temp,"\n");
			list[index]->_description = strdup(elem);
			fprintf(log,"%s\n",list[index]->_description);
		}
	} 
	fprintf(log,"%s\n", "End of url.txt While Loop");
	fclose(fd);
	fd = fopen("url.txt","r");
	fprintf(log,"%s\n", "Debug url.txt");
	FILE *f = fopen("u.txt","w");
	char*so = new char[100];
	while(fscanf(fd, "%s", so) == 1){
		fprintf(f,"%s\n",so);
		fprintf(log,"%s\n",so);
	}
	fclose(f);
	/*int l;
	int i = 0;
	while ((l = fgetc(fd))!='\n')
		temp[i++] = l;
	temp[i] = '\0';
	printf("%s",temp);
	//line ends
	/*index = 0;
	char *d;
	while (fgets(temp,1000,fd)) {
		if((d = strstr(temp, "http://"))!=NULL) 
			list[index] -> _url = strdup(d);
		else
			list[index] -> _description = strdup(temp);
		index++;
		//memset(temp,0,1000);
	}
			
		
	
	/*for (int i = 0; i < numUrls; i++) {
		printf("%s\n", list[i] -> _url);
		printf("%s\n", list[i] -> _description);
	}*/
	/*char *sim;
	FILE *so = fopen("url.txt","r");
	FILE *f = fopen("u.txt","a");
	while(fscanf(fd, "%s", so){
		sim = so;
		fprintf(f,"%s\n",so);
	}*/
			//fscanf(fd, "%s",desc);
			//fscanf(fd, "%s",next);
		/*while(fgets(temp,1000,fd)) {
			if(strncmp(temp,"\n",1)) {
				strcpy(desc,temp);
				//url = strstr(temp, "http://");
				url = strtok(strstr(temp, "http://"), "\n");
				if (url!=NULL)				
					printf("%s\n",url);
				else 
					printf("%s\n",desc);
			}

		}*/
	countLines = 0;
	fclose(fd);
	fprintf(log,"%s\n", "Attempting to open word.txt");
	fd = fopen("word.txt","r");
	if(fd == NULL) {
		printf("Could not open file %s\n", "word.txt");
		fprintf(log,"%s\n", "Couldnot open word.txt");		
		exit(1);
		
	}
	else {
		while ((c=fgetc(fd))!=-1) {
		if(c=='\n')
			countLines++;
		}
	}
	fclose(fd);
	fd = fopen("word.txt","r");
		//printf("%d\n",countLines);	
			/*if(strncmp(temp, "http://",strlen("http://"))==0){
				printf("%s\n",temp);
				printf("%s\n",desc);
				desc[0] = '\0';
				count = 0;
			}
			else {
				if(count == 0) {
					strcpy(desc, temp);
				count = 1;
				}
				else {
				strcat(desc," ");
				strcat(desc,temp);
				}
			}
		}
		char *word;
		/*while (fgets(temp, 1000, fd)) {
			//if (strcmp(temp, "\n")) {
				elem = strtok(temp, " ");
				//strcpy(word,elem);				
				word = strdup(elem);
				//elem = strtok(NULL, " \n");
				printf("%s\n", word);
				/*while (elem!=NULL) {
					index = atoi(elem);
					printf("%d\n", index);
					elem = strtok(NULL, " \n");
				}*/
			//} 
		
		/*while (fgets(temp, 1000, fd)) {
			while(fscanf(fd, "%s", temp)==1){
				printf("%s\n",temp);
			}
		}*/
		fprintf(log,"%s\n", "Debug word.txt");
		fd = fopen("word.txt","r");
		f = fopen("w.txt","w");
		while(fscanf(fd, "%s", so) == 1){
			fprintf(f,"%s\n",so);
			fprintf(log,"%s\n",so);
		}
		fclose(fd);
		fclose(f);
		fd = fopen("word.txt","r");
        char *word;
		fprintf(log,"%s\n", "Start of word.txt While Loop");
		while (fgets(temp, 1000, fd)) {
			if (strcmp(temp, "\n") == 0) {
				fprintf(log,"%s\n", "temp = \n");
			}
			else {
				elem = strtok(temp, " ");
				word = strdup(elem);
				URLRecordList *head = NULL;
				URLRecordList *prev = NULL;
				elem = strtok(NULL, " \n");
				while (elem != NULL) {
					index = atoi(elem);
					fprintf(log,"%d\n",index);
					URLRecordList *tmp = new URLRecordList();
					if (head == NULL) {
						head = tmp;
						fprintf(log,"%s\n", "head = NULL");
					}
					else {
						fprintf(log,"%s\n", "head!=NULL");
					}
					tmp -> _urlRecord = list[index];
					if (prev != NULL) {
						prev -> _next = tmp;
						fprintf(log,"%s\n", "prev != NULL");
					}
					else {
					fprintf(log,"%s\n", "prev = NULL");
					}
					prev = tmp;
					elem = strtok(NULL, " \n");
				}
			
				_wordToURLList->addRecord(word, head);
			}
		}
		fprintf(log,"%s\n", "End of word.txt While Loop");
		fclose(log);
	

}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
	FILE *log = fopen("log.txt","a");
	if (strcmp(documentRequested, "/")==0) {
    // Send initial form
    fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
    fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
    fprintf(fout, "<H2>\n");
    fprintf(fout, "<FORM ACTION=\"search\">\n");
    fprintf(fout, "Search:\n");
    fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
    fprintf(fout, "</H2>\n");
    fprintf(fout, "</FORM></CENTER>\n");
    return;
  }
	// TODO: The words to search in "documentRequested" are in the form
  // /search?word=a+b+c
  //
  // You need to separate the words before search
  // Search the words in the dictionary and find the URLs that
  // are common for al the words. Then print the URLs and descriptions
  // in HTML. Make the output look nicer.

  // Here the URLs printed are hardwired
	char *temp = strdup (documentRequested + 13);
	printf("%s\n",temp);
	char * p = temp;
	fprintf(log,"%s\n", "Creating Worl List");
	char **wordList = new char*[50];
	int index = 0;
	char *token = strtok (temp, "+");
	while (token!=NULL) {
		wordList[index] = strdup(token);
		//printf("%s\n",wordList[index]);
		fprintf(log,"%s\n", wordList[index]);		
		index++;
		token = strtok(NULL,"+");
	}
	char *result = new char[100];
	int i = 0;
	for (int i = 0; i < index; i++) {
		if(i == 0) 
			strcpy(result,wordList[i]);
		else {
			strcat(result,", ");
			strcat(result,wordList[i]);
		}
	}
	//for (int i = 0; i < j; i++
	
	
   /*const int nurls=2;

  const char * words = "data structures";

  const char * urls[] = {
    "http://www.cs.purdue.edu",
    "http://www.cs.purdue.edu/homes/cs251"
  };
  
  const char * description[] = {
    "Computer Science Department. Purdue University.",
    "CS251 Data Structures"
  };*/
  fprintf( stderr, "Search for words: \"%s\"\n", result);

  fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
  fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
  fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", result);

	/* for ( int i = 0; i < nurls; i++ ) {
    fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
    fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
  }*/
	int counter = 0;
	int count = 0;
	URLRecord **llist = new URLRecord*[1000];
	for (int i = 0; i < index; i++){
		fprintf(log,"%s\n", "Attempting to find word in word to UrlsArray");
		URLRecordList* e = (URLRecordList*) _wordToURLList->findRecord(wordList[i]);
		while (e != NULL){
			fprintf(log,"%s\n", "Flag sets to 0");
			int flag = 0;
			for (int j = 0; j < count; j++){
				if (e -> _urlRecord != llist[j]){
					fprintf(log,"%s\n", "e -> _urlRecord != llist[j]");
				}
				else{
					flag = 1;
				fprintf(log,"%s\n", "Flag sets to 1");
				}
			}
			if (flag == 0) {
				llist[count] = e -> _urlRecord;
				count++;
			}
			
			e = e -> _next;
		}
	}
	for (int i = 0; i < count; i++){
		for (int j = 0; j < index; j++) {
			URLRecordList* e = (URLRecordList*) _wordToURLList->findRecord(wordList[j]);
			int flag = 0;
			while (e != NULL) {
				if (llist[i] == e -> _urlRecord) {
					flag = 1;
				}
				else {
				fprintf(log,"%s\n", "llist[i] == e -> _urlRecord");
				}
				e = e -> _next;
			}
			if (flag != 0) {
				fprintf(log,"%s\n", "flag != 0");
			}
			else
				llist[i] = NULL;
		}
	}
	for (int i = 0; i < count; i++) {
		if (llist[i] == NULL) 
			continue;
		fprintf(fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", counter+1, llist[i]->_url, llist[i]->_url);
		fprintf(fout, "<blockquote>%s<p></blockquote>\n", llist[i]->_description);
		counter++;
	}
	fclose(log);

	// Add search form at the end
  fprintf(fout, "<HR><H2>\n");
  fprintf(fout, "<FORM ACTION=\"search\">\n");
  fprintf(fout, "Search:\n");
  fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
  fprintf(fout, "</H2>\n");
  fprintf(fout, "</FORM>\n");
}

void
printUsage()
{
  const char * usage =
    "Usage: search-engine port (array | hash | avl | bsearch)\n"
    "  It starts a search engine at this port using the\n"
    "  data structure indicated. Port has to be larger than 1024.\n";

  fprintf(stderr, "%s", usage);
}

int main(int argc, char ** argv)
{
  if (argc < 3) {
    printUsage();
    return 1;
  }

  // Get port
  int port;
  sscanf( argv[1], "%d", &port);

  // Get DictionaryType
  const char * dictType = argv[2];
  DictionaryType dictionaryType;
  if (!strcmp(dictType, "array")) {
    dictionaryType = ArrayDictionaryType;
  }
  else if (!strcmp(dictType, "hash")) {
    dictionaryType = HashDictionaryType;
  }
  else if (!strcmp(dictType, "avl")) {
    dictionaryType = AVLDictionaryType;
  }
  else if (!strcmp(dictType, "bsearch")) {
    dictionaryType = BinarySearchDictionaryType;
  }
  else {
    printUsage();
    return 0;
  }
  
  SearchEngine httpd(port, dictionaryType);
  
  httpd.run();

  return 0;
}
char * nextword(char*p) {
	char word[40];
	int i = 0;
	while (*p) {
		if (*p != '+') {
			word[i] = *p;
			i++;
		}
		else {
			if (i > 0) {
				word[i] = '\0';
				
				i = 0;	
				return word;			
			}
		}
		p++;
	}
	if (i>=1) {
		word[i]='\0';
		i = 0;
		return word;
	}
	// Return null if there are no more words
	return NULL;
}

