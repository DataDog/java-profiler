---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-23 00:55:49 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 507 |
| Sample Rate | 8.45/sec |
| Health Score | 528% |
| Threads | 9 |
| Allocations | 331 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 10 |
| Allocations | 430 |

<details>
<summary>CPU Timeline (2 unique values: 51-66 cores)</summary>

```
1787460725 51
1787460730 51
1787460735 51
1787460740 51
1787460745 51
1787460750 51
1787460755 51
1787460760 51
1787460765 51
1787460770 51
1787460775 51
1787460780 51
1787460785 51
1787460790 51
1787460795 51
1787460800 51
1787460805 51
1787460810 51
1787460815 51
1787460820 66
```
</details>

---

