---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-19 11:31:09 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 143 |
| Sample Rate | 2.38/sec |
| Health Score | 149% |
| Threads | 8 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 256 |
| Sample Rate | 4.27/sec |
| Health Score | 267% |
| Threads | 13 |
| Allocations | 156 |

<details>
<summary>CPU Timeline (2 unique values: 44-50 cores)</summary>

```
1795105605 50
1795105610 50
1795105615 50
1795105620 50
1795105625 50
1795105630 50
1795105635 50
1795105640 50
1795105645 50
1795105650 50
1795105655 50
1795105660 50
1795105665 50
1795105670 50
1795105675 50
1795105680 50
1795105685 50
1795105690 50
1795105695 50
1795105700 50
```
</details>

---

