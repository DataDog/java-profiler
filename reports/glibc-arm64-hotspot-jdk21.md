---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ❌ FAIL

**Date:** 2026-02-02 12:55:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 8 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 12 |
| Sample Rate | 0.20/sec |
| Health Score | 12% |
| Threads | 6 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1770054702 24
1770054707 24
1770054712 24
1770054717 24
1770054722 24
1770054727 24
1770054732 24
1770054737 24
1770054742 24
1770054747 24
1770054752 24
1770054757 24
1770054762 24
1770054767 24
1770054772 24
1770054777 24
1770054782 24
1770054787 24
1770054792 24
1770054797 24
```
</details>

---

