---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-05-11 18:22:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 314 |
| Sample Rate | 5.23/sec |
| Health Score | 327% |
| Threads | 10 |
| Allocations | 138 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 10 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (3 unique values: 47-57 cores)</summary>

```
1778537930 47
1778537935 52
1778537940 52
1778537945 52
1778537950 57
1778537955 57
1778537960 57
1778537965 57
1778537970 57
1778537975 57
1778537980 57
1778537985 57
1778537990 57
1778537995 57
1778538000 57
1778538005 57
1778538010 57
1778538015 57
1778538020 57
1778538025 57
```
</details>

---

