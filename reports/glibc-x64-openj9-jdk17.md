---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-04-23 14:32:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 482 |
| Sample Rate | 8.03/sec |
| Health Score | 502% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 72-96 cores)</summary>

```
1776968738 96
1776968743 96
1776968748 96
1776968753 96
1776968758 96
1776968763 96
1776968768 96
1776968773 96
1776968778 96
1776968783 96
1776968788 96
1776968793 96
1776968798 96
1776968803 96
1776968808 96
1776968813 96
1776968818 96
1776968823 96
1776968828 96
1776968833 72
```
</details>

---

