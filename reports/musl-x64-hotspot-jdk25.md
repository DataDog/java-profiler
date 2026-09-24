---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 15:41:53 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 11 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 51-88 cores)</summary>

```
1790278655 60
1790278660 60
1790278665 52
1790278670 52
1790278675 88
1790278680 88
1790278685 51
1790278690 51
1790278695 51
1790278700 51
1790278705 51
1790278710 51
1790278715 51
1790278720 51
1790278725 51
1790278730 51
1790278735 51
1790278740 51
1790278745 51
1790278750 51
```
</details>

---

