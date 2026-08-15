---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-15 05:47:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 88 |
| Sample Rate | 1.47/sec |
| Health Score | 92% |
| Threads | 8 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 260 |
| Sample Rate | 4.33/sec |
| Health Score | 271% |
| Threads | 11 |
| Allocations | 165 |

<details>
<summary>CPU Timeline (2 unique values: 30-34 cores)</summary>

```
1786786943 30
1786786948 34
1786786953 34
1786786958 34
1786786964 34
1786786969 34
1786786974 34
1786786979 34
1786786984 34
1786786989 34
1786786994 34
1786786999 34
1786787004 34
1786787009 34
1786787014 34
1786787019 34
1786787024 34
1786787029 34
1786787034 34
1786787039 34
```
</details>

---

