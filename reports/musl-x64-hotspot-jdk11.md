---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-19 05:56:46 EDT

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 532 |
| Sample Rate | 8.87/sec |
| Health Score | 554% |
| Threads | 8 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 543 |

<details>
<summary>CPU Timeline (3 unique values: 89-96 cores)</summary>

```
1792403446 89
1792403451 89
1792403456 89
1792403461 89
1792403466 89
1792403471 89
1792403476 89
1792403481 91
1792403486 91
1792403491 91
1792403496 91
1792403501 91
1792403506 91
1792403511 91
1792403516 91
1792403521 91
1792403526 96
1792403531 96
1792403536 96
1792403541 96
```
</details>

---

