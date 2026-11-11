---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 13:18:16 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 133 |
| Sample Rate | 2.22/sec |
| Health Score | 139% |
| Threads | 12 |
| Allocations | 79 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794420857 48
1794420862 48
1794420867 48
1794420872 48
1794420877 48
1794420882 48
1794420887 48
1794420892 48
1794420897 48
1794420902 48
1794420907 48
1794420912 48
1794420917 48
1794420922 48
1794420927 48
1794420932 48
1794420937 48
1794420942 48
1794420947 48
1794420952 43
```
</details>

---

