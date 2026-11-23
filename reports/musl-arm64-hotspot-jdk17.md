---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 04:42:47 EST

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 11 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 37 |
| Sample Rate | 0.62/sec |
| Health Score | 39% |
| Threads | 11 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 54-64 cores)</summary>

```
1795426677 54
1795426682 54
1795426687 54
1795426692 54
1795426697 59
1795426702 59
1795426707 59
1795426712 64
1795426717 64
1795426722 64
1795426727 64
1795426732 64
1795426737 64
1795426742 64
1795426747 64
1795426752 64
1795426757 64
1795426762 64
1795426767 64
1795426772 64
```
</details>

---

