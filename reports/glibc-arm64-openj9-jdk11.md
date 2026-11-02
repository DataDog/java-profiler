---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 05:13:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 12 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1793614066 40
1793614071 40
1793614076 40
1793614081 40
1793614086 40
1793614091 40
1793614096 40
1793614101 40
1793614106 40
1793614111 40
1793614116 40
1793614121 40
1793614126 40
1793614131 40
1793614136 40
1793614141 40
1793614146 40
1793614151 40
1793614156 40
1793614161 40
```
</details>

---

