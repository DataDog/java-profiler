---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-08 06:54:10 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 9 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 993 |
| Sample Rate | 16.55/sec |
| Health Score | 1034% |
| Threads | 9 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791456623 43
1791456628 43
1791456633 43
1791456638 43
1791456643 43
1791456648 43
1791456653 43
1791456658 43
1791456663 43
1791456668 43
1791456673 43
1791456678 43
1791456683 43
1791456688 43
1791456693 48
1791456698 48
1791456703 48
1791456708 48
1791456713 48
1791456718 48
```
</details>

---

