---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-27 13:58:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 8 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 218 |
| Sample Rate | 3.63/sec |
| Health Score | 227% |
| Threads | 11 |
| Allocations | 138 |

<details>
<summary>CPU Timeline (7 unique values: 27-43 cores)</summary>

```
1793123656 32
1793123661 27
1793123666 27
1793123671 30
1793123676 30
1793123681 30
1793123686 30
1793123691 33
1793123696 33
1793123701 33
1793123706 33
1793123711 33
1793123716 33
1793123721 38
1793123726 38
1793123731 43
1793123736 43
1793123741 43
1793123746 43
1793123751 43
```
</details>

---

