---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:36:12 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 11 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (2 unique values: 19-24 cores)</summary>

```
1795379481 24
1795379486 24
1795379491 24
1795379496 24
1795379501 24
1795379506 24
1795379511 24
1795379516 24
1795379521 24
1795379526 24
1795379531 24
1795379536 19
1795379541 19
1795379546 19
1795379551 19
1795379556 19
1795379561 19
1795379566 19
1795379571 19
1795379576 19
```
</details>

---

