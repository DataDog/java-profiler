---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 14:35:37 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 445 |
| Sample Rate | 7.42/sec |
| Health Score | 464% |
| Threads | 8 |
| Allocations | 440 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 10 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (4 unique values: 20-30 cores)</summary>

```
1793125812 20
1793125817 23
1793125822 23
1793125827 21
1793125832 21
1793125837 21
1793125842 21
1793125847 30
1793125852 30
1793125857 30
1793125862 30
1793125867 30
1793125872 30
1793125877 30
1793125882 30
1793125887 30
1793125892 30
1793125897 30
1793125902 30
1793125907 30
```
</details>

---

