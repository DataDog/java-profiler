---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 20:17:01 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 9 |
| Allocations | 332 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 431 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1786579991 52
1786579996 52
1786580001 52
1786580006 52
1786580011 52
1786580016 52
1786580021 52
1786580026 52
1786580031 52
1786580036 52
1786580041 54
1786580046 54
1786580051 54
1786580056 54
1786580061 54
1786580066 54
1786580071 54
1786580076 54
1786580081 54
1786580086 54
```
</details>

---

