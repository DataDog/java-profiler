---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-09 15:36:45 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 199 |
| Sample Rate | 3.32/sec |
| Health Score | 207% |
| Threads | 9 |
| Allocations | 143 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (4 unique values: 37-45 cores)</summary>

```
1794256301 42
1794256306 42
1794256311 42
1794256316 42
1794256321 42
1794256326 37
1794256331 37
1794256336 37
1794256341 37
1794256346 37
1794256351 37
1794256356 37
1794256361 37
1794256366 37
1794256371 37
1794256376 40
1794256381 40
1794256386 40
1794256391 40
1794256396 40
```
</details>

---

