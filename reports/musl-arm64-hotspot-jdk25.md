---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 01:03:35 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 12 |
| Allocations | 82 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1788497961 48
1788497966 48
1788497971 48
1788497976 48
1788497981 48
1788497986 48
1788497991 48
1788497996 48
1788498001 48
1788498006 48
1788498011 48
1788498016 48
1788498021 48
1788498026 48
1788498031 48
1788498036 46
1788498041 46
1788498047 46
1788498052 46
1788498057 46
```
</details>

---

