---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-02-04 09:27:27 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 803 |
| Sample Rate | 13.38/sec |
| Health Score | 836% |
| Threads | 11 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1245 |
| Sample Rate | 20.75/sec |
| Health Score | 1297% |
| Threads | 13 |
| Allocations | 494 |

<details>
<summary>CPU Timeline (7 unique values: 77-84 cores)</summary>

```
1770214925 80
1770214930 80
1770214935 80
1770214940 78
1770214945 78
1770214950 78
1770214955 78
1770214960 78
1770214965 82
1770214970 82
1770214975 82
1770214980 84
1770214985 84
1770214990 84
1770214995 79
1770215000 79
1770215005 79
1770215010 79
1770215015 79
1770215020 79
```
</details>

---

