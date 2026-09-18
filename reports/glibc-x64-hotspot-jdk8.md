---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 04:34:10 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 156 |
| Sample Rate | 2.60/sec |
| Health Score | 162% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 195 |
| Sample Rate | 3.25/sec |
| Health Score | 203% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1789719889 75
1789719894 75
1789719899 75
1789719904 77
1789719909 77
1789719914 77
1789719919 77
1789719924 77
1789719929 77
1789719934 77
1789719940 77
1789719945 77
1789719950 77
1789719955 75
1789719960 75
1789719965 75
1789719970 77
1789719975 77
1789719980 77
1789719985 77
```
</details>

---

