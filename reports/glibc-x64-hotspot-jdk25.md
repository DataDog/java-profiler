---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 373 |
| Sample Rate | 6.22/sec |
| Health Score | 389% |
| Threads | 8 |
| Allocations | 420 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1793123665 32
1793123670 32
1793123675 32
1793123680 32
1793123685 32
1793123690 32
1793123695 32
1793123700 32
1793123705 32
1793123710 32
1793123715 32
1793123720 32
1793123725 32
1793123730 32
1793123735 32
1793123740 32
1793123745 32
1793123750 32
1793123755 32
1793123760 32
```
</details>

---

