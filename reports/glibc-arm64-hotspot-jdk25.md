---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-16 08:44:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 163 |
| Sample Rate | 2.72/sec |
| Health Score | 170% |
| Threads | 10 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 48-51 cores)</summary>

```
1794836406 51
1794836411 51
1794836416 48
1794836421 48
1794836426 48
1794836431 48
1794836436 48
1794836441 48
1794836446 48
1794836451 48
1794836456 48
1794836461 48
1794836466 48
1794836471 48
1794836476 48
1794836481 48
1794836486 48
1794836491 48
1794836496 48
1794836501 48
```
</details>

---

