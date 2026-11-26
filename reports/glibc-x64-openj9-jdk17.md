---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 06:16:17 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 418 |
| Sample Rate | 6.97/sec |
| Health Score | 436% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 597 |
| Sample Rate | 9.95/sec |
| Health Score | 622% |
| Threads | 10 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 52-55 cores)</summary>

```
1795691206 52
1795691211 52
1795691216 52
1795691221 55
1795691226 55
1795691231 55
1795691236 55
1795691241 55
1795691246 55
1795691251 55
1795691256 55
1795691261 55
1795691266 55
1795691271 55
1795691276 55
1795691281 55
1795691286 55
1795691291 53
1795691296 53
1795691301 53
```
</details>

---

