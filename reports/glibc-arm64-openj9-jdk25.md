---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-30 10:12:28 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 13 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777558039 64
1777558044 64
1777558049 64
1777558054 64
1777558059 64
1777558064 64
1777558069 64
1777558074 64
1777558079 64
1777558084 64
1777558089 64
1777558094 64
1777558099 64
1777558104 64
1777558109 64
1777558114 64
1777558119 64
1777558124 64
1777558129 64
1777558134 64
```
</details>

---

