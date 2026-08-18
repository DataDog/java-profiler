---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-18 09:21:52 EDT

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
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 230 |
| Sample Rate | 3.83/sec |
| Health Score | 239% |
| Threads | 15 |
| Allocations | 141 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1787059086 64
1787059091 64
1787059096 64
1787059101 64
1787059106 64
1787059111 64
1787059116 64
1787059121 64
1787059126 64
1787059131 64
1787059136 64
1787059141 64
1787059146 64
1787059151 64
1787059156 64
1787059161 64
1787059166 64
1787059171 64
1787059176 64
1787059181 64
```
</details>

---

