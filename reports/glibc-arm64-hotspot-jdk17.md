---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-06 10:28:59 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 294 |
| Sample Rate | 4.90/sec |
| Health Score | 306% |
| Threads | 14 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1793978657 36
1793978662 36
1793978667 36
1793978672 36
1793978677 36
1793978682 36
1793978687 36
1793978692 36
1793978697 36
1793978702 36
1793978707 36
1793978712 36
1793978717 36
1793978722 36
1793978727 36
1793978732 36
1793978737 36
1793978742 36
1793978747 36
1793978752 36
```
</details>

---

