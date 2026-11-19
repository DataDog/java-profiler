---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 13:27:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 504 |
| Sample Rate | 8.40/sec |
| Health Score | 525% |
| Threads | 10 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795112662 64
1795112667 64
1795112672 64
1795112677 64
1795112682 64
1795112687 64
1795112692 64
1795112697 64
1795112702 64
1795112707 64
1795112712 64
1795112717 64
1795112722 64
1795112727 64
1795112732 64
1795112737 64
1795112742 64
1795112747 64
1795112752 64
1795112757 64
```
</details>

---

