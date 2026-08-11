---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-11 07:16:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1786446595 51
1786446600 51
1786446605 51
1786446610 51
1786446615 51
1786446620 51
1786446625 51
1786446630 51
1786446635 51
1786446640 51
1786446645 51
1786446650 51
1786446655 51
1786446660 51
1786446665 39
1786446670 39
1786446675 39
1786446680 39
1786446685 39
1786446690 39
```
</details>

---

