---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-19 15:32:48 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 9 |
| Allocations | 371 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 890 |
| Sample Rate | 14.83/sec |
| Health Score | 927% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 76-84 cores)</summary>

```
1792438021 84
1792438026 84
1792438031 84
1792438036 84
1792438041 84
1792438046 84
1792438051 84
1792438056 84
1792438061 84
1792438066 84
1792438071 80
1792438076 80
1792438081 80
1792438086 80
1792438091 80
1792438096 82
1792438101 82
1792438106 82
1792438111 78
1792438116 78
```
</details>

---

