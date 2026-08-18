---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 11:02:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 923 |
| Sample Rate | 15.38/sec |
| Health Score | 961% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787065029 64
1787065035 64
1787065040 64
1787065045 64
1787065050 64
1787065055 64
1787065060 64
1787065065 64
1787065070 64
1787065075 64
1787065080 64
1787065085 64
1787065090 64
1787065095 64
1787065100 64
1787065105 64
1787065110 64
1787065115 64
1787065120 64
1787065125 64
```
</details>

---

