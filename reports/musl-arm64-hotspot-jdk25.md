---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-18 08:00:35 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 310 |
| Sample Rate | 5.17/sec |
| Health Score | 323% |
| Threads | 11 |
| Allocations | 146 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1795006497 41
1795006502 41
1795006507 41
1795006512 46
1795006517 46
1795006522 46
1795006527 46
1795006532 46
1795006537 46
1795006542 46
1795006547 46
1795006552 46
1795006557 46
1795006562 46
1795006567 46
1795006572 46
1795006577 46
1795006582 46
1795006587 46
1795006592 46
```
</details>

---

