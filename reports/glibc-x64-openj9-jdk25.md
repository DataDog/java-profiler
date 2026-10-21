---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 16:58:42 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 397 |
| Sample Rate | 6.62/sec |
| Health Score | 414% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 89-91 cores)</summary>

```
1792615959 91
1792615964 91
1792615969 91
1792615974 91
1792615979 91
1792615984 91
1792615989 91
1792615994 91
1792615999 91
1792616004 91
1792616009 91
1792616014 91
1792616019 91
1792616024 91
1792616029 91
1792616034 91
1792616039 91
1792616044 91
1792616049 89
1792616054 89
```
</details>

---

