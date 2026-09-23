---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-23 09:06:33 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 12 |
| Allocations | 164 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1790168583 46
1790168588 46
1790168593 46
1790168598 46
1790168603 46
1790168608 46
1790168613 48
1790168618 48
1790168623 48
1790168628 48
1790168633 48
1790168638 48
1790168643 48
1790168648 48
1790168653 48
1790168658 48
1790168663 48
1790168668 48
1790168673 48
1790168678 43
```
</details>

---

