---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 13:35:46 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 47 |
| Sample Rate | 0.78/sec |
| Health Score | 49% |
| Threads | 11 |
| Allocations | 33 |

<details>
<summary>CPU Timeline (2 unique values: 50-64 cores)</summary>

```
1795112734 50
1795112739 50
1795112744 50
1795112749 50
1795112754 50
1795112759 50
1795112764 50
1795112769 50
1795112774 50
1795112779 50
1795112784 50
1795112789 50
1795112794 50
1795112799 64
1795112804 64
1795112809 64
1795112814 64
1795112819 64
1795112824 64
1795112829 64
```
</details>

---

