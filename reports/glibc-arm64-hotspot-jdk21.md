---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-28 00:04:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 7 |
| Allocations | 4 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795842047 64
1795842052 64
1795842057 64
1795842062 64
1795842067 64
1795842072 64
1795842077 64
1795842082 64
1795842087 64
1795842092 64
1795842097 64
1795842102 64
1795842107 64
1795842112 64
1795842117 64
1795842122 64
1795842127 64
1795842132 64
1795842137 64
1795842142 64
```
</details>

---

