---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-10 10:21:06 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 70 |
| Sample Rate | 1.17/sec |
| Health Score | 73% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 6 |
| Sample Rate | 0.10/sec |
| Health Score | 6% |
| Threads | 4 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 21-26 cores)</summary>

```
1794323807 22
1794323812 22
1794323817 21
1794323822 21
1794323827 25
1794323832 25
1794323837 25
1794323842 25
1794323847 25
1794323852 25
1794323857 25
1794323862 25
1794323867 25
1794323872 25
1794323877 25
1794323882 25
1794323887 25
1794323892 25
1794323897 25
1794323902 26
```
</details>

---

