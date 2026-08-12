---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 05:45:50 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 51-59 cores)</summary>

```
1786527645 51
1786527650 59
1786527655 59
1786527660 59
1786527665 59
1786527670 54
1786527675 54
1786527680 54
1786527685 54
1786527690 54
1786527695 54
1786527700 54
1786527705 54
1786527710 54
1786527715 54
1786527720 54
1786527725 54
1786527730 54
1786527735 54
1786527740 54
```
</details>

---

