---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-11 10:05:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 714 |
| Sample Rate | 11.90/sec |
| Health Score | 744% |
| Threads | 9 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 882 |
| Sample Rate | 14.70/sec |
| Health Score | 919% |
| Threads | 10 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (4 unique values: 75-86 cores)</summary>

```
1778507986 75
1778507991 75
1778507996 78
1778508001 78
1778508006 78
1778508011 78
1778508016 81
1778508021 81
1778508026 81
1778508031 81
1778508036 81
1778508041 86
1778508046 86
1778508051 86
1778508056 86
1778508061 86
1778508066 86
1778508071 86
1778508076 86
1778508081 86
```
</details>

---

