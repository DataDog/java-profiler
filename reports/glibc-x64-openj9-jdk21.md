---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-10 19:29:54 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 440 |
| Sample Rate | 7.33/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (2 unique values: 64-68 cores)</summary>

```
1775863614 68
1775863619 68
1775863624 68
1775863629 68
1775863634 68
1775863639 68
1775863644 68
1775863649 68
1775863654 68
1775863659 68
1775863664 68
1775863669 68
1775863674 68
1775863679 68
1775863684 68
1775863689 68
1775863694 68
1775863699 68
1775863704 68
1775863709 64
```
</details>

---

