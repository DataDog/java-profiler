---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 09:06:34 EDT

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
| CPU Cores (start) | 7 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 7 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 324 |
| Sample Rate | 5.40/sec |
| Health Score | 338% |
| Threads | 10 |
| Allocations | 131 |

<details>
<summary>CPU Timeline (3 unique values: 7-44 cores)</summary>

```
1790168557 7
1790168562 7
1790168567 7
1790168572 7
1790168577 7
1790168582 7
1790168587 7
1790168592 7
1790168597 44
1790168602 44
1790168607 44
1790168612 44
1790168617 44
1790168622 44
1790168627 44
1790168632 44
1790168637 44
1790168642 44
1790168647 44
1790168652 44
```
</details>

---

