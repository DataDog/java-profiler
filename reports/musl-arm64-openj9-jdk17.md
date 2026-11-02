---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-02 13:47:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 403 |
| Sample Rate | 6.72/sec |
| Health Score | 420% |
| Threads | 9 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 172 |
| Sample Rate | 2.87/sec |
| Health Score | 179% |
| Threads | 12 |
| Allocations | 94 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1793644964 43
1793644969 43
1793644974 48
1793644979 48
1793644984 48
1793644989 48
1793644994 48
1793644999 48
1793645004 48
1793645009 48
1793645014 48
1793645019 48
1793645024 48
1793645029 48
1793645034 48
1793645039 48
1793645044 48
1793645049 48
1793645054 48
1793645059 48
```
</details>

---

