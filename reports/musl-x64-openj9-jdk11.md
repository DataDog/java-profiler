---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-16 11:44:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 8 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 835 |
| Sample Rate | 13.92/sec |
| Health Score | 870% |
| Threads | 10 |
| Allocations | 531 |

<details>
<summary>CPU Timeline (5 unique values: 85-92 cores)</summary>

```
1794847056 92
1794847061 92
1794847066 92
1794847071 92
1794847076 92
1794847081 92
1794847086 92
1794847091 92
1794847096 92
1794847101 92
1794847106 88
1794847111 88
1794847116 88
1794847121 88
1794847126 88
1794847131 85
1794847136 85
1794847141 85
1794847146 87
1794847151 87
```
</details>

---

