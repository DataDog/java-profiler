---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-01 09:06:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 12 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 38-43 cores)</summary>

```
1790859785 43
1790859790 43
1790859795 43
1790859800 43
1790859805 43
1790859810 43
1790859815 43
1790859820 43
1790859825 43
1790859830 43
1790859835 43
1790859840 43
1790859845 43
1790859850 43
1790859855 43
1790859860 43
1790859865 43
1790859870 38
1790859875 38
1790859880 43
```
</details>

---

