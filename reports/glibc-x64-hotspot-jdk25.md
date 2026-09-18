---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:31:08 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 10 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 577 |
| Sample Rate | 9.62/sec |
| Health Score | 601% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (4 unique values: 76-96 cores)</summary>

```
1789716376 92
1789716381 92
1789716386 92
1789716391 92
1789716396 94
1789716401 94
1789716406 94
1789716411 94
1789716416 94
1789716421 94
1789716426 94
1789716431 94
1789716436 94
1789716441 94
1789716446 96
1789716451 96
1789716456 96
1789716461 96
1789716466 96
1789716471 96
```
</details>

---

