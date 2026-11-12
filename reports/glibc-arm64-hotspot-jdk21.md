---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-12 12:40:42 EST

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
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 576 |
| Sample Rate | 9.60/sec |
| Health Score | 600% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794504916 48
1794504921 48
1794504926 48
1794504931 48
1794504936 48
1794504941 48
1794504946 48
1794504951 48
1794504956 48
1794504961 48
1794504966 48
1794504971 48
1794504976 48
1794504981 48
1794504986 48
1794504991 43
1794504996 43
1794505001 43
1794505006 43
1794505011 43
```
</details>

---

