---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-18 08:23:48 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 13 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (3 unique values: 26-39 cores)</summary>

```
1795007865 34
1795007870 34
1795007875 34
1795007880 34
1795007885 34
1795007890 39
1795007895 39
1795007900 39
1795007905 39
1795007910 39
1795007915 39
1795007920 39
1795007925 39
1795007930 39
1795007935 39
1795007940 39
1795007945 39
1795007950 39
1795007955 39
1795007960 39
```
</details>

---

