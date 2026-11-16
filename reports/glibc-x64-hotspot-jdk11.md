---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-16 07:35:19 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 728 |
| Sample Rate | 12.13/sec |
| Health Score | 758% |
| Threads | 11 |
| Allocations | 555 |

<details>
<summary>CPU Timeline (2 unique values: 75-77 cores)</summary>

```
1794832261 75
1794832266 75
1794832271 75
1794832276 75
1794832281 75
1794832286 75
1794832291 75
1794832296 75
1794832301 75
1794832306 75
1794832311 75
1794832316 75
1794832321 77
1794832326 77
1794832331 77
1794832336 77
1794832341 77
1794832346 77
1794832351 77
1794832356 77
```
</details>

---

