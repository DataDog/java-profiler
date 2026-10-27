---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-27 16:51:57 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (1 unique values: 31-31 cores)</summary>

```
1793133976 31
1793133981 31
1793133986 31
1793133991 31
1793133996 31
1793134001 31
1793134006 31
1793134011 31
1793134016 31
1793134021 31
1793134026 31
1793134031 31
1793134036 31
1793134041 31
1793134046 31
1793134051 31
1793134056 31
1793134061 31
1793134066 31
1793134071 31
```
</details>

---

