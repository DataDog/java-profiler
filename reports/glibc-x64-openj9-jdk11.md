---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-15 08:15:10 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 995 |
| Sample Rate | 16.58/sec |
| Health Score | 1036% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1794748194 63
1794748199 63
1794748204 63
1794748209 63
1794748214 63
1794748219 63
1794748224 63
1794748229 63
1794748234 61
1794748239 61
1794748244 61
1794748249 61
1794748254 61
1794748259 61
1794748264 61
1794748269 61
1794748274 63
1794748279 63
1794748284 63
1794748289 63
```
</details>

---

