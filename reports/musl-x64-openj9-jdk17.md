---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 11:57:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (5 unique values: 66-92 cores)</summary>

```
1794502086 68
1794502091 68
1794502096 66
1794502101 66
1794502106 66
1794502111 66
1794502116 66
1794502121 66
1794502126 66
1794502131 66
1794502136 66
1794502141 72
1794502146 72
1794502151 72
1794502156 72
1794502161 74
1794502166 74
1794502171 74
1794502176 74
1794502181 92
```
</details>

---

