---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:28:13 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 138 |
| Sample Rate | 2.30/sec |
| Health Score | 144% |
| Threads | 8 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1794842588 39
1794842593 39
1794842598 39
1794842603 44
1794842608 44
1794842613 39
1794842618 39
1794842623 39
1794842628 39
1794842633 39
1794842638 39
1794842643 39
1794842648 39
1794842653 39
1794842658 39
1794842663 39
1794842668 39
1794842673 39
1794842678 39
1794842683 44
```
</details>

---

