---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-10 18:31:13 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 12 |
| Allocations | 84 |

<details>
<summary>CPU Timeline (2 unique values: 48-53 cores)</summary>

```
1786400755 48
1786400760 48
1786400765 48
1786400770 53
1786400775 53
1786400780 53
1786400785 53
1786400790 53
1786400795 53
1786400800 53
1786400805 53
1786400810 53
1786400815 53
1786400820 53
1786400825 53
1786400830 53
1786400835 53
1786400840 53
1786400845 53
1786400850 53
```
</details>

---

