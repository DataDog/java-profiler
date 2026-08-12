---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-12 05:45:49 EDT

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
| CPU Cores (start) | 12 |
| CPU Cores (end) | 12 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 88 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 11 |
| Allocations | 83 |

<details>
<summary>CPU Timeline (2 unique values: 12-32 cores)</summary>

```
1786527647 12
1786527652 12
1786527657 12
1786527662 12
1786527667 12
1786527672 32
1786527677 32
1786527682 32
1786527687 32
1786527692 32
1786527697 32
1786527702 32
1786527707 32
1786527712 12
1786527717 12
1786527722 12
1786527727 12
1786527732 12
1786527737 12
1786527742 12
```
</details>

---

