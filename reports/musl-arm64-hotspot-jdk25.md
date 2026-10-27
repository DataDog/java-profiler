---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793125822 48
1793125827 48
1793125832 48
1793125837 43
1793125842 43
1793125847 43
1793125852 43
1793125857 43
1793125862 43
1793125867 43
1793125872 43
1793125877 43
1793125882 43
1793125887 43
1793125892 43
1793125897 43
1793125902 48
1793125907 48
1793125912 48
1793125917 48
```
</details>

---

