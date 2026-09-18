---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-18 07:49:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 323 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 673 |
| Sample Rate | 11.22/sec |
| Health Score | 701% |
| Threads | 11 |
| Allocations | 433 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1789731825 46
1789731830 46
1789731835 46
1789731840 46
1789731845 46
1789731850 46
1789731855 46
1789731860 46
1789731865 46
1789731870 48
1789731875 48
1789731880 48
1789731885 48
1789731890 48
1789731895 48
1789731900 48
1789731905 48
1789731910 48
1789731915 48
1789731920 48
```
</details>

---

