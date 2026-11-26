---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-26 06:16:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 53 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 684 |
| Sample Rate | 11.40/sec |
| Health Score | 712% |
| Threads | 9 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (3 unique values: 53-63 cores)</summary>

```
1795691236 53
1795691241 53
1795691246 53
1795691251 53
1795691256 53
1795691261 53
1795691266 53
1795691271 53
1795691276 53
1795691281 53
1795691286 61
1795691291 61
1795691296 61
1795691301 63
1795691306 63
1795691311 63
1795691316 63
1795691321 63
1795691326 63
1795691331 63
```
</details>

---

