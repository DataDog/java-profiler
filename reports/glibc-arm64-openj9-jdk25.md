---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-13 12:35:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 744 |
| Sample Rate | 12.40/sec |
| Health Score | 775% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 49-54 cores)</summary>

```
1791909050 54
1791909055 54
1791909060 54
1791909065 54
1791909070 54
1791909075 54
1791909080 54
1791909085 54
1791909090 54
1791909095 54
1791909100 54
1791909105 54
1791909110 54
1791909115 54
1791909120 54
1791909125 49
1791909130 49
1791909135 49
1791909140 49
1791909145 49
```
</details>

---

