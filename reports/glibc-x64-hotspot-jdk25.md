---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-15 09:57:54 EDT

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 8 |
| Allocations | 395 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 9 |
| Allocations | 508 |

<details>
<summary>CPU Timeline (5 unique values: 14-26 cores)</summary>

```
1792072271 24
1792072276 24
1792072281 24
1792072286 24
1792072291 24
1792072296 26
1792072301 26
1792072306 24
1792072311 24
1792072316 24
1792072321 24
1792072326 21
1792072331 21
1792072336 21
1792072341 21
1792072346 14
1792072351 14
1792072356 14
1792072361 14
1792072366 14
```
</details>

---

