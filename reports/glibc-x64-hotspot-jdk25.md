---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:28:35 EST

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 8 |
| Allocations | 84 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 10 |
| Sample Rate | 0.17/sec |
| Health Score | 11% |
| Threads | 8 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (2 unique values: 72-74 cores)</summary>

```
1795706655 72
1795706660 72
1795706665 72
1795706670 72
1795706675 72
1795706680 72
1795706685 72
1795706690 72
1795706695 72
1795706700 72
1795706705 74
1795706710 74
1795706715 72
1795706720 72
1795706725 72
1795706730 72
1795706735 72
1795706740 74
1795706745 74
1795706750 74
```
</details>

---

