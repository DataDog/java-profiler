---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-25 00:08:20 EST

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 49 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 176 |
| Sample Rate | 2.93/sec |
| Health Score | 183% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 17-34 cores)</summary>

```
1795583045 17
1795583050 17
1795583055 17
1795583060 17
1795583065 17
1795583070 17
1795583075 17
1795583080 17
1795583085 17
1795583090 17
1795583095 17
1795583100 17
1795583105 17
1795583110 17
1795583115 17
1795583120 17
1795583125 34
1795583130 34
1795583135 34
1795583140 34
```
</details>

---

