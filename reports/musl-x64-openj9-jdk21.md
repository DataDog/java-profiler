---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-06 07:56:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 6 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 481 |
| Sample Rate | 8.02/sec |
| Health Score | 501% |
| Threads | 8 |
| Allocations | 358 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 519 |
| Sample Rate | 8.65/sec |
| Health Score | 541% |
| Threads | 8 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 6-32 cores)</summary>

```
1786017141 6
1786017146 6
1786017151 6
1786017156 6
1786017161 6
1786017166 6
1786017171 6
1786017176 6
1786017181 6
1786017186 6
1786017191 6
1786017196 6
1786017201 6
1786017206 6
1786017211 6
1786017216 6
1786017221 6
1786017226 6
1786017231 6
1786017236 32
```
</details>

---

