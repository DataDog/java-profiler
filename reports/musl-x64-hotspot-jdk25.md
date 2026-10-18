---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-18 01:04:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 8 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 529 |
| Sample Rate | 8.82/sec |
| Health Score | 551% |
| Threads | 8 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (2 unique values: 24-32 cores)</summary>

```
1792299625 24
1792299630 24
1792299635 24
1792299640 24
1792299645 24
1792299650 24
1792299655 24
1792299660 24
1792299665 24
1792299670 24
1792299675 32
1792299680 32
1792299685 32
1792299690 32
1792299695 32
1792299700 32
1792299705 32
1792299710 32
1792299715 32
1792299720 32
```
</details>

---

