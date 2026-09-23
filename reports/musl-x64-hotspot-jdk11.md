---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:06:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 970 |
| Sample Rate | 16.17/sec |
| Health Score | 1011% |
| Threads | 11 |
| Allocations | 539 |

<details>
<summary>CPU Timeline (3 unique values: 32-66 cores)</summary>

```
1790168539 32
1790168544 32
1790168549 32
1790168554 32
1790168559 32
1790168564 32
1790168569 32
1790168574 32
1790168579 32
1790168584 32
1790168589 32
1790168594 32
1790168599 34
1790168604 34
1790168609 66
1790168615 66
1790168620 66
1790168625 66
1790168630 66
1790168635 66
```
</details>

---

