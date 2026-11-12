---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 06:49:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 318 |
| Sample Rate | 5.30/sec |
| Health Score | 331% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 36-44 cores)</summary>

```
1794483826 44
1794483831 44
1794483836 44
1794483841 44
1794483846 44
1794483851 36
1794483856 36
1794483861 36
1794483866 36
1794483871 36
1794483876 36
1794483881 36
1794483886 36
1794483891 36
1794483896 36
1794483901 36
1794483906 36
1794483911 36
1794483916 36
1794483921 36
```
</details>

---

