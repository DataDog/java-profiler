---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 04:49:16 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 367 |
| Sample Rate | 6.12/sec |
| Health Score | 382% |
| Threads | 14 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792658568 48
1792658573 48
1792658578 48
1792658583 48
1792658588 48
1792658593 48
1792658598 48
1792658603 48
1792658608 48
1792658613 48
1792658618 48
1792658623 48
1792658628 48
1792658633 48
1792658638 48
1792658643 48
1792658648 48
1792658653 48
1792658658 48
1792658663 48
```
</details>

---

