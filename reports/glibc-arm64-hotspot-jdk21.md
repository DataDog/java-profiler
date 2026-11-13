---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:47:46 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 11 |
| Allocations | 72 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 8 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794580974 48
1794580979 48
1794580984 48
1794580989 48
1794580994 48
1794580999 43
1794581004 43
1794581009 43
1794581014 43
1794581019 43
1794581025 43
1794581030 43
1794581035 43
1794581040 43
1794581045 43
1794581050 43
1794581055 43
1794581060 48
1794581065 48
1794581070 48
```
</details>

---

