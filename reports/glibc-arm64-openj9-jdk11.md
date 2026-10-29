---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 16:31:10 EDT

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
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 8 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1022 |
| Sample Rate | 17.03/sec |
| Health Score | 1064% |
| Threads | 10 |
| Allocations | 489 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793305649 48
1793305654 48
1793305659 48
1793305664 48
1793305669 48
1793305674 48
1793305679 48
1793305684 48
1793305689 48
1793305694 48
1793305699 48
1793305704 48
1793305709 48
1793305714 48
1793305719 48
1793305724 48
1793305729 48
1793305734 48
1793305739 48
1793305744 48
```
</details>

---

