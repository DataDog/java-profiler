---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 10:25:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 551 |
| Sample Rate | 9.18/sec |
| Health Score | 574% |
| Threads | 9 |
| Allocations | 308 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 781 |
| Sample Rate | 13.02/sec |
| Health Score | 814% |
| Threads | 11 |
| Allocations | 432 |

<details>
<summary>CPU Timeline (2 unique values: 63-65 cores)</summary>

```
1790173219 65
1790173224 65
1790173229 65
1790173234 65
1790173239 65
1790173244 65
1790173249 65
1790173254 65
1790173259 65
1790173264 65
1790173269 63
1790173274 63
1790173279 63
1790173284 63
1790173289 63
1790173294 63
1790173299 63
1790173304 65
1790173309 65
1790173314 65
```
</details>

---

