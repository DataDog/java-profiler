---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 05:45:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 238 |
| Sample Rate | 3.97/sec |
| Health Score | 248% |
| Threads | 11 |
| Allocations | 141 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 19 |
| Sample Rate | 0.32/sec |
| Health Score | 20% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 46-64 cores)</summary>

```
1794480096 51
1794480101 46
1794480106 46
1794480111 46
1794480116 46
1794480121 46
1794480126 46
1794480131 46
1794480136 46
1794480142 46
1794480147 46
1794480152 59
1794480157 59
1794480162 59
1794480167 64
1794480172 64
1794480177 64
1794480182 64
1794480187 51
1794480192 51
```
</details>

---

