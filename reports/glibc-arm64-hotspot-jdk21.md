---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 11:01:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 287 |
| Sample Rate | 4.78/sec |
| Health Score | 299% |
| Threads | 11 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1794585456 39
1794585461 51
1794585466 51
1794585471 51
1794585476 51
1794585481 51
1794585486 51
1794585491 51
1794585496 39
1794585501 39
1794585506 39
1794585511 39
1794585517 39
1794585522 39
1794585527 39
1794585532 39
1794585537 39
1794585542 39
1794585547 39
1794585552 39
```
</details>

---

