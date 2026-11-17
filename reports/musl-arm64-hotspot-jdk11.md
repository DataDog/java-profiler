---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-17 07:23:37 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 10 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1017 |
| Sample Rate | 16.95/sec |
| Health Score | 1059% |
| Threads | 9 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794917973 34
1794917978 34
1794917983 34
1794917988 34
1794917993 34
1794917998 34
1794918003 34
1794918008 39
1794918013 39
1794918018 39
1794918023 39
1794918028 39
1794918033 39
1794918038 39
1794918043 39
1794918048 39
1794918053 39
1794918058 39
1794918063 39
1794918068 39
```
</details>

---

