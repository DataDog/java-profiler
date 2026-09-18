---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-18 07:48:06 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 557 |
| Sample Rate | 9.28/sec |
| Health Score | 580% |
| Threads | 10 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (5 unique values: 29-65 cores)</summary>

```
1789731822 41
1789731827 41
1789731832 41
1789731837 41
1789731842 41
1789731847 41
1789731852 41
1789731857 41
1789731862 41
1789731867 41
1789731872 39
1789731877 39
1789731882 63
1789731887 63
1789731892 63
1789731897 63
1789731902 63
1789731907 63
1789731912 63
1789731917 65
```
</details>

---

