---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-19 05:17:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 365 |
| Sample Rate | 6.08/sec |
| Health Score | 380% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 14 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (5 unique values: 27-34 cores)</summary>

```
1787130730 32
1787130735 32
1787130740 32
1787130745 32
1787130750 32
1787130755 27
1787130760 27
1787130765 29
1787130770 29
1787130775 29
1787130780 29
1787130785 29
1787130790 29
1787130795 29
1787130800 29
1787130805 34
1787130810 34
1787130815 34
1787130820 34
1787130825 33
```
</details>

---

