---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-24 07:06:41 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 10 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 753 |
| Sample Rate | 12.55/sec |
| Health Score | 784% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795521717 64
1795521722 64
1795521727 64
1795521732 64
1795521737 64
1795521742 64
1795521747 64
1795521752 64
1795521757 64
1795521762 64
1795521767 64
1795521772 64
1795521777 64
1795521782 64
1795521787 64
1795521792 64
1795521797 64
1795521802 64
1795521807 64
1795521812 64
```
</details>

---

