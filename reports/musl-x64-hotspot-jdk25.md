---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-27 21:22:41 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 468 |
| Sample Rate | 7.80/sec |
| Health Score | 488% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 11 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 43-73 cores)</summary>

```
1790558262 51
1790558267 51
1790558272 51
1790558277 43
1790558282 43
1790558287 43
1790558292 43
1790558297 43
1790558302 43
1790558307 43
1790558312 43
1790558317 43
1790558322 43
1790558327 43
1790558332 43
1790558337 43
1790558342 43
1790558347 43
1790558352 43
1790558357 43
```
</details>

---

