---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:25:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 13 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (2 unique values: 30-34 cores)</summary>

```
1794914458 30
1794914463 30
1794914468 30
1794914473 30
1794914478 30
1794914483 30
1794914488 30
1794914493 30
1794914498 30
1794914503 30
1794914508 30
1794914513 30
1794914518 30
1794914523 30
1794914528 30
1794914533 30
1794914538 30
1794914543 34
1794914548 34
1794914553 34
```
</details>

---

