---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:32:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 13 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 461 |
| Sample Rate | 7.68/sec |
| Health Score | 480% |
| Threads | 8 |
| Allocations | 372 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 630 |
| Sample Rate | 10.50/sec |
| Health Score | 656% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 13-32 cores)</summary>

```
1794914877 13
1794914882 13
1794914887 13
1794914892 13
1794914897 13
1794914903 13
1794914908 32
1794914913 32
1794914918 32
1794914923 32
1794914928 32
1794914933 32
1794914938 30
1794914943 30
1794914948 30
1794914953 30
1794914958 30
1794914963 30
1794914968 30
1794914973 30
```
</details>

---

