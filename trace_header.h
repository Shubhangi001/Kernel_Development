
#if !defined(_TRACE_MSHV_SHUBHANGI_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MSHV_SHUBHANGI_H

#include <linux/tracepoint.h>

#undef TRACE_SYSTEM
#define TRACE_SYSTEM shubhangi

TRACE_EVENT(shubhangi_tracepoint,
	TP_PROTO(const char *message),
	TP_ARGS(message),
	TP_STRUCT__entry(
		__field(const char *, msg)
	),
	TP_fast_assign(
		__entry->msg = message;
	),
	TP_printk("tracepoint: %s", __entry->msg)
);

#endif /* _TRACE_SUBSYS_H */

/* This part must be outside protection */
#include <trace/define_trace.h>
