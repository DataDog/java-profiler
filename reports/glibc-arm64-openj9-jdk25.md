---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-14 11:49:32 EDT

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
| CPU Cores (start) | 11 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (3 unique values: 11-48 cores)</summary>

```
1791992588 11
1791992593 11
1791992598 11
1791992603 11
1791992608 11
1791992613 11
1791992618 11
1791992623 11
1791992628 11
1791992633 11
1791992638 48
1791992643 48
1791992648 48
1791992653 48
1791992658 48
1791992663 48
1791992668 48
1791992673 48
1791992678 48
1791992683 48
```
</details>

---

