---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 17:00:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 262 |
| Sample Rate | 4.37/sec |
| Health Score | 273% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 18-31 cores)</summary>

```
1790110479 18
1790110484 30
1790110489 30
1790110494 30
1790110499 30
1790110504 31
1790110509 31
1790110514 31
1790110519 31
1790110524 31
1790110529 31
1790110534 31
1790110539 31
1790110544 31
1790110549 31
1790110554 31
1790110559 31
1790110564 31
1790110569 31
1790110574 31
```
</details>

---

