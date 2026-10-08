---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-08 09:47:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 57 |
| Sample Rate | 0.95/sec |
| Health Score | 59% |
| Threads | 10 |
| Allocations | 79 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 201 |
| Sample Rate | 3.35/sec |
| Health Score | 209% |
| Threads | 11 |
| Allocations | 177 |

<details>
<summary>CPU Timeline (4 unique values: 7-18 cores)</summary>

```
1791466836 18
1791466841 18
1791466846 18
1791466851 18
1791466856 18
1791466861 18
1791466866 18
1791466871 18
1791466876 18
1791466881 16
1791466886 16
1791466891 7
1791466896 7
1791466901 7
1791466906 7
1791466911 7
1791466916 7
1791466921 7
1791466926 7
1791466931 7
```
</details>

---

