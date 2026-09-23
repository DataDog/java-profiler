---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-23 10:08:38 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 451 |
| Sample Rate | 7.52/sec |
| Health Score | 470% |
| Threads | 9 |
| Allocations | 309 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 10 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (5 unique values: 45-53 cores)</summary>

```
1790172179 45
1790172184 45
1790172189 45
1790172194 45
1790172199 45
1790172204 45
1790172209 45
1790172214 47
1790172219 47
1790172224 47
1790172229 47
1790172234 47
1790172239 47
1790172244 47
1790172249 47
1790172254 49
1790172259 49
1790172264 50
1790172269 50
1790172274 50
```
</details>

---

