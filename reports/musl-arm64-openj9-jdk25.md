---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-19 07:26:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 9 |
| Allocations | 83 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 13 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1792408964 43
1792408969 43
1792408974 43
1792408979 43
1792408984 43
1792408989 43
1792408994 43
1792408999 48
1792409004 48
1792409009 48
1792409014 43
1792409019 43
1792409024 43
1792409029 43
1792409034 43
1792409039 43
1792409044 43
1792409049 43
1792409054 43
1792409059 43
```
</details>

---

