---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-20 09:32:06 EDT

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
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 11 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1787232442 64
1787232447 64
1787232452 64
1787232457 64
1787232462 64
1787232467 64
1787232472 64
1787232477 64
1787232482 64
1787232487 64
1787232492 64
1787232497 64
1787232502 64
1787232507 64
1787232512 64
1787232517 64
1787232522 64
1787232527 64
1787232532 64
1787232537 64
```
</details>

---

