---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ❌ FAIL

**Date:** 2026-11-23 11:59:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 4 |
| Sample Rate | 0.07/sec |
| Health Score | 4% |
| Threads | 2 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 17-33 cores)</summary>

```
1795452908 17
1795452913 17
1795452918 17
1795452923 17
1795452928 17
1795452933 17
1795452938 17
1795452943 17
1795452948 17
1795452953 17
1795452958 17
1795452963 17
1795452968 17
1795452973 17
1795452978 17
1795452983 17
1795452988 17
1795452993 17
1795452998 17
1795453003 17
```
</details>

---

