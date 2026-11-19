---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-19 11:53:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 798 |
| Sample Rate | 13.30/sec |
| Health Score | 831% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (4 unique values: 40-70 cores)</summary>

```
1795106915 40
1795106920 40
1795106925 40
1795106930 44
1795106935 44
1795106940 44
1795106945 44
1795106950 44
1795106955 44
1795106960 44
1795106965 44
1795106970 44
1795106975 44
1795106980 42
1795106985 42
1795106990 42
1795106995 42
1795107000 42
1795107005 42
1795107010 42
```
</details>

---

