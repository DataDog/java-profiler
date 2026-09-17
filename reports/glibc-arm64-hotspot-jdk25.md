---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-17 06:53:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 48 |
| Sample Rate | 0.80/sec |
| Health Score | 50% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 11 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (4 unique values: 32-39 cores)</summary>

```
1789642204 38
1789642209 38
1789642214 38
1789642219 38
1789642224 38
1789642229 38
1789642234 38
1789642239 38
1789642244 38
1789642249 38
1789642254 38
1789642259 38
1789642264 39
1789642269 39
1789642274 37
1789642279 37
1789642284 37
1789642289 37
1789642294 37
1789642299 37
```
</details>

---

