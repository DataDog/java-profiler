---
layout: default
title: musl-arm64-hotspot-jdk17
---

## musl-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-18 01:04:35 EDT

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
| CPU Cores (start) | 14 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 312 |
| Sample Rate | 5.20/sec |
| Health Score | 325% |
| Threads | 13 |
| Allocations | 88 |

<details>
<summary>CPU Timeline (3 unique values: 14-34 cores)</summary>

```
1792299655 14
1792299660 14
1792299665 34
1792299670 34
1792299675 34
1792299680 34
1792299685 34
1792299690 34
1792299695 34
1792299700 34
1792299705 34
1792299710 34
1792299715 34
1792299720 34
1792299725 34
1792299730 34
1792299735 34
1792299740 34
1792299745 34
1792299750 34
```
</details>

---

