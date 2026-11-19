---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-19 12:14:20 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1795108227 9
1795108232 9
1795108237 9
1795108242 9
1795108247 9
1795108252 29
1795108257 29
1795108262 29
1795108267 29
1795108272 29
1795108277 29
1795108282 29
1795108287 29
1795108292 29
1795108297 29
1795108302 29
1795108307 29
1795108312 29
1795108317 29
1795108322 29
```
</details>

---

