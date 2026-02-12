---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-12 06:37:54 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 865 |
| Sample Rate | 14.42/sec |
| Health Score | 901% |
| Threads | 12 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1167 |
| Sample Rate | 19.45/sec |
| Health Score | 1216% |
| Threads | 13 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (3 unique values: 76-81 cores)</summary>

```
1770895946 81
1770895951 81
1770895956 81
1770895961 81
1770895966 81
1770895971 81
1770895976 81
1770895981 81
1770895986 78
1770895991 78
1770895996 78
1770896001 76
1770896006 76
1770896011 76
1770896016 76
1770896021 76
1770896026 76
1770896031 76
1770896036 76
1770896042 76
```
</details>

---

