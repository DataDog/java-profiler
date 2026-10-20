---
layout: default
title: musl-arm64-hotspot-jdk21
---

## musl-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-20 06:11:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 10 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 10 |
| Allocations | 71 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1792490651 29
1792490656 29
1792490661 29
1792490666 29
1792490671 29
1792490676 29
1792490681 29
1792490686 29
1792490691 29
1792490696 29
1792490701 29
1792490706 29
1792490711 29
1792490716 29
1792490721 64
1792490726 64
1792490731 64
1792490736 53
1792490741 53
1792490746 53
```
</details>

---

