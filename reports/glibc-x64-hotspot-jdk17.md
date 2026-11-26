---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:28:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 94 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 94-96 cores)</summary>

```
1795706635 96
1795706640 96
1795706645 96
1795706650 96
1795706655 96
1795706660 96
1795706665 96
1795706670 96
1795706675 96
1795706680 96
1795706685 96
1795706690 96
1795706695 96
1795706700 96
1795706705 96
1795706710 96
1795706715 96
1795706720 96
1795706725 96
1795706730 94
```
</details>

---

