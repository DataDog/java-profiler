---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-09 18:56:12 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (4 unique values: 20-42 cores)</summary>

```
1794268242 40
1794268247 40
1794268252 40
1794268257 40
1794268262 40
1794268267 40
1794268272 40
1794268277 40
1794268282 40
1794268287 23
1794268292 23
1794268297 23
1794268302 23
1794268307 40
1794268312 40
1794268317 40
1794268322 40
1794268327 20
1794268332 20
1794268337 20
```
</details>

---

