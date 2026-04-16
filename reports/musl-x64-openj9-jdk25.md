---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-16 05:53:26 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1776332835 27
1776332840 27
1776332845 27
1776332850 27
1776332855 27
1776332860 27
1776332865 27
1776332870 27
1776332875 27
1776332880 27
1776332885 27
1776332890 27
1776332895 27
1776332900 27
1776332905 27
1776332910 27
1776332915 27
1776332920 27
1776332925 32
1776332930 32
```
</details>

---

