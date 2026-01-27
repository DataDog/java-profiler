---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-01-27 09:51:05 EST

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 17.57/sec |
| Health Score | 1098% |
| Threads | 10 |
| Allocations | 363 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 758 |
| Sample Rate | 25.27/sec |
| Health Score | 1579% |
| Threads | 11 |
| Allocations | 455 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1769524875 32
1769524880 32
1769524885 32
1769524890 32
1769524895 32
1769524900 32
1769524905 32
1769524910 30
1769524915 30
1769524920 30
1769524925 30
1769524930 30
1769524935 30
1769524940 30
1769524945 30
1769524950 32
1769524955 32
1769524960 32
1769524965 32
1769524970 30
```
</details>

---

