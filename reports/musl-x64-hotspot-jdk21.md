---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-17 13:52:04 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 25 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 816 |
| Sample Rate | 13.60/sec |
| Health Score | 850% |
| Threads | 9 |
| Allocations | 476 |

<details>
<summary>CPU Timeline (4 unique values: 25-30 cores)</summary>

```
1789667223 25
1789667228 27
1789667233 27
1789667238 29
1789667243 29
1789667248 30
1789667253 30
1789667258 30
1789667263 30
1789667268 30
1789667273 30
1789667278 30
1789667283 30
1789667288 30
1789667293 30
1789667298 30
1789667303 30
1789667308 30
1789667313 30
1789667318 30
```
</details>

---

