---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:38:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 11 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1794479600 38
1794479605 51
1794479610 51
1794479615 51
1794479620 51
1794479625 51
1794479630 51
1794479635 51
1794479640 51
1794479645 51
1794479650 51
1794479655 51
1794479660 51
1794479665 51
1794479670 51
1794479675 51
1794479680 51
1794479685 51
1794479690 51
1794479695 51
```
</details>

---

