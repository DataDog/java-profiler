---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 05:55:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 51-64 cores)</summary>

```
1792403481 64
1792403486 64
1792403491 64
1792403496 64
1792403501 64
1792403506 64
1792403511 64
1792403516 64
1792403521 64
1792403526 64
1792403531 64
1792403536 64
1792403541 64
1792403546 64
1792403551 51
1792403556 51
1792403561 51
1792403566 51
1792403571 51
1792403576 51
```
</details>

---

