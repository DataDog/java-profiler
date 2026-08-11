---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 09:28:00 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 849 |
| Sample Rate | 14.15/sec |
| Health Score | 884% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (4 unique values: 65-93 cores)</summary>

```
1786454489 91
1786454494 91
1786454499 91
1786454504 91
1786454509 91
1786454514 91
1786454519 91
1786454524 91
1786454529 93
1786454534 93
1786454539 93
1786454544 65
1786454549 65
1786454554 65
1786454559 65
1786454564 65
1786454569 65
1786454574 65
1786454579 65
1786454584 65
```
</details>

---

