---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 17:15:33 EDT

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 84 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 457 |
| Sample Rate | 7.62/sec |
| Health Score | 476% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 621 |
| Sample Rate | 10.35/sec |
| Health Score | 647% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (6 unique values: 81-88 cores)</summary>

```
1777324273 85
1777324278 85
1777324283 85
1777324288 85
1777324293 81
1777324298 81
1777324303 85
1777324308 85
1777324313 85
1777324318 87
1777324323 87
1777324328 87
1777324333 87
1777324338 87
1777324343 87
1777324348 87
1777324353 87
1777324358 83
1777324363 83
1777324368 83
```
</details>

---

