---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-23 21:23:18 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787534376 64
1787534381 64
1787534386 64
1787534391 64
1787534396 64
1787534401 64
1787534406 64
1787534411 64
1787534416 64
1787534421 64
1787534426 64
1787534431 64
1787534436 64
1787534441 64
1787534446 64
1787534451 64
1787534456 64
1787534461 64
1787534466 64
1787534471 64
```
</details>

---

