---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

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
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 30-42 cores)</summary>

```
1786454504 30
1786454509 30
1786454514 30
1786454519 30
1786454524 30
1786454529 30
1786454534 30
1786454539 30
1786454544 30
1786454549 30
1786454554 30
1786454559 30
1786454564 30
1786454569 30
1786454574 30
1786454579 30
1786454584 30
1786454589 30
1786454594 30
1786454599 30
```
</details>

---

