---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-05 08:22:41 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 191 |
| Sample Rate | 3.18/sec |
| Health Score | 199% |
| Threads | 14 |
| Allocations | 102 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777983513 64
1777983518 64
1777983523 64
1777983528 64
1777983533 64
1777983538 64
1777983543 64
1777983548 64
1777983553 64
1777983558 64
1777983563 64
1777983568 64
1777983573 64
1777983578 64
1777983583 64
1777983588 64
1777983593 64
1777983598 64
1777983603 64
1777983608 64
```
</details>

---

