---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-11 11:59:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 12 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 904 |
| Sample Rate | 15.07/sec |
| Health Score | 942% |
| Threads | 13 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 69-75 cores)</summary>

```
1770828919 74
1770828924 74
1770828929 74
1770828934 74
1770828939 74
1770828944 74
1770828949 72
1770828954 72
1770828959 72
1770828964 72
1770828969 72
1770828974 72
1770828979 72
1770828984 72
1770828989 72
1770828994 72
1770828999 72
1770829004 72
1770829009 72
1770829014 72
```
</details>

---

