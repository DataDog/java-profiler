---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:49:09 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 355 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 55-74 cores)</summary>

```
1794483825 55
1794483830 55
1794483835 55
1794483840 55
1794483845 55
1794483850 55
1794483855 74
1794483860 74
1794483865 74
1794483870 74
1794483875 74
1794483880 74
1794483886 74
1794483891 74
1794483896 74
1794483901 74
1794483906 74
1794483911 74
1794483916 74
1794483921 74
```
</details>

---

