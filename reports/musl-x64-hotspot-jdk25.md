---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:57:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 11 |
| CPU Cores (end) | 15 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 8 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (3 unique values: 11-15 cores)</summary>

```
1789966335 11
1789966340 11
1789966345 11
1789966350 11
1789966355 11
1789966360 11
1789966365 11
1789966370 11
1789966375 11
1789966380 11
1789966385 11
1789966390 11
1789966395 13
1789966400 13
1789966405 15
1789966410 15
1789966415 15
1789966420 15
1789966425 15
1789966430 15
```
</details>

---

