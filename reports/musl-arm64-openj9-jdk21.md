---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-27 14:35:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
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
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 268 |
| Sample Rate | 4.47/sec |
| Health Score | 279% |
| Threads | 16 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793125827 48
1793125832 48
1793125837 48
1793125842 48
1793125847 48
1793125852 48
1793125857 48
1793125862 48
1793125867 48
1793125872 48
1793125877 48
1793125882 48
1793125887 48
1793125892 48
1793125897 48
1793125902 48
1793125907 48
1793125912 48
1793125917 48
1793125922 48
```
</details>

---

