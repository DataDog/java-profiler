---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-20 06:48:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 97 |
| Sample Rate | 1.62/sec |
| Health Score | 101% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 16 |
| Sample Rate | 0.27/sec |
| Health Score | 17% |
| Threads | 10 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (2 unique values: 32-34 cores)</summary>

```
1787222594 32
1787222599 34
1787222604 34
1787222609 34
1787222614 34
1787222619 34
1787222624 34
1787222629 34
1787222634 34
1787222639 34
1787222644 34
1787222649 34
1787222654 34
1787222659 34
1787222664 34
1787222669 34
1787222674 32
1787222679 32
1787222684 32
1787222689 32
```
</details>

---

