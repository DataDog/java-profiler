---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-26 09:45:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 160 |
| Sample Rate | 2.67/sec |
| Health Score | 167% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 207 |
| Sample Rate | 3.45/sec |
| Health Score | 216% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 85-96 cores)</summary>

```
1787751608 85
1787751613 85
1787751618 85
1787751623 85
1787751628 85
1787751633 85
1787751638 85
1787751643 85
1787751648 85
1787751653 91
1787751658 91
1787751663 91
1787751668 91
1787751673 91
1787751678 91
1787751684 96
1787751689 96
1787751694 96
1787751699 96
1787751704 96
```
</details>

---

