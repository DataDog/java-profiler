---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-21 08:08:21 EDT

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
| CPU Cores (start) | 21 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 491 |
| Sample Rate | 8.18/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (2 unique values: 21-32 cores)</summary>

```
1789992211 21
1789992216 21
1789992221 21
1789992226 21
1789992231 21
1789992236 21
1789992241 21
1789992246 21
1789992251 21
1789992256 32
1789992261 32
1789992266 32
1789992271 32
1789992276 32
1789992281 32
1789992286 32
1789992291 32
1789992296 32
1789992301 32
1789992306 32
```
</details>

---

