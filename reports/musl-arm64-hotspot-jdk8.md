---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 02:29:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1789712790 43
1789712795 43
1789712800 43
1789712805 48
1789712810 48
1789712815 48
1789712820 48
1789712825 48
1789712830 48
1789712835 48
1789712840 48
1789712845 48
1789712850 48
1789712855 48
1789712860 48
1789712865 48
1789712870 48
1789712875 48
1789712880 48
1789712885 48
```
</details>

---

