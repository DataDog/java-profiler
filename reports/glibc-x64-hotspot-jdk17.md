---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 12:39:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 542 |
| Sample Rate | 9.03/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 11 |
| Allocations | 447 |

<details>
<summary>CPU Timeline (5 unique values: 55-61 cores)</summary>

```
1793205296 56
1793205301 56
1793205306 55
1793205311 55
1793205316 55
1793205321 55
1793205326 57
1793205331 57
1793205336 57
1793205341 57
1793205346 57
1793205351 57
1793205356 57
1793205361 59
1793205366 59
1793205371 59
1793205376 59
1793205381 59
1793205386 59
1793205391 59
```
</details>

---

