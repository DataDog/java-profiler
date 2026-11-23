---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-23 06:55:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 614 |
| Sample Rate | 10.23/sec |
| Health Score | 639% |
| Threads | 11 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (3 unique values: 80-91 cores)</summary>

```
1795434629 80
1795434634 80
1795434639 80
1795434644 80
1795434649 89
1795434654 89
1795434659 89
1795434664 89
1795434669 89
1795434674 89
1795434679 89
1795434684 89
1795434689 89
1795434694 89
1795434699 89
1795434704 89
1795434709 89
1795434714 91
1795434719 91
1795434724 91
```
</details>

---

