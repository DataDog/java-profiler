---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 13:58:50 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 30-35 cores)</summary>

```
1793123640 30
1793123645 30
1793123650 30
1793123655 30
1793123660 30
1793123665 30
1793123670 30
1793123675 30
1793123680 30
1793123685 30
1793123690 30
1793123695 30
1793123700 30
1793123706 30
1793123711 35
1793123716 35
1793123721 35
1793123726 35
1793123731 35
1793123736 35
```
</details>

---

