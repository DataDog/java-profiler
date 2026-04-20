---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-19 21:19:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 8 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 826 |
| Sample Rate | 13.77/sec |
| Health Score | 861% |
| Threads | 9 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (6 unique values: 74-93 cores)</summary>

```
1776647623 74
1776647628 74
1776647633 74
1776647638 76
1776647643 76
1776647648 76
1776647653 76
1776647658 76
1776647663 76
1776647668 76
1776647673 76
1776647678 76
1776647683 81
1776647688 81
1776647693 81
1776647698 81
1776647703 86
1776647708 86
1776647713 91
1776647718 91
```
</details>

---

