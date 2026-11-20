---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-20 12:23:35 EST

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 7 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 53 |
| Sample Rate | 0.88/sec |
| Health Score | 55% |
| Threads | 9 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 46-61 cores)</summary>

```
1795195165 46
1795195170 46
1795195175 46
1795195180 46
1795195185 61
1795195190 61
1795195195 61
1795195200 61
1795195205 61
1795195210 61
1795195215 61
1795195220 61
1795195225 61
1795195230 61
1795195235 61
1795195240 61
1795195245 61
1795195250 61
1795195255 61
1795195260 61
```
</details>

---

