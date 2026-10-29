---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-29 16:31:10 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 330 |
| Sample Rate | 5.50/sec |
| Health Score | 344% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 14-18 cores)</summary>

```
1793305614 14
1793305619 14
1793305624 14
1793305629 14
1793305634 14
1793305639 14
1793305644 14
1793305649 14
1793305654 14
1793305659 14
1793305664 14
1793305669 14
1793305674 14
1793305679 14
1793305684 14
1793305689 14
1793305694 14
1793305699 14
1793305704 16
1793305709 16
```
</details>

---

