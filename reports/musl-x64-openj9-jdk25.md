---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 16:49:17 EST

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
| CPU Cores (start) | 57 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 478 |
| Sample Rate | 7.97/sec |
| Health Score | 498% |
| Threads | 9 |
| Allocations | 422 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 553 |
| Sample Rate | 9.22/sec |
| Health Score | 576% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (2 unique values: 48-57 cores)</summary>

```
1794346990 57
1794346995 57
1794347000 57
1794347005 57
1794347010 48
1794347015 48
1794347020 48
1794347025 48
1794347030 48
1794347035 48
1794347040 48
1794347045 48
1794347050 48
1794347055 48
1794347060 48
1794347065 48
1794347070 48
1794347075 48
1794347080 48
1794347085 48
```
</details>

---

