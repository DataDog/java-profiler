---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:59:23 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 815 |
| Sample Rate | 13.58/sec |
| Health Score | 849% |
| Threads | 9 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 54-61 cores)</summary>

```
1795452903 54
1795452908 54
1795452913 54
1795452918 54
1795452923 54
1795452928 54
1795452933 54
1795452938 54
1795452943 54
1795452948 54
1795452953 61
1795452959 61
1795452964 61
1795452969 61
1795452974 61
1795452979 61
1795452984 61
1795452989 61
1795452994 61
1795452999 61
```
</details>

---

