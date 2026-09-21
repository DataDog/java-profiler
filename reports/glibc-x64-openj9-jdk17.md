---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 04:48:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 70 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 7.60/sec |
| Health Score | 475% |
| Threads | 9 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (5 unique values: 70-91 cores)</summary>

```
1789980085 70
1789980090 70
1789980095 70
1789980100 70
1789980105 70
1789980110 70
1789980115 70
1789980120 70
1789980125 70
1789980130 70
1789980135 83
1789980140 83
1789980145 83
1789980150 83
1789980155 83
1789980160 83
1789980165 83
1789980170 83
1789980175 83
1789980180 78
```
</details>

---

