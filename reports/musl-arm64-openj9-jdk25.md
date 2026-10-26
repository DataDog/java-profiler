---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-25 21:29:09 EDT

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
| CPU Cores (start) | 19 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 14 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1792977879 19
1792977884 19
1792977889 19
1792977894 19
1792977899 19
1792977904 19
1792977909 19
1792977914 19
1792977919 19
1792977924 19
1792977930 19
1792977935 19
1792977940 19
1792977945 19
1792977950 19
1792977955 19
1792977960 19
1792977965 24
1792977970 24
1792977975 24
```
</details>

---

