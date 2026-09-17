---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-17 16:32:19 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 130 |
| Sample Rate | 2.17/sec |
| Health Score | 136% |
| Threads | 12 |
| Allocations | 86 |

<details>
<summary>CPU Timeline (2 unique values: 30-64 cores)</summary>

```
1789676891 30
1789676896 30
1789676901 64
1789676906 64
1789676911 64
1789676916 64
1789676921 64
1789676927 64
1789676932 64
1789676937 64
1789676942 64
1789676947 64
1789676952 64
1789676957 64
1789676962 64
1789676967 64
1789676972 64
1789676977 64
1789676982 64
1789676987 64
```
</details>

---

