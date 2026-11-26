---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-26 10:49:39 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 29 |
| Sample Rate | 0.48/sec |
| Health Score | 30% |
| Threads | 10 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 28-33 cores)</summary>

```
1795707982 33
1795707988 33
1795707993 33
1795707998 33
1795708003 33
1795708008 33
1795708013 33
1795708018 33
1795708023 33
1795708028 33
1795708033 33
1795708038 33
1795708043 33
1795708048 33
1795708053 33
1795708058 33
1795708063 33
1795708068 33
1795708073 28
1795708078 28
```
</details>

---

