---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-14 21:04:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 10 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 31-64 cores)</summary>

```
1794707973 31
1794707978 31
1794707983 31
1794707988 31
1794707993 31
1794707998 31
1794708003 31
1794708008 31
1794708013 31
1794708018 31
1794708023 31
1794708028 31
1794708033 31
1794708038 31
1794708043 31
1794708048 31
1794708053 31
1794708058 31
1794708063 31
1794708068 31
```
</details>

---

