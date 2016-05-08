#ifndef HG_CONNECT_H
#define HG_CONNECT_H

#include "run-command.h"
#include "sha1-array.h"
#include "string-list.h"

struct hg_connection {
	struct string_list capabilities;

	void (*simple_command)(struct hg_connection *, struct strbuf *response,
			       const char *command, ...);

	int (*finish)(struct hg_connection *);

	union {
		struct {
			struct child_process proc;
			FILE *out;
		} stdio;
		struct {
			char *url;
		} http;
	};
};

extern struct hg_connection *hg_connect(const char *url, int flags);

extern int hg_finish_connect(struct hg_connection *conn);

extern void hg_get_repo_state(struct hg_connection *conn,
			      struct strbuf *branchmap, struct strbuf *heads,
			      struct strbuf *bookmarks);

extern void hg_known(struct hg_connection *conn, struct strbuf *result,
		     struct sha1_array *nodes);

extern void hg_listkeys(struct hg_connection *conn, struct strbuf *result,
			const char *namespace);

#endif
