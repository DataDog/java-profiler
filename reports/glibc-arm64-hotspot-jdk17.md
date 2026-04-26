---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-04-26 16:34:18 EDT

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
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 520 |
| Sample Rate | 8.67/sec |
| Health Score | 542% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1777235408 43
1777235413 43
1777235418 43
1777235423 43
1777235428 43
1777235433 43
1777235438 43
1777235443 43
1777235448 43
1777235453 43
1777235458 43
1777235463 43
1777235468 43
1777235473 43
1777235478 38
1777235483 38
1777235488 38
1777235493 38
1777235498 38
1777235503 38
```
</details>

---

