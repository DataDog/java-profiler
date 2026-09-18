---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 03:41:24 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 641 |
| Sample Rate | 10.68/sec |
| Health Score | 668% |
| Threads | 11 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1789716650 79
1789716655 79
1789716660 79
1789716665 79
1789716670 79
1789716675 79
1789716680 79
1789716685 79
1789716690 79
1789716695 79
1789716700 79
1789716705 77
1789716710 77
1789716715 77
1789716720 77
1789716725 77
1789716730 77
1789716735 75
1789716740 75
1789716745 77
```
</details>

---

