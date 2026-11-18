---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 09:52:43 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 8 |
| Allocations | 345 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 619 |
| Sample Rate | 10.32/sec |
| Health Score | 645% |
| Threads | 9 |
| Allocations | 436 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1795013152 32
1795013157 32
1795013162 32
1795013167 32
1795013172 32
1795013177 32
1795013182 32
1795013187 32
1795013192 32
1795013197 30
1795013202 30
1795013207 30
1795013212 30
1795013217 30
1795013222 30
1795013227 30
1795013232 30
1795013237 30
1795013242 30
1795013247 30
```
</details>

---

