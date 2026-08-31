---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-31 05:50:55 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 42 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 10 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (4 unique values: 43-46 cores)</summary>

```
1788169424 44
1788169429 44
1788169434 44
1788169439 44
1788169444 43
1788169449 43
1788169454 43
1788169459 43
1788169464 45
1788169469 45
1788169474 45
1788169479 45
1788169484 46
1788169489 46
1788169494 46
1788169499 46
1788169504 46
1788169509 46
1788169514 46
1788169519 46
```
</details>

---

