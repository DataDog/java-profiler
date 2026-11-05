---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 00:07:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (5 unique values: 30-96 cores)</summary>

```
1793855051 30
1793855056 30
1793855061 30
1793855066 63
1793855071 63
1793855076 46
1793855081 46
1793855086 79
1793855091 79
1793855096 79
1793855101 79
1793855106 96
1793855111 96
1793855116 96
1793855121 96
1793855126 96
1793855131 96
1793855136 96
1793855141 96
1793855146 96
```
</details>

---

