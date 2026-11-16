---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-16 09:19:43 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 359 |
| Sample Rate | 5.98/sec |
| Health Score | 374% |
| Threads | 14 |
| Allocations | 164 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1794838437 51
1794838442 51
1794838447 46
1794838452 46
1794838457 46
1794838462 46
1794838467 46
1794838472 46
1794838477 46
1794838482 46
1794838487 46
1794838492 46
1794838497 46
1794838502 46
1794838507 46
1794838512 46
1794838517 46
1794838522 46
1794838527 46
1794838532 46
```
</details>

---

