---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 04:42:47 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 188 |
| Sample Rate | 3.13/sec |
| Health Score | 196% |
| Threads | 8 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 6 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795426662 24
1795426667 24
1795426672 24
1795426677 24
1795426682 24
1795426687 24
1795426692 24
1795426697 24
1795426702 29
1795426707 29
1795426712 29
1795426717 29
1795426722 29
1795426727 29
1795426732 29
1795426737 29
1795426742 29
1795426747 29
1795426752 29
1795426757 29
```
</details>

---

