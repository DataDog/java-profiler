---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 05:16:16 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 519 |

<details>
<summary>CPU Timeline (3 unique values: 44-84 cores)</summary>

```
1792141898 44
1792141903 44
1792141908 44
1792141913 44
1792141918 44
1792141923 44
1792141928 44
1792141933 64
1792141938 64
1792141943 64
1792141948 64
1792141953 64
1792141958 64
1792141963 64
1792141968 64
1792141973 64
1792141978 64
1792141983 64
1792141988 64
1792141993 64
```
</details>

---

