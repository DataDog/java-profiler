---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-18 09:26:46 EDT

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 489 |
| Sample Rate | 8.15/sec |
| Health Score | 509% |
| Threads | 8 |
| Allocations | 347 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 422 |

<details>
<summary>CPU Timeline (3 unique values: 14-32 cores)</summary>

```
1789737651 16
1789737656 16
1789737661 14
1789737666 14
1789737671 14
1789737676 14
1789737681 14
1789737686 14
1789737691 14
1789737696 14
1789737701 16
1789737706 16
1789737711 16
1789737716 16
1789737721 16
1789737726 16
1789737731 16
1789737736 16
1789737741 16
1789737746 16
```
</details>

---

