---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:37:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 271 |
| Sample Rate | 4.52/sec |
| Health Score | 282% |
| Threads | 12 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (2 unique values: 30-50 cores)</summary>

```
1795196015 50
1795196020 50
1795196025 50
1795196030 50
1795196035 50
1795196040 50
1795196045 50
1795196050 50
1795196055 50
1795196060 30
1795196065 30
1795196070 30
1795196075 30
1795196080 30
1795196085 30
1795196090 30
1795196095 30
1795196100 30
1795196105 30
1795196110 30
```
</details>

---

