---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 452 |
| Sample Rate | 7.53/sec |
| Health Score | 471% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 565 |
| Sample Rate | 9.42/sec |
| Health Score | 589% |
| Threads | 8 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1794357124 32
1794357129 32
1794357134 32
1794357139 32
1794357144 32
1794357149 32
1794357154 32
1794357159 32
1794357164 32
1794357169 32
1794357174 32
1794357179 32
1794357184 32
1794357189 32
1794357194 30
1794357199 30
1794357204 30
1794357209 30
1794357214 30
1794357219 30
```
</details>

---

