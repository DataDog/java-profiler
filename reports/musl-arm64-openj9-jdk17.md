---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 02:31:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 11 |
| Allocations | 149 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 13 |
| Allocations | 81 |

<details>
<summary>CPU Timeline (2 unique values: 9-29 cores)</summary>

```
1789712750 29
1789712755 29
1789712760 29
1789712765 29
1789712770 29
1789712775 29
1789712780 29
1789712785 29
1789712790 29
1789712795 29
1789712800 29
1789712805 29
1789712810 29
1789712815 29
1789712820 29
1789712825 29
1789712830 29
1789712835 29
1789712840 9
1789712845 9
```
</details>

---

