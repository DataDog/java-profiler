---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:35:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 11 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 30-30 cores)</summary>

```
1793280655 30
1793280660 30
1793280665 30
1793280670 30
1793280675 30
1793280680 30
1793280685 30
1793280690 30
1793280695 30
1793280700 30
1793280705 30
1793280710 30
1793280715 30
1793280720 30
1793280725 30
1793280730 30
1793280735 30
1793280740 30
1793280745 30
1793280750 30
```
</details>

---

