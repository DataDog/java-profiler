---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-11 15:22:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 583 |
| Sample Rate | 9.72/sec |
| Health Score | 608% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 715 |
| Sample Rate | 11.92/sec |
| Health Score | 745% |
| Threads | 10 |
| Allocations | 542 |

<details>
<summary>CPU Timeline (4 unique values: 21-46 cores)</summary>

```
1794428179 32
1794428184 32
1794428189 32
1794428194 32
1794428199 32
1794428204 32
1794428209 32
1794428214 32
1794428219 32
1794428224 21
1794428229 21
1794428234 21
1794428239 21
1794428244 30
1794428249 30
1794428254 30
1794428259 30
1794428264 30
1794428269 30
1794428274 30
```
</details>

---

