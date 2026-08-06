---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-06 04:51:59 EDT

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
| CPU Cores (start) | 61 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 374 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 821 |
| Sample Rate | 13.68/sec |
| Health Score | 855% |
| Threads | 9 |
| Allocations | 488 |

<details>
<summary>CPU Timeline (3 unique values: 49-61 cores)</summary>

```
1786006060 61
1786006065 61
1786006070 49
1786006075 49
1786006080 49
1786006085 49
1786006090 52
1786006095 52
1786006100 52
1786006105 52
1786006110 52
1786006115 52
1786006120 52
1786006125 52
1786006130 52
1786006135 52
1786006140 52
1786006145 52
1786006150 52
1786006155 52
```
</details>

---

