---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 10:25:39 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 111 |
| Sample Rate | 1.85/sec |
| Health Score | 116% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1795533664 32
1795533669 32
1795533674 32
1795533679 32
1795533684 32
1795533689 32
1795533694 32
1795533699 32
1795533704 32
1795533709 32
1795533714 32
1795533719 32
1795533724 32
1795533729 32
1795533734 32
1795533739 32
1795533744 32
1795533749 32
1795533754 32
1795533759 32
```
</details>

---

