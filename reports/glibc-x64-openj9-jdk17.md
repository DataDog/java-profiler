---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-18 05:54:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 8 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792316934 30
1792316939 32
1792316944 32
1792316949 32
1792316954 32
1792316959 32
1792316964 32
1792316969 32
1792316974 32
1792316979 32
1792316984 32
1792316989 32
1792316994 32
1792316999 32
1792317004 32
1792317009 32
1792317014 32
1792317019 32
1792317024 32
1792317029 32
```
</details>

---

