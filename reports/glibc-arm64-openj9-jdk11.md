---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-07 08:27:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 272 |
| Sample Rate | 4.53/sec |
| Health Score | 283% |
| Threads | 11 |
| Allocations | 143 |

<details>
<summary>CPU Timeline (3 unique values: 19-32 cores)</summary>

```
1786105438 19
1786105443 19
1786105448 19
1786105453 27
1786105458 27
1786105463 27
1786105468 27
1786105473 27
1786105478 27
1786105483 27
1786105488 27
1786105493 27
1786105498 27
1786105503 27
1786105508 27
1786105513 32
1786105518 32
1786105523 32
1786105528 32
1786105533 32
```
</details>

---

