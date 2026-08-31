---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-31 05:50:55 EDT

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
| CPU Cores (start) | 37 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 10 |

<details>
<summary>CPU Timeline (4 unique values: 34-45 cores)</summary>

```
1788169431 37
1788169436 37
1788169441 34
1788169446 34
1788169451 34
1788169456 34
1788169461 34
1788169466 34
1788169471 34
1788169476 34
1788169481 34
1788169486 34
1788169491 34
1788169496 42
1788169501 42
1788169506 45
1788169512 45
1788169517 45
1788169522 45
1788169527 45
```
</details>

---

