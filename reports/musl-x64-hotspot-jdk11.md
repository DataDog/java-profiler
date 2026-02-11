---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-02-11 11:59:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 80 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 616 |
| Sample Rate | 10.27/sec |
| Health Score | 642% |
| Threads | 7 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 964 |
| Sample Rate | 16.07/sec |
| Health Score | 1004% |
| Threads | 11 |
| Allocations | 551 |

<details>
<summary>CPU Timeline (4 unique values: 72-80 cores)</summary>

```
1770828856 72
1770828861 72
1770828866 74
1770828871 74
1770828876 74
1770828881 74
1770828886 74
1770828891 74
1770828896 74
1770828901 74
1770828906 74
1770828911 74
1770828916 74
1770828921 74
1770828926 74
1770828931 74
1770828936 74
1770828941 78
1770828946 78
1770828951 78
```
</details>

---

