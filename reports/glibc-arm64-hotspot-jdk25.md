---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-17 13:06:34 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 8 |
| Allocations | 51 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 252 |
| Sample Rate | 4.20/sec |
| Health Score | 262% |
| Threads | 13 |
| Allocations | 153 |

<details>
<summary>CPU Timeline (3 unique values: 33-51 cores)</summary>

```
1794938595 33
1794938600 33
1794938605 33
1794938610 33
1794938615 33
1794938620 33
1794938625 33
1794938630 33
1794938635 33
1794938640 33
1794938645 33
1794938650 38
1794938655 38
1794938660 38
1794938665 38
1794938670 38
1794938675 38
1794938680 38
1794938685 38
1794938690 38
```
</details>

---

