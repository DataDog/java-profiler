---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-21 05:47:03 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1795257744 13
1795257749 13
1795257754 13
1795257759 13
1795257764 13
1795257769 18
1795257774 18
1795257779 18
1795257784 18
1795257789 18
1795257794 18
1795257799 18
1795257804 18
1795257809 18
1795257814 18
1795257819 18
1795257824 18
1795257829 18
1795257834 18
1795257839 18
```
</details>

---

