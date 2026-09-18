---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 07:52:00 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 472 |
| Sample Rate | 7.87/sec |
| Health Score | 492% |
| Threads | 9 |
| Allocations | 339 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 655 |
| Sample Rate | 10.92/sec |
| Health Score | 682% |
| Threads | 11 |
| Allocations | 425 |

<details>
<summary>CPU Timeline (2 unique values: 88-96 cores)</summary>

```
1789731955 96
1789731960 96
1789731965 96
1789731970 96
1789731975 96
1789731980 96
1789731985 96
1789731990 96
1789731995 96
1789732000 88
1789732005 88
1789732010 88
1789732015 88
1789732020 88
1789732025 88
1789732030 88
1789732035 88
1789732040 88
1789732045 88
1789732050 88
```
</details>

---

