---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-02 09:51:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 13 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 22-35 cores)</summary>

```
1793630836 22
1793630841 22
1793630846 22
1793630851 22
1793630856 22
1793630861 22
1793630866 22
1793630871 22
1793630876 35
1793630881 35
1793630886 35
1793630891 35
1793630896 35
1793630901 35
1793630906 35
1793630911 35
1793630916 35
1793630921 35
1793630926 24
1793630931 24
```
</details>

---

