---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 06:42:05 EDT

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 269 |
| Sample Rate | 4.48/sec |
| Health Score | 280% |
| Threads | 12 |
| Allocations | 145 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792492672 51
1792492677 51
1792492682 51
1792492687 51
1792492692 51
1792492697 51
1792492702 51
1792492707 51
1792492712 51
1792492717 51
1792492722 51
1792492727 51
1792492732 51
1792492737 51
1792492742 51
1792492747 51
1792492752 51
1792492757 51
1792492762 51
1792492767 51
```
</details>

---

