---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-29 14:36:22 EDT

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 206 |
| Sample Rate | 3.43/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 162 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 13 |
| Allocations | 37 |

<details>
<summary>CPU Timeline (4 unique values: 47-59 cores)</summary>

```
1790706457 49
1790706462 49
1790706467 49
1790706472 49
1790706477 47
1790706482 47
1790706487 59
1790706492 59
1790706497 59
1790706502 59
1790706507 59
1790706512 59
1790706517 59
1790706522 59
1790706527 59
1790706532 47
1790706537 47
1790706542 47
1790706548 47
1790706553 47
```
</details>

---

