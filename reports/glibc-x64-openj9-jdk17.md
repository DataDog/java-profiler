---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-13 05:44:28 EDT

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 414 |
| Sample Rate | 6.90/sec |
| Health Score | 431% |
| Threads | 9 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (4 unique values: 53-60 cores)</summary>

```
1773394748 57
1773394753 57
1773394758 57
1773394763 53
1773394768 53
1773394773 58
1773394778 58
1773394783 58
1773394788 58
1773394793 58
1773394798 58
1773394803 58
1773394808 58
1773394813 58
1773394818 58
1773394823 58
1773394828 58
1773394833 58
1773394838 58
1773394843 58
```
</details>

---

