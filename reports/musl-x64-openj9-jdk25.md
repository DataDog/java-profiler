---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:47:26 EDT

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 9 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 10 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (6 unique values: 56-96 cores)</summary>

```
1789965812 56
1789965817 76
1789965822 76
1789965827 74
1789965832 74
1789965837 74
1789965842 74
1789965847 74
1789965852 74
1789965857 84
1789965862 84
1789965867 84
1789965872 84
1789965877 84
1789965882 84
1789965887 84
1789965892 84
1789965897 84
1789965902 84
1789965907 84
```
</details>

---

