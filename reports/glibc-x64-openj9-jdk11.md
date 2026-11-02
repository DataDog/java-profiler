---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:03:39 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 8 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 732 |
| Sample Rate | 12.20/sec |
| Health Score | 762% |
| Threads | 9 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 74-78 cores)</summary>

```
1793620781 74
1793620786 74
1793620791 74
1793620796 74
1793620801 74
1793620806 74
1793620811 74
1793620816 74
1793620821 74
1793620826 76
1793620831 76
1793620836 76
1793620841 78
1793620846 78
1793620851 78
1793620856 78
1793620861 78
1793620866 78
1793620872 78
1793620877 78
```
</details>

---

