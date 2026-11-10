---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 16:49:15 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 377 |
| Sample Rate | 6.28/sec |
| Health Score | 392% |
| Threads | 8 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 518 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1794347033 29
1794347038 29
1794347043 29
1794347048 29
1794347053 32
1794347058 32
1794347063 32
1794347068 32
1794347073 32
1794347078 32
1794347083 32
1794347088 32
1794347093 32
1794347098 32
1794347103 32
1794347108 32
1794347113 32
1794347118 32
1794347123 32
1794347128 32
```
</details>

---

