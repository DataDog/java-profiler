---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-11 05:49:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 54-62 cores)</summary>

```
1786441471 62
1786441476 62
1786441481 62
1786441486 62
1786441491 62
1786441496 54
1786441501 54
1786441506 54
1786441511 54
1786441516 54
1786441521 54
1786441526 54
1786441531 54
1786441536 54
1786441541 54
1786441546 54
1786441551 54
1786441556 54
1786441561 54
1786441566 54
```
</details>

---

