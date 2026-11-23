---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 10:21:31 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 254 |
| Sample Rate | 4.23/sec |
| Health Score | 264% |
| Threads | 15 |
| Allocations | 127 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795447000 49
1795447005 49
1795447010 49
1795447015 49
1795447020 49
1795447025 49
1795447030 49
1795447035 49
1795447040 49
1795447045 44
1795447050 44
1795447055 44
1795447060 44
1795447065 44
1795447070 44
1795447075 44
1795447080 44
1795447085 44
1795447090 44
1795447095 44
```
</details>

---

