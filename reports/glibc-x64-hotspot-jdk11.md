---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:00:52 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 534 |

<details>
<summary>CPU Timeline (3 unique values: 70-79 cores)</summary>

```
1795452898 70
1795452903 70
1795452908 70
1795452913 70
1795452918 70
1795452923 70
1795452928 70
1795452933 70
1795452938 70
1795452943 70
1795452948 70
1795452953 70
1795452958 70
1795452963 70
1795452968 70
1795452973 70
1795452978 70
1795452983 70
1795452988 70
1795452993 79
```
</details>

---

