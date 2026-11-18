---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-18 14:09:04 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 84 |
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
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 681 |
| Sample Rate | 11.35/sec |
| Health Score | 709% |
| Threads | 12 |
| Allocations | 478 |

<details>
<summary>CPU Timeline (2 unique values: 84-96 cores)</summary>

```
1795028647 96
1795028652 96
1795028657 96
1795028662 96
1795028667 96
1795028672 96
1795028677 96
1795028682 96
1795028687 96
1795028692 96
1795028697 96
1795028702 96
1795028707 96
1795028712 96
1795028717 96
1795028722 96
1795028727 96
1795028732 84
1795028737 84
1795028742 84
```
</details>

---

