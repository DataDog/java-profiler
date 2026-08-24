---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-24 09:28:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 11 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 181 |
| Sample Rate | 3.02/sec |
| Health Score | 189% |
| Threads | 14 |
| Allocations | 111 |

<details>
<summary>CPU Timeline (3 unique values: 12-27 cores)</summary>

```
1787577814 12
1787577819 12
1787577824 12
1787577829 12
1787577834 12
1787577839 12
1787577844 12
1787577849 12
1787577854 18
1787577859 18
1787577864 18
1787577870 18
1787577875 18
1787577880 18
1787577885 18
1787577890 18
1787577895 18
1787577900 18
1787577905 18
1787577910 18
```
</details>

---

