---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-26 10:05:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 483 |
| Sample Rate | 8.05/sec |
| Health Score | 503% |
| Threads | 8 |
| Allocations | 330 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 514 |
| Sample Rate | 8.57/sec |
| Health Score | 536% |
| Threads | 9 |
| Allocations | 445 |

<details>
<summary>CPU Timeline (3 unique values: 22-32 cores)</summary>

```
1793023178 32
1793023183 32
1793023188 32
1793023193 32
1793023198 32
1793023203 24
1793023208 24
1793023213 24
1793023218 24
1793023223 24
1793023228 24
1793023233 24
1793023238 24
1793023243 22
1793023248 22
1793023253 22
1793023258 22
1793023263 22
1793023268 22
1793023273 22
```
</details>

---

