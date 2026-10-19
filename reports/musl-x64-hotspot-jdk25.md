---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:56:47 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 9 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 669 |
| Sample Rate | 11.15/sec |
| Health Score | 697% |
| Threads | 11 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1792403439 89
1792403444 89
1792403449 89
1792403454 89
1792403459 89
1792403464 89
1792403469 89
1792403474 89
1792403479 89
1792403484 91
1792403489 91
1792403494 91
1792403499 91
1792403504 91
1792403509 91
1792403514 91
1792403519 91
1792403524 91
1792403529 96
1792403534 96
```
</details>

---

