---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 07:23:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 14 |
| Allocations | 154 |

<details>
<summary>CPU Timeline (4 unique values: 34-51 cores)</summary>

```
1794917954 51
1794917959 51
1794917964 51
1794917969 51
1794917974 51
1794917979 51
1794917984 51
1794917989 51
1794917994 51
1794917999 51
1794918004 51
1794918009 51
1794918014 51
1794918019 51
1794918024 51
1794918029 46
1794918034 46
1794918039 46
1794918044 46
1794918049 46
```
</details>

---

