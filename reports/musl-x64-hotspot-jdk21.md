---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:37:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 9 |
| Allocations | 417 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 695 |
| Sample Rate | 11.58/sec |
| Health Score | 724% |
| Threads | 10 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 62-90 cores)</summary>

```
1795613511 68
1795613516 68
1795613521 65
1795613526 65
1795613531 65
1795613536 65
1795613541 62
1795613546 62
1795613551 62
1795613556 62
1795613561 62
1795613566 62
1795613571 62
1795613576 62
1795613581 62
1795613586 62
1795613591 62
1795613596 90
1795613601 90
1795613606 90
```
</details>

---

