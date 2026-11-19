---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:27:31 EST

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 249 |
| Sample Rate | 4.15/sec |
| Health Score | 259% |
| Threads | 14 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 20-34 cores)</summary>

```
1795112647 20
1795112652 20
1795112657 20
1795112662 20
1795112667 20
1795112672 20
1795112677 20
1795112682 20
1795112687 20
1795112692 20
1795112697 20
1795112702 20
1795112707 20
1795112712 20
1795112717 20
1795112722 20
1795112727 20
1795112732 34
1795112737 34
1795112742 34
```
</details>

---

