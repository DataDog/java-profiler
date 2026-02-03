---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-03 11:54:11 EST

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
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 901 |
| Sample Rate | 15.02/sec |
| Health Score | 939% |
| Threads | 9 |
| Allocations | 560 |

<details>
<summary>CPU Timeline (2 unique values: 65-67 cores)</summary>

```
1770137304 65
1770137309 65
1770137314 65
1770137319 65
1770137324 65
1770137329 67
1770137334 67
1770137339 67
1770137344 67
1770137349 67
1770137354 67
1770137359 67
1770137364 67
1770137369 67
1770137374 67
1770137379 67
1770137384 67
1770137389 67
1770137394 67
1770137399 67
```
</details>

---

