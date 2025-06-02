#include <stdio.h>
#include <stdlib.h>

#include <mxml.h>

int main(void) {
  const char path[] = "./test.xml";
  mxml_node_t *xml = mxmlLoadFilename(NULL, NULL, path);
  if (xml == NULL) {
    fprintf(stderr, "ERROR : cant load test file with path \"%s\"", path);
    exit(EXIT_FAILURE);
  }
  mxmlDelete(xml);
}
