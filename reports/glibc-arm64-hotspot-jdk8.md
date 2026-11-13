---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-13 16:17:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 326 |
| Sample Rate | 5.43/sec |
| Health Score | 339% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794604367 40
1794604372 40
1794604377 40
1794604382 40
1794604387 40
1794604392 40
1794604397 40
1794604402 40
1794604407 40
1794604412 40
1794604417 40
1794604422 40
1794604427 40
1794604432 40
1794604437 40
1794604442 40
1794604447 40
1794604452 40
1794604457 40
1794604462 40
```
</details>

---

