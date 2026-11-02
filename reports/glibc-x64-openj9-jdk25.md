---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-02 08:00:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 8 |
| Allocations | 436 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 9 |
| Allocations | 448 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1793624184 32
1793624189 32
1793624194 32
1793624199 32
1793624204 32
1793624209 32
1793624214 32
1793624219 32
1793624224 32
1793624229 32
1793624234 32
1793624239 32
1793624244 32
1793624249 32
1793624254 32
1793624259 32
1793624264 32
1793624269 32
1793624274 32
1793624279 32
```
</details>

---

