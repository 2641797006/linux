#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdarg.h>
#include <string.h>
#include "ccolor.h"
#include "string24k.h"
#include "cli_box.h"
#include "levens.h"

#define opt_level	'l'
#define opt_align	'a'
#define opt_string	's'
#define opt_help	'h'

#define lopt_level	0x2401
#define lopt_align	0x2402
#define lopt_string	0x2403
#define lopt_help	0x2404

#define lopt_buttom	0x240
#define lopt_left	0x241
#define lopt_right	0x242
#define lopt_angle	0x243

#define _24k_error__(name, fmt, ...)	( box_fatal_error(name, fmt, __VA_ARGS__), box_end(), exit(24-'k') )
#define _24k_error(name, fmt, ...)	_24k_error__(name, fmt, __VA_ARGS__)

void
box_fatal_error (const char *name, const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	fprintf(stderr, WHITE_S("%s: ") L_RED_S("error: "), name);
	vfprintf(stderr, fmt, ap);
	va_end(ap);
}

void
box_end() {
	fprintf(stderr, "24k box terminated.\n");
}

const char help_msg_short[] =
"24k CLI box\n"
"use --help for a list of possible options\n"
;

const char help_msg[] =
"Usage: [command] | %s [options] [[-]%%d]\n"
"           (Read data from the previous command)\n"
"   or  %s [[-]%%d] -s/--string [string]\n"
"           (Use -s/--string to set the input string)\n"
"   or  %s [[-]%%d]\n"
"           (Read a line from the keyboard)\n"
"\n"
"Options:\n"
"  -l, --level             set the number of boxes\n"
"  -a, --align             set the alignment of the string in the box such as -ac or --align=center\n"
"  -s, --string            set a string as input data\n"
"  -h, --help              display this message\n"
"  --left                  set box's left string\n"
"  --right                 set box's right string\n"
"  --angle                 set box's angle string\n"
"  --buttom                set box's buttom \"Char\"\n"
;

// first : to return ':' while missing argument
const char short_options[] = ":l:a::s:h";

const struct option long_options[] = {
	{"level", required_argument, NULL, lopt_level},
	{"align", optional_argument, NULL, lopt_align},
	{"string", required_argument, NULL, lopt_string},
	{"buttom", required_argument, NULL, lopt_buttom},
	{"left", required_argument, NULL, lopt_left},
	{"right", required_argument, NULL, lopt_right},
	{"angle", required_argument, NULL, lopt_angle},
	{"--help", no_argument, NULL, lopt_help},
	{NULL, 0, NULL, 0}
};

int get_similar(const char*);

int main(int argc, char **argv)
{
	int i, level=1, opt, long_optind, align=0, help_short=0;
	char px='-';
	const char *fname = argv[0], *arg_input=NULL, *pa="+", *pyl="| ", *pyr=" |";
	string _s, *s=&_s;
	BOX _b, *b=&_b;

	while (argc >= 2 && argv[1][0] != '-')
		if ( sscanf(argv[1], "%d", &level ) < 1 )
			_24k_error(fname, "unrecognized command line option " WHITE_S("‘%s’") ". Did you miss `-` or `--`?\n", argv[1]);
		else
			--argc, ++argv;
	while ( (opt=getopt_long(argc, argv, short_options, long_options, &long_optind)) != -1 ) {
		switch (opt) {
		case opt_level: case lopt_level:
			if (sscanf(optarg, "%d", &level) < 1)
				_24k_error(fname, "argument `%s` expected %%d\n", optarg);
			break;
		case opt_align:
			if (optarg)
				switch (optarg[0]) {
				case 'l':
					align = -1;
					break;
				case 'c':
					align = 0;
					break;
				case 'r':
					align = 1;
					break;
				default:
					_24k_error(fname, "expected 'l', 'r', or 'c' after option `%s`\n", "-a");
				}
			else
				align = 0;
			break;
		case lopt_align:
			if (optarg)
				if (strcmp(optarg, "left") == 0)
					align = -1;
				else if (strcmp(optarg, "center") == 0)
					align = 0;
				else if (strcmp(optarg, "right") == 0)
					align = 1;
				else
					_24k_error(fname, "expected 'left', 'right', or 'center' after option `%s`\n", "--align");
			break;
		case opt_string: case lopt_string:
			arg_input = optarg;
			break;
		case opt_help:
			arg_input = help_msg_short;
			level=1, align=0, px='-', pa="+", pyl="| ", pyr=" |";
			help_short=1;
			goto getopt_end;
		case lopt_help:
			printf(help_msg, fname, fname, fname);
			return 0;
			break;
		case lopt_angle:
			pa = optarg;
			break;
		case lopt_buttom:
			px = optarg[0];
			break;
		case lopt_left:
			pyl = optarg;
			break;
		case lopt_right:
			pyr = optarg;
			break;
		case ':':
			_24k_error(fname, "missing argument after " WHITE_S("‘%s’\n"), argv[optind-1]);
			break;
		case '?':
			if ( sscanf(argv[1], "%d", &level ) == 1 )
				break;
			if ( (i = get_similar(argv[optind-1])) >= 0 )
				_24k_error(fname, "unrecognized command line option " WHITE_S("‘%s’") "; did you mean `%s`?\n", argv[optind-1], long_options[i].name);
			_24k_error(fname, "unrecognized command line option " WHITE_S("‘%s’\n"), argv[optind-1]);
			break;
		}
		while (optind < argc && argv[optind][0] != '-')
			if ( sscanf(argv[optind], "%d", &level ) < 1 )
				_24k_error(fname, "unrecognized command line option " WHITE_S("‘%s’") ". Did you miss `-` or `--`?\n", argv[optind]);
			else
				++optind;
	}

getopt_end:
	string_init(s);
	box_init(b, px, pa, pyl, pyr)->set_align(b, align);

	if (arg_input)
		s->assign(s, arg_input);

	if (s->empty(s))
		if ( isatty(fileno(stdin)) ) {
			printf(">>> ");
			s->getline(s);
		} else
			s->fgetline(s, stdin, EOF);

	level = level>0 ? level : -level;
	for (i=0; i<level; ++i) {
		string_clear(b->strbuf);
		b->box(b, s);
		s->swap(s, b->strbuf);
	}

	if (help_short)
		printf("%s", L_PURPLE);
	printf("%s", string_c_str(s));
	if (help_short)
		printf("%s", ENDCC);

	return 24-'k';
}

int get_similar(const char *s)
{
	int i, len, n, similar=0x7fffffff, index=-1;
	for (i=0; i<2; ++i) {
		if ( ! s[i] )
			return -1;
		if ( s[0] == '-' )
			++s;
	}
	len = strlen(s);
	for (i=0; ; ++i) {
		if ( ! long_options[i].name )
			break;
		if ( (n = distance(s, len, long_options[i].name, strlen(long_options[i].name))) < 4 )
			if ( n < similar )
				similar = n, index = i;
	}
	return index;
}

