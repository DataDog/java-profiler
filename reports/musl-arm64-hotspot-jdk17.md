---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-17 06:43:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 121 |
| Sample Rate | 2.02/sec |
| Health Score | 126% |
| Threads | 8 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 13 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 37-47 cores)</summary>

```
1794915472 37
1794915477 37
1794915482 37
1794915487 37
1794915492 37
1794915497 37
1794915502 37
1794915507 37
1794915512 37
1794915517 37
1794915522 42
1794915527 42
1794915532 47
1794915537 47
1794915542 47
1794915547 47
1794915552 47
1794915557 47
1794915562 47
1794915567 47
```
</details>

---

