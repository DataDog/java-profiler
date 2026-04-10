---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-10 11:02:56 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (5 unique values: 28-32 cores)</summary>

```
1775833200 28
1775833205 28
1775833210 30
1775833215 30
1775833220 29
1775833225 29
1775833230 29
1775833235 29
1775833240 29
1775833245 29
1775833250 29
1775833255 29
1775833260 29
1775833265 29
1775833270 29
1775833275 29
1775833280 31
1775833285 31
1775833290 31
1775833295 31
```
</details>

---

