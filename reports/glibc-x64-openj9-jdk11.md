---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:49:02 EDT

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
| CPU Cores (start) | 8 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 748 |
| Sample Rate | 12.47/sec |
| Health Score | 779% |
| Threads | 8 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 8-32 cores)</summary>

```
1789731810 8
1789731815 11
1789731820 11
1789731825 11
1789731830 11
1789731835 11
1789731840 11
1789731845 11
1789731850 11
1789731855 11
1789731860 11
1789731865 11
1789731870 11
1789731875 11
1789731880 11
1789731885 11
1789731890 11
1789731895 11
1789731900 11
1789731905 11
```
</details>

---

