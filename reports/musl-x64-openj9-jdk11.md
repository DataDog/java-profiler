---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:59:20 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 8 |
| Allocations | 432 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 804 |
| Sample Rate | 13.40/sec |
| Health Score | 838% |
| Threads | 9 |
| Allocations | 581 |

<details>
<summary>CPU Timeline (4 unique values: 23-40 cores)</summary>

```
1770828856 31
1770828861 31
1770828866 31
1770828871 31
1770828876 31
1770828881 31
1770828886 31
1770828891 31
1770828896 40
1770828901 40
1770828906 40
1770828911 40
1770828916 40
1770828921 40
1770828926 40
1770828931 40
1770828936 23
1770828941 23
1770828946 23
1770828951 23
```
</details>

---

