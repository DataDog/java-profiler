---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:49:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 86 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 605 |
| Sample Rate | 10.08/sec |
| Health Score | 630% |
| Threads | 9 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 10 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (2 unique values: 86-88 cores)</summary>

```
1794483846 86
1794483851 86
1794483856 86
1794483861 86
1794483866 86
1794483871 86
1794483876 86
1794483881 86
1794483886 86
1794483891 86
1794483896 86
1794483901 86
1794483906 86
1794483911 86
1794483916 86
1794483921 88
1794483926 88
1794483931 88
1794483936 88
1794483941 88
```
</details>

---

