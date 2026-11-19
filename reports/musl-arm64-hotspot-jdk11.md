---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-19 08:25:42 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 131 |
| Sample Rate | 2.18/sec |
| Health Score | 136% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 23 |
| Sample Rate | 0.38/sec |
| Health Score | 24% |
| Threads | 6 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 38-45 cores)</summary>

```
1795094452 45
1795094457 45
1795094462 45
1795094467 45
1795094472 45
1795094477 45
1795094482 45
1795094487 45
1795094492 45
1795094497 45
1795094502 38
1795094507 38
1795094512 38
1795094517 38
1795094522 38
1795094527 38
1795094532 38
1795094537 38
1795094542 38
1795094547 38
```
</details>

---

