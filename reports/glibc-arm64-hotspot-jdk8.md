---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 13:30:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 37-43 cores)</summary>

```
1795112632 41
1795112637 41
1795112642 42
1795112647 42
1795112652 40
1795112657 40
1795112662 40
1795112667 40
1795112672 40
1795112677 39
1795112682 39
1795112687 37
1795112692 37
1795112697 37
1795112702 37
1795112707 42
1795112712 42
1795112717 42
1795112722 42
1795112727 43
```
</details>

---

