---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 05:09:42 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 8 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (3 unique values: 45-64 cores)</summary>

```
1795082642 45
1795082647 45
1795082652 45
1795082657 45
1795082662 45
1795082667 45
1795082672 50
1795082677 50
1795082682 50
1795082687 50
1795082692 50
1795082697 50
1795082702 50
1795082707 50
1795082712 50
1795082717 50
1795082722 50
1795082727 50
1795082732 50
1795082737 50
```
</details>

---

