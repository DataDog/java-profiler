---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 09:13:29 EST

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
| CPU Cores (start) | 59 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 320 |
| Sample Rate | 5.33/sec |
| Health Score | 333% |
| Threads | 12 |
| Allocations | 197 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (4 unique values: 49-59 cores)</summary>

```
1795529408 59
1795529413 59
1795529418 55
1795529423 55
1795529428 49
1795529433 49
1795529438 49
1795529443 49
1795529448 49
1795529453 49
1795529458 49
1795529463 49
1795529468 49
1795529473 49
1795529478 49
1795529483 54
1795529488 54
1795529493 54
1795529498 54
1795529503 54
```
</details>

---

