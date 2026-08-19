---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-19 11:10:58 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787151505 64
1787151510 64
1787151515 64
1787151520 64
1787151525 64
1787151530 64
1787151535 64
1787151540 64
1787151545 64
1787151550 64
1787151555 64
1787151560 64
1787151565 64
1787151570 64
1787151575 64
1787151580 64
1787151585 64
1787151590 64
1787151595 64
1787151600 64
```
</details>

---

