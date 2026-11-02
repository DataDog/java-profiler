---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-02 07:03:42 EST

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
| CPU Cores (start) | 91 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (6 unique values: 82-94 cores)</summary>

```
1793620766 91
1793620771 91
1793620776 93
1793620781 93
1793620786 93
1793620791 93
1793620796 91
1793620801 91
1793620806 91
1793620811 91
1793620816 91
1793620821 91
1793620826 91
1793620831 94
1793620836 94
1793620841 86
1793620846 86
1793620851 86
1793620856 86
1793620861 86
```
</details>

---

