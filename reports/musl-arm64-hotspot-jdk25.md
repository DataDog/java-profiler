---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:07:03 EST

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
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795111306 50
1795111311 50
1795111316 50
1795111321 50
1795111326 50
1795111331 50
1795111336 50
1795111341 50
1795111346 50
1795111351 50
1795111357 50
1795111362 50
1795111367 50
1795111372 50
1795111377 50
1795111382 50
1795111387 50
1795111392 50
1795111397 50
1795111402 50
```
</details>

---

