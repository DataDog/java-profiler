---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:44:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 13 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1794843610 64
1794843615 64
1794843620 64
1794843625 64
1794843630 64
1794843635 64
1794843640 64
1794843645 51
1794843650 51
1794843655 51
1794843661 51
1794843666 51
1794843671 51
1794843676 51
1794843681 51
1794843686 51
1794843691 51
1794843696 51
1794843701 51
1794843706 51
```
</details>

---

