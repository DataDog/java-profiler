---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 12:31:52 EDT

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 598 |
| Sample Rate | 9.97/sec |
| Health Score | 623% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 15 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787243246 48
1787243251 48
1787243256 48
1787243261 48
1787243266 48
1787243271 48
1787243276 48
1787243281 48
1787243286 48
1787243291 48
1787243296 48
1787243301 48
1787243306 43
1787243311 43
1787243316 43
1787243321 43
1787243326 43
1787243331 43
1787243336 43
1787243341 43
```
</details>

---

