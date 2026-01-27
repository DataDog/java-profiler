---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 14:14:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 18.00/sec |
| Health Score | 1125% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 28.83/sec |
| Health Score | 1802% |
| Threads | 12 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769540950 32
1769540955 32
1769540960 32
1769540965 32
1769540970 32
1769540975 32
1769540980 32
1769540985 32
1769540990 30
1769540995 30
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

