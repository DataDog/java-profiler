---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-05-05 08:22:41 EDT

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 20 |

<details>
<summary>CPU Timeline (1 unique values: 60-60 cores)</summary>

```
1777983473 60
1777983478 60
1777983483 60
1777983488 60
1777983493 60
1777983498 60
1777983503 60
1777983508 60
1777983513 60
1777983518 60
1777983523 60
1777983528 60
1777983533 60
1777983538 60
1777983543 60
1777983548 60
1777983553 60
1777983558 60
1777983563 60
1777983568 60
```
</details>

---

