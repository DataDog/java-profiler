---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 12:15:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 11 |
| Allocations | 187 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (2 unique values: 25-30 cores)</summary>

```
1795108231 30
1795108236 30
1795108241 30
1795108246 30
1795108251 30
1795108256 30
1795108261 30
1795108266 30
1795108271 30
1795108276 30
1795108281 30
1795108286 30
1795108291 30
1795108296 30
1795108301 30
1795108306 30
1795108311 25
1795108316 25
1795108321 25
1795108326 25
```
</details>

---

