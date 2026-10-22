---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 10:29:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 570 |
| Sample Rate | 9.50/sec |
| Health Score | 594% |
| Threads | 8 |
| Allocations | 399 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 674 |
| Sample Rate | 11.23/sec |
| Health Score | 702% |
| Threads | 9 |
| Allocations | 525 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792678990 30
1792678995 30
1792679000 32
1792679005 32
1792679010 30
1792679015 30
1792679020 30
1792679025 30
1792679030 30
1792679035 30
1792679040 30
1792679045 30
1792679050 30
1792679055 30
1792679060 30
1792679065 30
1792679070 30
1792679075 30
1792679080 30
1792679085 30
```
</details>

---

