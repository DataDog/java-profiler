---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 01:04:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 6 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 9 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 59 |

<details>
<summary>CPU Timeline (1 unique values: 6-6 cores)</summary>

```
1793249959 6
1793249964 6
1793249969 6
1793249974 6
1793249979 6
1793249984 6
1793249989 6
1793249994 6
1793249999 6
1793250004 6
1793250009 6
1793250014 6
1793250019 6
1793250024 6
1793250029 6
1793250034 6
1793250039 6
1793250044 6
1793250049 6
1793250054 6
```
</details>

---

