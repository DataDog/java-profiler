---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-02 13:35:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 326 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 750 |
| Sample Rate | 12.50/sec |
| Health Score | 781% |
| Threads | 10 |
| Allocations | 498 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1788369984 86
1788369989 86
1788369994 88
1788369999 88
1788370004 88
1788370009 88
1788370014 88
1788370019 88
1788370024 88
1788370029 88
1788370034 88
1788370039 88
1788370044 88
1788370049 88
1788370054 88
1788370059 88
1788370064 88
1788370069 88
1788370074 88
1788370079 88
```
</details>

---

