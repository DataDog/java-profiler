---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-26 15:31:05 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 7 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (3 unique values: 46-48 cores)</summary>

```
1787772384 48
1787772389 48
1787772394 48
1787772399 48
1787772404 48
1787772409 48
1787772414 48
1787772419 48
1787772424 48
1787772429 48
1787772434 48
1787772439 47
1787772444 47
1787772449 47
1787772454 47
1787772459 47
1787772464 47
1787772469 48
1787772474 48
1787772479 46
```
</details>

---

