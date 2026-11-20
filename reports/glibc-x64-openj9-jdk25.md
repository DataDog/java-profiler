---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 07:04:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 400 |
| Sample Rate | 6.67/sec |
| Health Score | 417% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (4 unique values: 66-73 cores)</summary>

```
1795175986 68
1795175991 68
1795175996 68
1795176001 68
1795176006 68
1795176011 68
1795176016 66
1795176021 66
1795176026 66
1795176031 66
1795176036 66
1795176041 66
1795176046 66
1795176051 66
1795176056 66
1795176061 66
1795176066 66
1795176071 66
1795176076 68
1795176081 68
```
</details>

---

