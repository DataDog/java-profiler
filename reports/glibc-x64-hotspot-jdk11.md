---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:08:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 868 |
| Sample Rate | 14.47/sec |
| Health Score | 904% |
| Threads | 9 |
| Allocations | 492 |

<details>
<summary>CPU Timeline (3 unique values: 46-49 cores)</summary>

```
1790172189 49
1790172194 49
1790172199 49
1790172204 47
1790172209 47
1790172214 47
1790172219 47
1790172224 49
1790172229 49
1790172234 49
1790172239 49
1790172244 47
1790172249 47
1790172254 47
1790172259 47
1790172264 47
1790172269 47
1790172274 47
1790172279 47
1790172284 47
```
</details>

---

