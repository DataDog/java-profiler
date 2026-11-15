---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-14 21:04:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 572 |
| Sample Rate | 9.53/sec |
| Health Score | 596% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 73-81 cores)</summary>

```
1794707958 81
1794707963 81
1794707968 81
1794707973 81
1794707978 81
1794707983 81
1794707988 81
1794707993 81
1794707998 81
1794708003 81
1794708008 81
1794708013 81
1794708018 81
1794708023 81
1794708028 81
1794708033 81
1794708038 81
1794708043 81
1794708048 81
1794708053 73
```
</details>

---

