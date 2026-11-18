---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 12:33:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 737 |
| Sample Rate | 12.28/sec |
| Health Score | 767% |
| Threads | 10 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 69-73 cores)</summary>

```
1795022899 69
1795022904 69
1795022909 69
1795022914 69
1795022919 69
1795022924 69
1795022929 71
1795022934 71
1795022939 71
1795022944 71
1795022949 71
1795022954 71
1795022959 71
1795022964 71
1795022969 71
1795022974 71
1795022979 71
1795022984 73
1795022989 73
1795022994 71
```
</details>

---

