---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-17 21:38:41 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1787016841 43
1787016846 43
1787016851 43
1787016856 43
1787016861 43
1787016866 43
1787016871 43
1787016876 43
1787016881 43
1787016886 43
1787016891 43
1787016896 43
1787016901 43
1787016906 38
1787016911 38
1787016916 38
1787016921 38
1787016926 38
1787016931 38
1787016936 38
```
</details>

---

