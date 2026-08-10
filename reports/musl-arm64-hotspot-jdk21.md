---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-10 11:38:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 459 |
| Sample Rate | 7.65/sec |
| Health Score | 478% |
| Threads | 9 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 11 |
| Allocations | 522 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1786376011 32
1786376016 32
1786376021 32
1786376026 32
1786376031 32
1786376036 32
1786376041 32
1786376046 32
1786376051 32
1786376056 32
1786376061 32
1786376066 32
1786376071 32
1786376076 34
1786376081 34
1786376086 34
1786376091 34
1786376096 34
1786376101 34
1786376106 34
```
</details>

---

