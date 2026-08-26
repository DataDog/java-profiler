---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 480 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1787751610 85
1787751615 85
1787751620 85
1787751625 85
1787751630 85
1787751635 85
1787751640 85
1787751645 85
1787751650 85
1787751655 91
1787751660 91
1787751665 91
1787751670 91
1787751675 91
1787751680 91
1787751685 96
1787751690 96
1787751695 96
1787751700 96
1787751705 96
```
</details>

---

