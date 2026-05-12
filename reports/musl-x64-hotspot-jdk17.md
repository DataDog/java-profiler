---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-05-12 06:42:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 9 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 831 |
| Sample Rate | 13.85/sec |
| Health Score | 866% |
| Threads | 11 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (5 unique values: 58-77 cores)</summary>

```
1778582213 58
1778582218 58
1778582223 58
1778582228 58
1778582233 58
1778582238 63
1778582243 63
1778582248 63
1778582253 63
1778582258 63
1778582263 63
1778582268 63
1778582273 63
1778582278 63
1778582283 63
1778582288 63
1778582293 63
1778582298 63
1778582303 63
1778582308 68
```
</details>

---

