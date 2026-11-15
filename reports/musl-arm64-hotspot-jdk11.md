---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-15 11:58:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 702 |
| Sample Rate | 11.70/sec |
| Health Score | 731% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 398 |
| Sample Rate | 6.63/sec |
| Health Score | 414% |
| Threads | 11 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1794761666 29
1794761671 29
1794761676 29
1794761681 29
1794761686 29
1794761691 29
1794761696 34
1794761701 34
1794761706 34
1794761711 34
1794761716 34
1794761721 34
1794761726 34
1794761731 34
1794761736 34
1794761741 34
1794761746 34
1794761751 34
1794761756 34
1794761761 34
```
</details>

---

