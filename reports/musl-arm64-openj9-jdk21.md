---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:59:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 54 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 859 |
| Sample Rate | 14.32/sec |
| Health Score | 895% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (2 unique values: 54-59 cores)</summary>

```
1795452893 54
1795452898 54
1795452903 59
1795452908 59
1795452913 59
1795452918 59
1795452923 59
1795452928 59
1795452933 59
1795452938 59
1795452943 59
1795452948 59
1795452953 59
1795452958 59
1795452963 59
1795452968 59
1795452973 59
1795452978 59
1795452983 59
1795452988 59
```
</details>

---

