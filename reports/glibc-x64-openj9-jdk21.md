---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 20:34:27 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 9 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 615 |
| Sample Rate | 10.25/sec |
| Health Score | 641% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (6 unique values: 41-76 cores)</summary>

```
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
1790209895 65
1790209900 65
1790209905 65
1790209910 65
1790209916 76
```
</details>

---

