---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-11 19:24:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 57 |
| CPU Cores (end) | 57 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 295 |
| Sample Rate | 4.92/sec |
| Health Score | 308% |
| Threads | 11 |
| Allocations | 136 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 12 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 57-64 cores)</summary>

```
1778541616 57
1778541621 57
1778541626 57
1778541631 57
1778541636 57
1778541641 57
1778541646 57
1778541651 57
1778541656 57
1778541661 57
1778541666 57
1778541671 57
1778541676 57
1778541681 57
1778541686 64
1778541691 64
1778541696 64
1778541701 64
1778541706 64
1778541711 64
```
</details>

---

