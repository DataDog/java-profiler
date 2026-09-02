---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-09-02 00:58:17 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 11 |
| Allocations | 80 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 881 |
| Sample Rate | 14.68/sec |
| Health Score | 917% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 38-43 cores)</summary>

```
1788324836 38
1788324841 38
1788324846 38
1788324851 43
1788324856 43
1788324861 43
1788324866 43
1788324871 43
1788324876 43
1788324881 43
1788324886 43
1788324891 43
1788324896 43
1788324901 43
1788324906 43
1788324911 43
1788324916 43
1788324921 43
1788324926 43
1788324931 43
```
</details>

---

