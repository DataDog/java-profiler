---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-11 15:43:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 242 |
| Sample Rate | 4.03/sec |
| Health Score | 252% |
| Threads | 11 |
| Allocations | 125 |

<details>
<summary>CPU Timeline (5 unique values: 38-48 cores)</summary>

```
1791747585 48
1791747590 43
1791747595 43
1791747600 43
1791747605 43
1791747610 38
1791747615 38
1791747620 38
1791747625 38
1791747630 38
1791747635 38
1791747640 41
1791747645 41
1791747650 41
1791747655 41
1791747660 46
1791747665 46
1791747670 46
1791747675 46
1791747680 46
```
</details>

---

