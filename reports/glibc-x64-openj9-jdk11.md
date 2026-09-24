---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 20:34:27 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 488 |
| Sample Rate | 8.13/sec |
| Health Score | 508% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 777 |
| Sample Rate | 12.95/sec |
| Health Score | 809% |
| Threads | 8 |
| Allocations | 495 |

<details>
<summary>CPU Timeline (5 unique values: 41-76 cores)</summary>

```
1790209795 43
1790209800 43
1790209805 43
1790209810 43
1790209815 43
1790209820 43
1790209825 43
1790209830 43
1790209835 43
1790209840 43
1790209845 43
1790209850 43
1790209855 43
1790209860 43
1790209865 43
1790209870 43
1790209875 41
1790209880 41
1790209885 73
1790209890 73
```
</details>

---

