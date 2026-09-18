---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:52:02 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 471 |
| Sample Rate | 7.85/sec |
| Health Score | 491% |
| Threads | 10 |
| Allocations | 396 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 11 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (8 unique values: 49-85 cores)</summary>

```
1789731965 51
1789731970 51
1789731975 51
1789731980 49
1789731985 49
1789731990 50
1789731995 50
1789732000 50
1789732005 50
1789732010 52
1789732015 52
1789732020 52
1789732025 54
1789732030 54
1789732035 54
1789732040 54
1789732045 54
1789732050 54
1789732055 54
1789732060 54
```
</details>

---

