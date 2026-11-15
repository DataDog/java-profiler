---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-14 21:04:23 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 41-63 cores)</summary>

```
1794708028 63
1794708033 63
1794708038 63
1794708043 63
1794708048 63
1794708053 63
1794708058 63
1794708063 63
1794708068 63
1794708073 63
1794708078 63
1794708083 63
1794708088 43
1794708093 43
1794708098 43
1794708103 43
1794708108 43
1794708113 43
1794708118 41
1794708123 41
```
</details>

---

