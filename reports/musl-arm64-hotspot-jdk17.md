---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-02 05:51:51 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 14 |
| Sample Rate | 0.23/sec |
| Health Score | 14% |
| Threads | 9 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 46-48 cores)</summary>

```
1790934416 48
1790934421 48
1790934426 48
1790934431 48
1790934436 48
1790934441 48
1790934446 46
1790934451 46
1790934456 46
1790934461 46
1790934466 46
1790934471 46
1790934476 46
1790934481 46
1790934486 46
1790934491 46
1790934496 46
1790934501 46
1790934506 46
1790934511 46
```
</details>

---

