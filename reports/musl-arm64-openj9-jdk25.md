---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 574 |
| Sample Rate | 9.57/sec |
| Health Score | 598% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 15 |
| Allocations | 69 |

<details>
<summary>CPU Timeline (2 unique values: 39-44 cores)</summary>

```
1793125817 44
1793125822 44
1793125827 44
1793125832 44
1793125837 44
1793125842 44
1793125847 44
1793125852 44
1793125857 44
1793125862 39
1793125867 39
1793125872 39
1793125877 39
1793125882 39
1793125887 39
1793125892 39
1793125897 39
1793125902 39
1793125907 39
1793125912 39
```
</details>

---

