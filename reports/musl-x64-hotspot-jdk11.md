---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:17:05 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 643 |
| Sample Rate | 10.72/sec |
| Health Score | 670% |
| Threads | 9 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 848 |
| Sample Rate | 14.13/sec |
| Health Score | 883% |
| Threads | 11 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1794604362 75
1794604367 75
1794604372 75
1794604377 77
1794604382 77
1794604387 77
1794604392 77
1794604397 77
1794604402 77
1794604407 77
1794604412 77
1794604417 77
1794604422 77
1794604427 77
1794604432 77
1794604437 77
1794604442 77
1794604447 77
1794604452 77
1794604457 77
```
</details>

---

