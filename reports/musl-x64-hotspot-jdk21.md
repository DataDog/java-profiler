---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-17 07:23:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 721 |
| Sample Rate | 12.02/sec |
| Health Score | 751% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (2 unique values: 71-73 cores)</summary>

```
1794917949 71
1794917954 71
1794917959 71
1794917964 71
1794917969 71
1794917974 71
1794917979 71
1794917984 71
1794917989 73
1794917994 73
1794917999 73
1794918004 73
1794918009 73
1794918014 73
1794918019 73
1794918024 73
1794918029 73
1794918034 73
1794918039 73
1794918044 73
```
</details>

---

