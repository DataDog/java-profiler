---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-22 16:32:53 EST

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
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 14 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 23-33 cores)</summary>

```
1795382962 33
1795382967 33
1795382972 33
1795382977 33
1795382982 28
1795382987 28
1795382992 28
1795382997 28
1795383002 28
1795383007 23
1795383012 23
1795383017 23
1795383022 23
1795383027 23
1795383032 23
1795383037 23
1795383042 23
1795383047 23
1795383052 23
1795383057 23
```
</details>

---

