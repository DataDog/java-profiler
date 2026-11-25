---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-25 10:49:48 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 7 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 8 |
| Sample Rate | 0.13/sec |
| Health Score | 8% |
| Threads | 5 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1795621596 16
1795621601 16
1795621606 16
1795621611 16
1795621616 16
1795621621 16
1795621626 18
1795621631 18
1795621636 16
1795621641 16
1795621646 16
1795621651 16
1795621656 16
1795621661 16
1795621666 16
1795621671 16
1795621676 16
1795621681 16
1795621686 16
1795621691 16
```
</details>

---

