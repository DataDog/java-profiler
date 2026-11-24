---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 09:14:32 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 10 |
| Allocations | 391 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 500 |
| Sample Rate | 8.33/sec |
| Health Score | 521% |
| Threads | 11 |
| Allocations | 493 |

<details>
<summary>CPU Timeline (3 unique values: 63-71 cores)</summary>

```
1795529383 63
1795529388 63
1795529393 63
1795529398 63
1795529403 63
1795529408 63
1795529413 63
1795529418 63
1795529423 63
1795529428 63
1795529433 63
1795529438 63
1795529443 63
1795529448 63
1795529453 63
1795529458 63
1795529463 63
1795529468 63
1795529473 63
1795529478 63
```
</details>

---

