---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 09:29:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 11 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795098296 45
1795098301 45
1795098306 45
1795098311 45
1795098316 45
1795098321 45
1795098326 45
1795098331 45
1795098336 45
1795098341 45
1795098346 45
1795098351 45
1795098356 45
1795098361 45
1795098366 45
1795098372 45
1795098377 45
1795098382 45
1795098387 59
1795098392 59
```
</details>

---

