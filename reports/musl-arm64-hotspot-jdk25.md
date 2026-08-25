---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 09:45:08 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 85 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 60 |
| Sample Rate | 1.00/sec |
| Health Score | 62% |
| Threads | 11 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 27-32 cores)</summary>

```
1787665004 27
1787665010 27
1787665015 27
1787665020 27
1787665025 27
1787665030 27
1787665035 27
1787665040 27
1787665045 27
1787665050 27
1787665055 32
1787665060 32
1787665065 32
1787665070 32
1787665075 32
1787665080 32
1787665085 32
1787665090 32
1787665095 32
1787665100 32
```
</details>

---

