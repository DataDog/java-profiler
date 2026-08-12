---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 08:46:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 246 |
| Sample Rate | 4.10/sec |
| Health Score | 256% |
| Threads | 13 |
| Allocations | 105 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1786538509 48
1786538514 48
1786538519 48
1786538524 48
1786538529 48
1786538534 48
1786538539 48
1786538544 48
1786538549 48
1786538554 48
1786538559 48
1786538564 48
1786538569 48
1786538574 48
1786538579 48
1786538584 43
1786538589 43
1786538594 43
1786538599 43
1786538604 43
```
</details>

---

