---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 12:58:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 110 |
| Sample Rate | 1.83/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 7 |
| Allocations | 22 |

<details>
<summary>CPU Timeline (3 unique values: 24-34 cores)</summary>

```
1795542770 24
1795542775 24
1795542780 24
1795542785 24
1795542790 24
1795542795 29
1795542800 29
1795542805 29
1795542810 29
1795542815 29
1795542820 29
1795542826 29
1795542831 29
1795542836 29
1795542841 29
1795542846 29
1795542851 29
1795542856 29
1795542861 29
1795542866 29
```
</details>

---

