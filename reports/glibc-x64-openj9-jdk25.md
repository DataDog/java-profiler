---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-09 21:22:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 406 |
| Sample Rate | 6.77/sec |
| Health Score | 423% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (4 unique values: 89-96 cores)</summary>

```
1786324649 89
1786324654 89
1786324659 91
1786324664 91
1786324669 91
1786324674 91
1786324679 91
1786324684 91
1786324689 91
1786324694 96
1786324699 96
1786324704 96
1786324709 96
1786324714 96
1786324719 96
1786324724 96
1786324729 96
1786324734 96
1786324739 96
1786324744 94
```
</details>

---

