---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-18 00:57:14 EDT

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
| CPU Cores (start) | 15 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 338 |
| Sample Rate | 5.63/sec |
| Health Score | 352% |
| Threads | 8 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 8 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 15-17 cores)</summary>

```
1787028796 15
1787028801 15
1787028806 15
1787028811 15
1787028816 15
1787028821 15
1787028826 15
1787028831 15
1787028836 17
1787028841 17
1787028846 17
1787028851 17
1787028856 17
1787028861 17
1787028866 17
1787028871 17
1787028876 17
1787028881 17
1787028886 17
1787028891 17
```
</details>

---

