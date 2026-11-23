---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 11:59:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 17 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 464 |
| Sample Rate | 7.73/sec |
| Health Score | 483% |
| Threads | 8 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1795452883 17
1795452888 17
1795452893 17
1795452898 17
1795452903 17
1795452908 17
1795452913 17
1795452918 17
1795452923 17
1795452928 17
1795452933 17
1795452938 17
1795452943 17
1795452948 15
1795452953 15
1795452958 15
1795452963 15
1795452968 15
1795452973 15
1795452978 15
```
</details>

---

