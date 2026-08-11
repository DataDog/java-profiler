---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-11 10:11:28 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 444 |

<details>
<summary>CPU Timeline (4 unique values: 38-63 cores)</summary>

```
1786457192 38
1786457197 38
1786457202 40
1786457207 40
1786457212 40
1786457217 38
1786457222 38
1786457227 38
1786457232 38
1786457237 40
1786457242 40
1786457247 61
1786457252 61
1786457257 61
1786457262 61
1786457267 61
1786457272 61
1786457277 61
1786457282 61
1786457287 61
```
</details>

---

