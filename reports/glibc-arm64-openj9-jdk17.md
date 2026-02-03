---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ❌ FAIL

**Date:** 2026-02-03 03:50:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 68 |
| Sample Rate | 1.13/sec |
| Health Score | 71% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 7 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770108377 24
1770108382 24
1770108387 24
1770108392 24
1770108397 24
1770108402 24
1770108407 24
1770108412 24
1770108417 24
1770108422 24
1770108427 24
1770108432 24
1770108437 24
1770108442 24
1770108447 24
1770108452 24
1770108457 24
1770108462 24
1770108467 24
1770108472 24
```
</details>

---

