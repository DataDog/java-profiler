---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-25 01:09:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 12 |
| Allocations | 148 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 10 |
| Allocations | 19 |

<details>
<summary>CPU Timeline (2 unique values: 13-18 cores)</summary>

```
1792904528 13
1792904533 13
1792904538 13
1792904543 13
1792904548 13
1792904553 13
1792904558 13
1792904563 13
1792904568 13
1792904573 13
1792904578 13
1792904583 13
1792904588 13
1792904593 13
1792904598 13
1792904603 13
1792904608 13
1792904613 18
1792904618 18
1792904623 18
```
</details>

---

