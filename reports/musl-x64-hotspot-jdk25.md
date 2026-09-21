---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-21 00:47:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 416 |
| Sample Rate | 6.93/sec |
| Health Score | 433% |
| Threads | 9 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 456 |

<details>
<summary>CPU Timeline (2 unique values: 80-81 cores)</summary>

```
1789965822 80
1789965827 80
1789965832 80
1789965837 80
1789965842 80
1789965847 80
1789965852 80
1789965857 80
1789965862 80
1789965867 80
1789965872 80
1789965877 80
1789965882 80
1789965887 80
1789965892 81
1789965897 81
1789965902 81
1789965907 81
1789965912 81
1789965917 81
```
</details>

---

