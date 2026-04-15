---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-04-15 14:59:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 75 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 384 |
| Sample Rate | 6.40/sec |
| Health Score | 400% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (5 unique values: 50-75 cores)</summary>

```
1776279163 75
1776279168 75
1776279173 75
1776279178 75
1776279183 75
1776279188 75
1776279193 75
1776279198 75
1776279203 55
1776279208 55
1776279213 55
1776279218 50
1776279223 50
1776279228 53
1776279233 53
1776279238 53
1776279243 53
1776279248 53
1776279253 53
1776279258 53
```
</details>

---

