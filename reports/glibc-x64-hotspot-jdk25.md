---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-06 04:52:00 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 10 |
| Allocations | 496 |

<details>
<summary>CPU Timeline (3 unique values: 27-70 cores)</summary>

```
1786006045 27
1786006050 27
1786006055 27
1786006060 27
1786006065 27
1786006070 27
1786006075 27
1786006080 27
1786006085 62
1786006090 62
1786006095 62
1786006100 62
1786006105 62
1786006110 62
1786006115 62
1786006120 62
1786006125 62
1786006130 62
1786006135 70
1786006140 70
```
</details>

---

