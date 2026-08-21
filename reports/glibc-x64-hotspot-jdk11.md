---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-21 18:25:03 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 590 |
| Sample Rate | 9.83/sec |
| Health Score | 614% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 699 |
| Sample Rate | 11.65/sec |
| Health Score | 728% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (4 unique values: 30-79 cores)</summary>

```
1787350895 32
1787350900 32
1787350905 32
1787350910 32
1787350915 30
1787350920 30
1787350925 30
1787350930 30
1787350935 30
1787350940 30
1787350945 30
1787350950 30
1787350955 30
1787350960 30
1787350965 30
1787350970 30
1787350975 30
1787350980 30
1787350985 30
1787350990 30
```
</details>

---

