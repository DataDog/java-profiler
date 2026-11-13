---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 06:01:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 87 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 512 |
| Sample Rate | 8.53/sec |
| Health Score | 533% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 768 |
| Sample Rate | 12.80/sec |
| Health Score | 800% |
| Threads | 9 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 84-87 cores)</summary>

```
1794567315 87
1794567320 87
1794567325 87
1794567330 87
1794567335 86
1794567340 86
1794567345 86
1794567350 86
1794567355 86
1794567360 86
1794567365 84
1794567370 84
1794567375 84
1794567380 84
1794567385 84
1794567390 84
1794567395 84
1794567400 84
1794567405 84
1794567410 84
```
</details>

---

