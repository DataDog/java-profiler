---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 09:27:57 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 9 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794234155 30
1794234160 30
1794234165 30
1794234170 30
1794234175 30
1794234180 30
1794234185 30
1794234190 30
1794234195 30
1794234200 30
1794234205 32
1794234210 32
1794234215 30
1794234220 30
1794234225 30
1794234230 30
1794234235 30
1794234240 30
1794234245 30
1794234250 30
```
</details>

---

