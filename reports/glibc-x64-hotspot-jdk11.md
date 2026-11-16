---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 10:15:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (4 unique values: 79-94 cores)</summary>

```
1794841858 91
1794841863 91
1794841868 91
1794841873 91
1794841878 91
1794841883 91
1794841888 91
1794841893 91
1794841898 91
1794841903 91
1794841908 91
1794841913 91
1794841918 94
1794841923 94
1794841928 94
1794841933 94
1794841938 94
1794841943 94
1794841948 94
1794841953 84
```
</details>

---

