---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:15:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 134 |
| Sample Rate | 2.23/sec |
| Health Score | 139% |
| Threads | 10 |
| Allocations | 85 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795108246 50
1795108251 50
1795108256 50
1795108261 50
1795108266 64
1795108271 64
1795108276 64
1795108281 64
1795108286 64
1795108291 64
1795108296 64
1795108301 64
1795108306 64
1795108311 64
1795108316 64
1795108321 64
1795108326 64
1795108331 64
1795108336 64
1795108341 64
```
</details>

---

