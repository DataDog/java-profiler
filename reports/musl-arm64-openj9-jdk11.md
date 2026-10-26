---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-26 08:57:45 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 678 |
| Sample Rate | 11.30/sec |
| Health Score | 706% |
| Threads | 8 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 227 |
| Sample Rate | 3.78/sec |
| Health Score | 236% |
| Threads | 11 |
| Allocations | 74 |

<details>
<summary>CPU Timeline (2 unique values: 12-24 cores)</summary>

```
1793019080 24
1793019085 24
1793019090 24
1793019095 24
1793019100 24
1793019105 24
1793019110 24
1793019115 24
1793019120 24
1793019125 24
1793019130 24
1793019135 24
1793019140 24
1793019145 24
1793019150 24
1793019155 24
1793019160 12
1793019165 12
1793019170 12
1793019175 12
```
</details>

---

