# GDB script for java-profiler + wasmtime hang investigation.
#
# Usage (after the reproducer prints "JVM paused for GDB"):
#   gdb -p <pid> -x wasmtime-reproducer/debug.gdb
#
# Available commands after load:
#   threads-summary   — one-liner per thread: id, lwpid, name, first interesting frame
#   dump-workers      — full bt for every thread that is NOT the launcher/monitor
#   bt-lwp <lwpid>    — full bt for the thread matching a specific lwpid (decimal)
#
# Correlating with the Java thread dump:
#   The Java thread dump prints lines like:
#     "trap-worker-0" #23 prio=5 os_prio=0 cpu=... nid=0x1a3f ...
#   Convert nid hex to decimal and pass to bt-lwp:
#     (gdb) bt-lwp 6719

set pagination off
set print thread-events off

define threads-summary
  python
import gdb

SKIP_INNER = {
    '__futex_abstimed_wait_common64',
    '__futex_abstimed_wait_common',
    '__GI___futex_abstimed_wait_cancelable64',
    '__futex_abstimed_wait_cancelable64',
    'futex_wait',
    '__lll_lock_wait',
    'syscall',
    'park',
}

for t in gdb.inferiors()[0].threads():
    t.switch()
    try:
        f = gdb.newest_frame()
        # Walk past low-level futex/park frames to find the interesting one.
        while f and (f.name() or '') in SKIP_INNER:
            f = f.older()
        fname = (f.name() if f else None) or '?'
        print("  Thread %3d  lwpid=%-7d  name=%-22s  @ %s" % (
            t.num, t.ptid[1], repr(t.name or '?'), fname))
    except Exception as e:
        print("  Thread %3d  lwpid=%-7d  [error: %s]" % (t.num, t.ptid[1], e))
  end
end

document threads-summary
Print a one-liner per thread: GDB thread number, LWP id, OS name, first
non-syscall frame.  Correlate lwpid with the nid= field in the Java thread
dump (convert hex to decimal).
end

define dump-workers
  python
import gdb

# Frames that indicate a "management" thread we can skip.
SKIP_TOP = {'__pthread_clockjoin_ex', 'Java_java_util_concurrent_locks_LockSupport_park0'}

for t in gdb.inferiors()[0].threads():
    t.switch()
    try:
        top = gdb.newest_frame().name() or ''
        if any(s in top for s in SKIP_TOP):
            continue
        print("\n" + "=" * 70)
        print("Thread %d  lwpid=%d  name=%r" % (t.num, t.ptid[1], t.name))
        gdb.execute("bt", to_string=False)
    except Exception as e:
        print("Thread %d  [error: %s]" % (t.num, e))
  end
end

document dump-workers
Print full bt for every thread that is not the JVM launcher (pthread_join)
or the monitor (LockSupport.park).  These are the threads actually doing
wasmtime work — the hung one will be in here.
end

define bt-lwp
  python
import gdb
target_lwp = int($arg0)
for t in gdb.inferiors()[0].threads():
    if t.ptid[1] == target_lwp:
        t.switch()
        print("Switched to thread %d (lwpid=%d name=%r)" % (t.num, t.ptid[1], t.name))
        gdb.execute("bt full", to_string=False)
        break
else:
    print("No thread with lwpid=%d found." % target_lwp)
  end
end

document bt-lwp
bt-lwp <lwpid>
Full bt for the thread whose Linux LWP id matches <lwpid> (decimal).
Get the lwpid from the Java thread dump nid= field (convert hex -> decimal).
end

echo \n
echo debug.gdb loaded. Commands: threads-summary  dump-workers  bt-lwp <lwpid>\n
echo \n
echo Quick start:\n
echo   (gdb) threads-summary          <- find the hung thread's lwpid\n
echo   (gdb) dump-workers             <- full bt of all worker threads\n
echo   (gdb) bt-lwp 6719              <- bt of specific thread by lwpid\n
echo \n
