---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 16:37:01 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 369 |
| Sample Rate | 6.15/sec |
| Health Score | 384% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 9-29 cores)</summary>

```
1792614713 27
1792614718 27
1792614723 27
1792614728 27
1792614733 29
1792614738 29
1792614743 9
1792614748 9
1792614753 9
1792614758 9
1792614763 9
1792614768 9
1792614773 9
1792614778 9
1792614783 9
1792614788 9
1792614793 9
1792614798 9
1792614803 9
1792614808 9
```
</details>

---

