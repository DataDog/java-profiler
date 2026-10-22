---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-22 10:29:16 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 84 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 767 |
| Sample Rate | 12.78/sec |
| Health Score | 799% |
| Threads | 10 |
| Allocations | 440 |

<details>
<summary>CPU Timeline (4 unique values: 84-96 cores)</summary>

```
1792678985 84
1792678990 84
1792678995 84
1792679000 84
1792679005 84
1792679010 84
1792679015 86
1792679020 86
1792679025 88
1792679030 88
1792679035 88
1792679040 96
1792679045 96
1792679050 96
1792679055 96
1792679060 96
1792679065 96
1792679070 96
1792679075 96
1792679080 96
```
</details>

---

