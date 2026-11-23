---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 12:36:27 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 15 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 52-64 cores)</summary>

```
1795455100 59
1795455105 59
1795455110 59
1795455115 59
1795455120 59
1795455125 59
1795455130 59
1795455135 64
1795455140 64
1795455145 64
1795455150 64
1795455155 64
1795455160 64
1795455165 64
1795455170 64
1795455175 64
1795455180 64
1795455185 52
1795455190 52
1795455195 52
```
</details>

---

