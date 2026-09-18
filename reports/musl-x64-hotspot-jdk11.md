---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-18 04:28:57 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 496 |
| Sample Rate | 8.27/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (2 unique values: 41-59 cores)</summary>

```
1789719884 41
1789719889 41
1789719894 41
1789719899 41
1789719904 41
1789719909 41
1789719914 41
1789719919 41
1789719924 41
1789719929 41
1789719934 41
1789719939 41
1789719944 41
1789719949 41
1789719954 41
1789719959 41
1789719964 59
1789719969 59
1789719974 59
1789719979 59
```
</details>

---

