---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 12:33:15 EDT

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
| CPU Cores (start) | 58 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 760 |
| Sample Rate | 12.67/sec |
| Health Score | 792% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 56-60 cores)</summary>

```
1790699283 58
1790699288 58
1790699293 58
1790699298 56
1790699303 56
1790699308 56
1790699313 56
1790699318 56
1790699323 56
1790699328 58
1790699333 58
1790699338 58
1790699343 58
1790699348 58
1790699353 58
1790699358 58
1790699363 60
1790699368 60
1790699373 60
1790699378 60
```
</details>

---

