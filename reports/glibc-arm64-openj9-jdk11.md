---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-27 17:32:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 654 |
| Sample Rate | 10.90/sec |
| Health Score | 681% |
| Threads | 8 |
| Allocations | 354 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 10 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1777325199 59
1777325204 59
1777325209 59
1777325214 59
1777325219 59
1777325224 59
1777325229 59
1777325234 59
1777325239 59
1777325244 59
1777325249 64
1777325254 64
1777325259 64
1777325264 64
1777325269 64
1777325274 64
1777325279 64
1777325284 64
1777325289 64
1777325294 64
```
</details>

---

