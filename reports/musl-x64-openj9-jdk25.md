---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:49:03 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 425 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 588 |
| Sample Rate | 9.80/sec |
| Health Score | 612% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (3 unique values: 43-81 cores)</summary>

```
1789731802 81
1789731807 81
1789731812 81
1789731817 81
1789731822 81
1789731827 81
1789731832 45
1789731837 45
1789731842 45
1789731847 45
1789731852 45
1789731857 45
1789731862 45
1789731867 43
1789731872 43
1789731877 43
1789731882 43
1789731887 43
1789731892 43
1789731897 45
```
</details>

---

