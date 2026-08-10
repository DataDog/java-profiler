---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-10 06:45:23 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 338 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 429 |

<details>
<summary>CPU Timeline (3 unique values: 32-70 cores)</summary>

```
1786358504 32
1786358509 32
1786358514 32
1786358519 32
1786358524 32
1786358529 32
1786358534 32
1786358539 32
1786358544 32
1786358549 32
1786358554 32
1786358559 32
1786358564 32
1786358569 32
1786358574 32
1786358579 32
1786358584 32
1786358589 32
1786358594 34
1786358599 34
```
</details>

---

