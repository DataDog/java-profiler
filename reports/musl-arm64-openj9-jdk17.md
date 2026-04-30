---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-30 14:54:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 776 |
| Sample Rate | 12.93/sec |
| Health Score | 808% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (2 unique values: 56-60 cores)</summary>

```
1777575110 56
1777575115 56
1777575120 56
1777575125 56
1777575130 56
1777575135 56
1777575140 56
1777575145 56
1777575150 56
1777575155 56
1777575160 56
1777575165 56
1777575170 56
1777575175 60
1777575180 60
1777575185 60
1777575190 60
1777575195 60
1777575200 60
1777575205 60
```
</details>

---

