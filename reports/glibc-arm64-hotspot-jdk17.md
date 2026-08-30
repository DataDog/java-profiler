---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-30 00:57:20 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 276 |
| Sample Rate | 4.60/sec |
| Health Score | 287% |
| Threads | 9 |
| Allocations | 110 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1788065570 43
1788065575 43
1788065580 43
1788065585 43
1788065590 43
1788065595 43
1788065600 43
1788065605 43
1788065610 43
1788065615 43
1788065620 43
1788065625 43
1788065630 43
1788065635 43
1788065640 43
1788065645 43
1788065650 43
1788065655 48
1788065660 48
1788065665 48
```
</details>

---

