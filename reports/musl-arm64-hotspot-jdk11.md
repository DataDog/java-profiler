---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-17 19:15:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 108 |
| Sample Rate | 1.80/sec |
| Health Score | 112% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 12 |
| Allocations | 55 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1789686641 59
1789686646 59
1789686651 59
1789686656 59
1789686661 59
1789686666 59
1789686671 59
1789686676 59
1789686681 59
1789686686 59
1789686691 59
1789686696 59
1789686701 59
1789686706 59
1789686711 59
1789686716 59
1789686721 59
1789686726 59
1789686731 59
1789686736 64
```
</details>

---

