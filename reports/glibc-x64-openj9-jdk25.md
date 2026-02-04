---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-04 07:50:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 89 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 12 |
| Allocations | 517 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1770208990 96
1770208995 96
1770209000 96
1770209005 91
1770209010 91
1770209015 91
1770209020 91
1770209025 91
1770209030 91
1770209035 91
1770209040 91
1770209045 91
1770209050 91
1770209055 91
1770209060 91
1770209065 91
1770209070 91
1770209075 91
1770209080 91
1770209085 91
```
</details>

---

