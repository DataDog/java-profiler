---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 18:13:01 EST

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
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 9 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1006 |
| Sample Rate | 16.77/sec |
| Health Score | 1048% |
| Threads | 9 |
| Allocations | 530 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795129657 50
1795129662 50
1795129667 50
1795129672 50
1795129677 50
1795129682 50
1795129687 50
1795129692 50
1795129697 50
1795129702 50
1795129707 50
1795129712 50
1795129717 50
1795129722 50
1795129727 50
1795129732 50
1795129737 50
1795129742 50
1795129747 50
1795129752 50
```
</details>

---

