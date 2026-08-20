---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-20 10:05:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 733 |
| Sample Rate | 12.22/sec |
| Health Score | 764% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (3 unique values: 64-76 cores)</summary>

```
1787234368 64
1787234373 64
1787234378 64
1787234383 64
1787234388 64
1787234393 64
1787234398 64
1787234403 64
1787234408 66
1787234413 66
1787234418 66
1787234423 66
1787234428 66
1787234433 66
1787234438 66
1787234443 66
1787234448 66
1787234453 66
1787234458 66
1787234463 66
```
</details>

---

