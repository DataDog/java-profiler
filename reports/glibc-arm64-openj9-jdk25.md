---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-30 00:57:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 23 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 10 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 23-28 cores)</summary>

```
1788065553 23
1788065558 23
1788065563 23
1788065568 23
1788065573 23
1788065578 23
1788065583 23
1788065588 23
1788065593 23
1788065598 23
1788065603 23
1788065608 23
1788065613 23
1788065618 23
1788065623 23
1788065628 23
1788065633 28
1788065638 28
1788065643 28
1788065648 28
```
</details>

---

