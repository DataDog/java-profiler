---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-29 10:20:23 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 8 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 13 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (1 unique values: 48-48 cores)</summary>

```
1793283343 48
1793283348 48
1793283353 48
1793283358 48
1793283363 48
1793283368 48
1793283373 48
1793283378 48
1793283383 48
1793283389 48
1793283394 48
1793283399 48
1793283404 48
1793283409 48
1793283414 48
1793283419 48
1793283424 48
1793283429 48
1793283434 48
1793283439 48
```
</details>

---

