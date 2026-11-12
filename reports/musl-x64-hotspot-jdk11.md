---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-12 09:02:19 EST

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
| CPU Cores (start) | 86 |
| CPU Cores (end) | 86 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 769 |
| Sample Rate | 12.82/sec |
| Health Score | 801% |
| Threads | 10 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (2 unique values: 84-86 cores)</summary>

```
1794491833 86
1794491838 86
1794491843 86
1794491848 84
1794491853 84
1794491858 84
1794491863 84
1794491868 84
1794491873 84
1794491878 84
1794491883 84
1794491888 84
1794491893 84
1794491898 84
1794491903 84
1794491908 84
1794491913 84
1794491918 84
1794491923 84
1794491928 86
```
</details>

---

