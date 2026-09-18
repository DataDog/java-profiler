---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 07:48:05 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 14 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 648 |
| Sample Rate | 10.80/sec |
| Health Score | 675% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 12 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1789731849 29
1789731854 29
1789731859 29
1789731864 34
1789731869 34
1789731874 34
1789731879 34
1789731884 34
1789731889 34
1789731894 34
1789731899 34
1789731904 34
1789731909 34
1789731914 14
1789731919 14
1789731924 14
1789731929 14
1789731934 14
1789731939 14
1789731944 14
```
</details>

---

