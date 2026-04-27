---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-04-27 17:32:21 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 12 |
| CPU Cores (end) | 10 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 396 |
| Sample Rate | 6.60/sec |
| Health Score | 412% |
| Threads | 9 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 11 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (2 unique values: 10-12 cores)</summary>

```
1777325169 12
1777325174 12
1777325179 12
1777325184 12
1777325189 12
1777325194 12
1777325199 12
1777325204 12
1777325209 12
1777325214 12
1777325219 12
1777325224 12
1777325229 12
1777325234 12
1777325239 10
1777325244 10
1777325249 10
1777325254 10
1777325259 10
1777325264 10
```
</details>

---

