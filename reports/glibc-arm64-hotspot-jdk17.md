---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-11 09:26:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 44 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 224 |
| Sample Rate | 3.73/sec |
| Health Score | 233% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 11 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (3 unique values: 44-48 cores)</summary>

```
1794406974 44
1794406979 44
1794406984 44
1794406989 44
1794406994 44
1794406999 44
1794407004 44
1794407009 44
1794407014 44
1794407019 44
1794407024 44
1794407029 44
1794407034 44
1794407039 46
1794407044 46
1794407049 46
1794407054 46
1794407059 46
1794407064 46
1794407069 46
```
</details>

---

