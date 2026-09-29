---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 10:08:25 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 668 |
| Sample Rate | 11.13/sec |
| Health Score | 696% |
| Threads | 9 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 24-28 cores)</summary>

```
1790690581 28
1790690586 28
1790690591 28
1790690596 28
1790690601 28
1790690606 28
1790690611 26
1790690616 26
1790690621 24
1790690626 24
1790690631 24
1790690636 24
1790690641 26
1790690646 26
1790690651 26
1790690656 26
1790690661 26
1790690666 26
1790690671 26
1790690676 24
```
</details>

---

