---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-30 00:57:20 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1788065580 24
1788065585 24
1788065590 24
1788065595 24
1788065600 24
1788065605 24
1788065610 24
1788065615 24
1788065620 24
1788065625 24
1788065630 24
1788065635 19
1788065640 19
1788065645 19
1788065650 19
1788065655 19
1788065660 19
1788065665 19
1788065670 19
1788065675 19
```
</details>

---

