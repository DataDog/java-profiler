---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 06:49:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 291 |
| Sample Rate | 4.85/sec |
| Health Score | 303% |
| Threads | 11 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 51 |

<details>
<summary>CPU Timeline (4 unique values: 35-64 cores)</summary>

```
1794483841 35
1794483846 35
1794483851 35
1794483856 35
1794483861 35
1794483866 35
1794483871 35
1794483876 35
1794483881 35
1794483886 35
1794483891 35
1794483896 35
1794483901 47
1794483906 47
1794483911 52
1794483916 52
1794483921 52
1794483926 52
1794483931 52
1794483936 52
```
</details>

---

