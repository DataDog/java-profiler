---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-13 11:08:22 EDT

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 509 |
| Sample Rate | 8.48/sec |
| Health Score | 530% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 875 |
| Sample Rate | 14.58/sec |
| Health Score | 911% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (3 unique values: 91-96 cores)</summary>

```
1778684557 91
1778684562 91
1778684567 91
1778684572 91
1778684577 91
1778684582 91
1778684587 91
1778684592 93
1778684597 93
1778684602 93
1778684607 93
1778684612 93
1778684617 93
1778684622 93
1778684627 93
1778684632 93
1778684637 96
1778684642 96
1778684647 96
1778684652 96
```
</details>

---

