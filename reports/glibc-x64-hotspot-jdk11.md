---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-01-27 14:14:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 15.70/sec |
| Health Score | 981% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 752 |
| Sample Rate | 25.07/sec |
| Health Score | 1567% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (2 unique values: 29-32 cores)</summary>

```
1769540950 29
1769540955 29
1769540960 29
1769540965 29
1769540970 29
1769540975 29
1769540980 29
1769540985 32
1769540990 32
1769540995 32
1769541000 32
1769541005 32
1769541010 32
1769541015 32
1769541020 32
1769541025 32
1769541030 32
1769541035 32
1769541040 32
1769541045 32
```
</details>

---

