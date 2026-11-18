---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

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
| CPU Cores (start) | 26 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 12 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 26-51 cores)</summary>

```
1795001529 26
1795001534 26
1795001539 26
1795001544 26
1795001549 26
1795001554 26
1795001559 26
1795001564 26
1795001569 26
1795001574 26
1795001579 26
1795001584 26
1795001589 51
1795001594 51
1795001599 51
1795001604 39
1795001609 39
1795001614 39
1795001619 39
1795001624 39
```
</details>

---

