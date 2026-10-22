---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 04:49:17 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 136 |
| Sample Rate | 2.27/sec |
| Health Score | 142% |
| Threads | 7 |
| Allocations | 91 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 12 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792658558 43
1792658563 43
1792658568 43
1792658573 43
1792658578 43
1792658583 43
1792658588 43
1792658593 43
1792658598 43
1792658603 43
1792658608 43
1792658613 43
1792658618 43
1792658623 48
1792658628 48
1792658633 48
1792658638 48
1792658643 48
1792658648 48
1792658653 48
```
</details>

---

