---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 18:22:08 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 200 |
| Sample Rate | 3.33/sec |
| Health Score | 208% |
| Threads | 9 |
| Allocations | 93 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1778537949 64
1778537954 64
1778537959 64
1778537964 64
1778537969 64
1778537974 64
1778537980 64
1778537985 64
1778537990 64
1778537995 64
1778538000 64
1778538005 64
1778538010 64
1778538015 64
1778538020 64
1778538025 64
1778538030 64
1778538035 64
1778538040 64
1778538045 64
```
</details>

---

