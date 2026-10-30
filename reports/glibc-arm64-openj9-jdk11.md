---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-30 11:07:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 13 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793372598 48
1793372603 48
1793372608 48
1793372613 48
1793372618 48
1793372623 48
1793372628 48
1793372633 48
1793372638 48
1793372643 48
1793372648 48
1793372653 48
1793372658 48
1793372663 48
1793372668 48
1793372673 48
1793372678 48
1793372683 48
1793372688 48
1793372693 48
```
</details>

---

