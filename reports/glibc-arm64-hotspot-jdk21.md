---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-13 12:35:44 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 663 |
| Sample Rate | 11.05/sec |
| Health Score | 691% |
| Threads | 10 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1791908988 48
1791908993 43
1791908998 43
1791909003 43
1791909008 43
1791909013 43
1791909018 43
1791909023 43
1791909028 43
1791909033 43
1791909038 43
1791909043 43
1791909048 43
1791909053 43
1791909058 43
1791909063 48
1791909068 48
1791909073 48
1791909078 48
1791909084 48
```
</details>

---

