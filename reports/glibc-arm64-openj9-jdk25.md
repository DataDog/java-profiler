---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 13:28:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 7 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795112627 50
1795112632 50
1795112637 50
1795112642 50
1795112647 50
1795112652 50
1795112657 50
1795112662 50
1795112667 50
1795112672 50
1795112677 50
1795112682 50
1795112687 50
1795112692 50
1795112697 50
1795112702 50
1795112707 50
1795112712 50
1795112717 50
1795112722 50
```
</details>

---

