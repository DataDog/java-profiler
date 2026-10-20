---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-20 13:05:24 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 10 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 237 |
| Sample Rate | 3.95/sec |
| Health Score | 247% |
| Threads | 13 |
| Allocations | 123 |

<details>
<summary>CPU Timeline (2 unique values: 39-51 cores)</summary>

```
1792515650 39
1792515655 39
1792515660 39
1792515665 39
1792515670 39
1792515675 39
1792515680 39
1792515685 51
1792515690 51
1792515695 51
1792515700 51
1792515705 51
1792515710 51
1792515715 51
1792515720 51
1792515725 51
1792515730 51
1792515735 51
1792515740 51
1792515745 51
```
</details>

---

