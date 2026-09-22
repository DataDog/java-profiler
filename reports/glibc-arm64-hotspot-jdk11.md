---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-22 07:06:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 408 |
| Sample Rate | 6.80/sec |
| Health Score | 425% |
| Threads | 8 |
| Allocations | 342 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 9 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1790074851 45
1790074856 45
1790074861 45
1790074866 45
1790074871 45
1790074876 45
1790074881 45
1790074886 45
1790074891 45
1790074896 45
1790074901 45
1790074906 45
1790074911 45
1790074916 45
1790074921 45
1790074926 45
1790074931 45
1790074936 45
1790074941 48
1790074946 48
```
</details>

---

