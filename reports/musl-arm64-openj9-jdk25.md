---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-13 16:44:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 245 |
| Sample Rate | 4.08/sec |
| Health Score | 255% |
| Threads | 14 |
| Allocations | 115 |

<details>
<summary>CPU Timeline (3 unique values: 23-31 cores)</summary>

```
1786653535 23
1786653540 23
1786653545 23
1786653550 23
1786653555 24
1786653560 24
1786653565 24
1786653570 24
1786653575 24
1786653580 24
1786653585 23
1786653590 23
1786653595 23
1786653600 23
1786653605 24
1786653610 24
1786653615 23
1786653620 23
1786653625 31
1786653630 31
```
</details>

---

