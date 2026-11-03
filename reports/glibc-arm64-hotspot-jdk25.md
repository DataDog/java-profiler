---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-03 07:41:14 EST

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
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 14 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (5 unique values: 39-59 cores)</summary>

```
1793709484 51
1793709489 51
1793709494 51
1793709499 51
1793709504 51
1793709509 51
1793709514 51
1793709519 51
1793709524 51
1793709529 51
1793709534 46
1793709539 46
1793709544 59
1793709549 59
1793709554 59
1793709559 59
1793709564 39
1793709569 39
1793709574 39
1793709579 39
```
</details>

---

