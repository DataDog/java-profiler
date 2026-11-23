---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:36:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 107 |
| Sample Rate | 1.78/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 36 |
| Sample Rate | 0.60/sec |
| Health Score | 37% |
| Threads | 9 |
| Allocations | 25 |

<details>
<summary>CPU Timeline (2 unique values: 18-49 cores)</summary>

```
1795455125 18
1795455130 18
1795455135 18
1795455140 18
1795455145 18
1795455150 18
1795455155 18
1795455160 18
1795455165 18
1795455170 18
1795455175 18
1795455180 18
1795455185 18
1795455190 18
1795455195 18
1795455200 49
1795455205 49
1795455210 49
1795455215 49
1795455220 49
```
</details>

---

