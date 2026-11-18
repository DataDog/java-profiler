---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 09:52:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 328 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 731 |
| Sample Rate | 12.18/sec |
| Health Score | 761% |
| Threads | 11 |
| Allocations | 528 |

<details>
<summary>CPU Timeline (3 unique values: 53-61 cores)</summary>

```
1795013129 61
1795013134 61
1795013139 61
1795013144 61
1795013149 61
1795013154 53
1795013159 53
1795013164 53
1795013169 53
1795013174 53
1795013179 53
1795013184 53
1795013189 53
1795013194 53
1795013199 53
1795013204 53
1795013209 53
1795013214 53
1795013219 53
1795013224 59
```
</details>

---

