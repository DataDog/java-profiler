---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-16 10:15:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 367 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (3 unique values: 83-86 cores)</summary>

```
1794841852 84
1794841858 84
1794841863 86
1794841868 86
1794841873 86
1794841878 86
1794841883 86
1794841888 86
1794841893 86
1794841898 83
1794841903 83
1794841908 83
1794841913 83
1794841918 83
1794841923 83
1794841928 83
1794841933 83
1794841938 83
1794841943 83
1794841948 83
```
</details>

---

