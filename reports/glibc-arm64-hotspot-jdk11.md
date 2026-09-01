---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-01 14:36:36 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 123 |
| Sample Rate | 2.05/sec |
| Health Score | 128% |
| Threads | 11 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 126 |
| Sample Rate | 2.10/sec |
| Health Score | 131% |
| Threads | 10 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1788287384 32
1788287389 32
1788287394 32
1788287399 32
1788287404 32
1788287409 32
1788287414 32
1788287419 32
1788287424 32
1788287429 32
1788287434 32
1788287439 32
1788287444 32
1788287449 32
1788287454 32
1788287459 32
1788287464 32
1788287469 32
1788287474 32
1788287479 32
```
</details>

---

