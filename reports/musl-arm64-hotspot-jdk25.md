---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 12:19:20 EST

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
| CPU Cores (start) | 47 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 7 |
| Allocations | 90 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 275 |
| Sample Rate | 4.58/sec |
| Health Score | 286% |
| Threads | 14 |
| Allocations | 178 |

<details>
<summary>CPU Timeline (2 unique values: 47-52 cores)</summary>

```
1795540497 47
1795540502 47
1795540507 47
1795540512 47
1795540517 47
1795540522 47
1795540527 47
1795540532 47
1795540537 47
1795540542 47
1795540547 47
1795540552 47
1795540557 47
1795540562 47
1795540567 47
1795540572 47
1795540577 47
1795540582 47
1795540587 47
1795540592 52
```
</details>

---

